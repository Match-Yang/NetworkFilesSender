//
// Created by 杨万青 on 2018/7/14.
//

#include <QNetworkInterface>
#include <QStorageInfo>
#include <QSysInfo>

#include "device_info_collector.h"

NFS_NAMESPACE_BEGIN

DeviceIpAddressList DeviceInfoCollector::getIpAddresses() {
  DeviceIpAddressList ip_list;
  auto all_interface = QNetworkInterface::allInterfaces();
  for (const QNetworkInterface &inter : all_interface) {
    auto entries = inter.addressEntries();
    for (auto e : entries) {
      auto ip = e.ip();
      if (! ip.isNull() && ip.protocol() == QAbstractSocket::IPv4Protocol
          && ip != QHostAddress(QHostAddress::LocalHost)
          && e.prefixLength() == 24) {
        DeviceIpAddress ta;
        ta.m_address = ip.toString();
        ta.m_name = inter.humanReadableName();
        ip_list.append(ta);
      }
    }
  }
  return ip_list;
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