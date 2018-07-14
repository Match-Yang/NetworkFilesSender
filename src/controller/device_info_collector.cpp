//
// Created by 杨万青 on 2018/7/14.
//

#include <QNetworkInterface>
#include <QStorageInfo>
#include <QSysInfo>

#include "device_info_collector.h"

NFS_NAMESPACE_BEGIN

DeviceInfomation NFS::DeviceInfoCollector::getDeviceInfomation() {
  DeviceInfomation info;
  info.m_storage_capability = getStorageCapability();
  info.m_devide_name = getDeviceName();
  info.m_devide_type = getDeviceType();
  info.m_ip_address = getIpAddress();
  info.m_storage_free = getStorageFree();
  return info;
}
QString DeviceInfoCollector::getIpAddress() {
  auto all_addresses = QNetworkInterface::allAddresses();
  for (const QHostAddress &address : all_addresses) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol
        && address != QHostAddress(QHostAddress::LocalHost)) {
      return address.toString();
    }
  }
  return QString();
}
QString DeviceInfoCollector::getDeviceName() {
  return QSysInfo::prettyProductName();
}
QString DeviceInfoCollector::getDeviceType() {
  return QSysInfo::productType();
}
qint64 DeviceInfoCollector::getStorageCapability() {
  QStorageInfo storage = QStorageInfo::root();
  return storage.bytesTotal();
}
qint64 DeviceInfoCollector::getStorageFree() {
  QStorageInfo storage = QStorageInfo::root();
  return storage.bytesFree();
}

NFS_NAMESPACE_END