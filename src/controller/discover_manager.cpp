//
// Created by 杨万青 on 2018/7/16.
//
#include "discover_manager.h"
#include <QDataStream>
#include <QDebug>
#include <QNetworkDatagram>

#include "settings_manager.h"

NFS_NAMESPACE_BEGIN

namespace {
const int kDiscoverInterval = 1000;
const QString kDefaultGroupAddress = "239.255.43.21";
const qint16 kDefaultPort = 4545;
const QString kSettingsGroup = "DiscoverManager";
const QString kSettingsAddressKey = "GroupAddress";
const QString kSettingsPortKey = "GroupPort";
const QString kSettingTcpIpGroup = "SettingsItem";  // same as qml
const QString kSettingTcpIpKey = "IpAddress";       // same as qml
}  // namespace

DiscoverManager::DiscoverManager() : QObject(nullptr) {
  sender_timer_ = new QTimer(this);
  sender_timer_->setSingleShot(false);
  sender_timer_->setInterval(kDiscoverInterval);
  connect(sender_timer_, &QTimer::timeout, this, [=] { sendSelfInfo(); });

  counter_timer_ = new QTimer(this);
  counter_timer_->setSingleShot(false);
  counter_timer_->setInterval(kDiscoverInterval);
  connect(counter_timer_, &QTimer::timeout, this, [=] {
    bool need_update = false;
    for (auto k : others_info_map_.keys()) {
      others_info_map_[k].first -= 1;
      // remove the info if it no longer update
      if (others_info_map_[k].first <= 0) {
        need_update = true;
        others_info_map_.remove(k);
      }
    }
    if (need_update) {
      set_others_devices(infoMapToList());
    }
  });
  counter_timer_->start();

  // init socket
  group_address_4_ = QHostAddress(
      SETTINGSINS
          ->value(kSettingsGroup, kSettingsAddressKey, kDefaultGroupAddress)
          .toString());
  port_ = SETTINGSINS->value(kSettingsGroup, kSettingsPortKey, kDefaultPort)
              .toInt();
  current_tcp_ip_ =
      SETTINGSINS->value(kSettingTcpIpGroup, kSettingTcpIpKey, "").toString();
  connect(SETTINGSINS, &SettingsManager::valueChanged, this,
          [=](const QString &group, const QString &key, const QVariant &value) {
            if (group == kSettingsGroup) {
              if (key == kSettingsAddressKey) {
                group_address_4_ = QHostAddress(value.toString());
                udp_receiver_socket_4_.joinMulticastGroup(group_address_4_);
              } else if (key == kSettingsPortKey) {
                port_ = value.toInt();
                udp_receiver_socket_4_.bind(QHostAddress::AnyIPv4, port_,
                                            QUdpSocket::ShareAddress);
              }
            } else if (group == kSettingTcpIpGroup) {
              if (key == kSettingTcpIpKey) {
                current_tcp_ip_ = value.toString();
              }
            }
          });

  initSenderSocket();
  initReceiverSocket();
}
DiscoverManager::~DiscoverManager() {}
void DiscoverManager::setDeviceInfo(const QVariantMap &v) {
  info_array_.clear();
  QDataStream out_stream(&info_array_, QIODevice::WriteOnly);
  out_stream << v.value("devide_name").toString();
  out_stream << v.value("devide_type").toString();
  out_stream << v.value("ip_address").toString();
  out_stream << v.value("storage_capability").toLongLong();
  out_stream << v.value("storage_free").toLongLong();
}

void DiscoverManager::sendSelfInfo() {
  udp_sender_socket_4_.writeDatagram(info_array_, group_address_4_, port_);
}

void DiscoverManager::readTargetInfo() {
  QNetworkDatagram dgram = udp_receiver_socket_4_.receiveDatagram();
  QByteArray data = dgram.data();
  DeviceInfomation info;
  QDataStream in_stream(&data, QIODevice::ReadOnly);
  in_stream >> info.m_devide_name;
  in_stream >> info.m_devide_type;
  in_stream >> info.m_ip_address;
  in_stream >> info.m_storage_capability;
  in_stream >> info.m_storage_free;

  if (!others_info_map_.contains(info.m_ip_address)) {
    // 把counter的初始值设置为10是为了防止counter timer刚好触发把计数归零
    //其实随便设置一个比较大的数都无所谓，因为一直接受不到消息的话，计数总能减为0
    others_info_map_[info.m_ip_address] = std::make_pair(10, info);
    LOGI << "New device: " << info.m_ip_address;
    set_others_devices(infoMapToList());
  } else {
    // increase counter
    // 反正倒数计时器不能一下给减到0就可以了，计时器的存在也只是为了验证是否一直有更新而已
    others_info_map_[info.m_ip_address].first = 10;
  }
}

void DiscoverManager::initSenderSocket() {
  udp_sender_socket_4_.bind(QHostAddress(QHostAddress::AnyIPv4), 0);
  // we only set the TTL on the IPv4 socket, as that changes the multicast scope
  udp_sender_socket_4_.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
}

void DiscoverManager::initReceiverSocket() {
  udp_receiver_socket_4_.bind(QHostAddress::AnyIPv4, port_,
                              QUdpSocket::ShareAddress);
  udp_receiver_socket_4_.joinMulticastGroup(group_address_4_);
  connect(&udp_receiver_socket_4_, &QUdpSocket::readyRead, this,
          &DiscoverManager::readTargetInfo);
}

QVariantList DiscoverManager::infoMapToList() const {
  QVariantList list;
  for (auto v : others_info_map_.values()) {
    list << QVariant::fromValue(v.second);
  }
  return list;
}

NFS_NAMESPACE_END
