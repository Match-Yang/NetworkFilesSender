//
// Created by 杨万青 on 2018/7/14.
//

#ifndef NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H
#define NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H

#include <QObject>

#include "common/nfs_namesapce.h"
#include "common/singleton_template.h"

NFS_NAMESPACE_BEGIN

#define DECL_QSP(DataType, data_name) DataType m_##data_name;\
Q_PROPERTY(DataType data_name MEMBER m_##data_name)

struct DeviceInfomation {
  Q_GADGET
 public:
  DECL_QSP(QString, ip_address)
  DECL_QSP(QString, devide_name)
  DECL_QSP(QString, devide_type)
  DECL_QSP(qint64, storage_capability)
  DECL_QSP(qint64, storage_free)
};

/**
 * This class is use to collect some simple info about this computer. Those info
 * can show in others client.
 */
class DeviceInfoCollector {
 public:
  explicit DeviceInfoCollector() = default;

  DeviceInfomation getDeviceInfomation();

 private:
  QString getIpAddress();
  QString getDeviceName();
  QString getDeviceType();
  qint64 getStorageFree();
  qint64 getStorageCapability();
};

NFS_NAMESPACE_END

#endif //NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H
