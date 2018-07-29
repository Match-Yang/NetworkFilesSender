//
// Created by 杨万青 on 2018/7/16.
//

#ifndef NETWORKFILESSENDER_DISCOVER_MANAGER_H
#define NETWORKFILESSENDER_DISCOVER_MANAGER_H

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

 private:
  void sendSelfInfo();
  void readTargetInfo();

  void initSenderSocket();
  void initReceiverSocket();

 private:
  QByteArray info_array_;
  DeviceInfomation target_info_;
  QTimer *sender_timer_;
  QUdpSocket udp_sender_socket_4_;
  QUdpSocket udp_receiver_socket_4_;
  QHostAddress group_address_4_;
  qint16 port_;
  QString current_tcp_ip_;
};

#define DISCOVERINS Singleton<NFS::DiscoverManager>::getInstancePointer()
NFS_NAMESPACE_END

#endif  // NETWORKFILESSENDER_DISCOVER_MANAGER_H
