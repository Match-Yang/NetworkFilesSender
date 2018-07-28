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
}  // namespace

DiscoverManager::DiscoverManager() : QObject(nullptr) {
  sender_timer_ = new QTimer(this);
  sender_timer_->setSingleShot(false);
  sender_timer_->setInterval(kDiscoverInterval);
  connect(sender_timer_, &QTimer::timeout, this, [=] { sendSelfInfo(); });

  // init socket
  group_address_4_ = QHostAddress(
      SETTINGSINS
          ->value(kSettingsGroup, kSettingsAddressKey, kDefaultGroupAddress)
          .toString());
  port_ = SETTINGSINS->value(kSettingsGroup, kSettingsPortKey, kDefaultPort)
              .toInt();
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
  //  qDebug() << __FUNCTION__ << info.m_devide_name << info.m_ip_address;
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

NFS_NAMESPACE_END
