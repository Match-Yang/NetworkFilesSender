//
// Created by 杨万青 on 2018/7/16.
//

#ifndef NETWORKFILESSENDER_DISCOVER_MANAGER_H
#define NETWORKFILESSENDER_DISCOVER_MANAGER_H

#include <utility>

#include <QHostAddress>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#include "common/nfs_namesapce.h"
#include "common/singleton_template.h"
#include "device_info_collector.h"

NFS_NAMESPACE_BEGIN

class DiscoverManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVariantList others_devices READ others_devices WRITE
                 set_others_devices NOTIFY othersDevicesChanged)
 public:
  explicit DiscoverManager();
  ~DiscoverManager();

  Q_INVOKABLE void setDeviceInfo(const QVariantMap &v);
  Q_INVOKABLE inline void enableDicover(bool e) {
    if (e) {
      sender_timer_->start();
    } else {
      sender_timer_->stop();
    }
  }

  QVariantList others_devices() const { return m_others_devices; }

 public slots:
  void set_others_devices(QVariantList others_devices) {
    if (m_others_devices == others_devices) return;

    m_others_devices = others_devices;
    emit othersDevicesChanged(m_others_devices);
  }

 signals:
  void othersDevicesChanged(QVariantList others_devices);

 private:
  void sendSelfInfo();
  void readTargetInfo();

  void initSenderSocket();
  void initReceiverSocket();

  QVariantList infoMapToList() const;

 private:
  QByteArray info_array_;
  DeviceInfomation target_info_;
  QTimer *sender_timer_;
  QTimer *counter_timer_;
  QUdpSocket udp_sender_socket_4_;
  QUdpSocket udp_receiver_socket_4_;
  QHostAddress group_address_4_;
  qint16 port_;
  QString current_tcp_ip_;
  QMap<QString, std::pair<int, DeviceInfomation>>
      others_info_map_;  ///< <ip, <counter, info>>
  QVariantList m_others_devices;
};

#define DISCOVERINS Singleton<NFS::DiscoverManager>::getInstancePointer()
NFS_NAMESPACE_END

#endif  // NETWORKFILESSENDER_DISCOVER_MANAGER_H
