//
// Created by 杨万青 on 2018/7/14.
//

#ifndef NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H
#define NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H

#include <QObject>
#include <QVariant>

#include "common/nfs_namesapce.h"
#include "common/singleton_template.h"

NFS_NAMESPACE_BEGIN

#define DECL_QSP(DataType, data_name) \
  DataType m_##data_name;             \
  Q_PROPERTY(DataType data_name MEMBER m_##data_name)

struct DeviceIpAddress {
  Q_GADGET
 public:
  DECL_QSP(QString, address)
  DECL_QSP(QString, name)
};
typedef QList<DeviceIpAddress> DeviceIpAddressList;

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
class DeviceInfoCollector : public QObject {
  Q_OBJECT
 public:
  explicit DeviceInfoCollector() = default;

  /**
   * Get all ips with netmask 255.255.255.0 for local connection.
   * QML can only access the basic data type of QList, so for the custom struct
   * we using QVariantList. You can check the doc on this page:
   * http://doc.qt.io/qt-5/qtqml-cppintegration-data.html
   * @return A list of DeviceIpAddress
   */
  Q_INVOKABLE QVariantList getIpAddresses();
  Q_INVOKABLE QString getDeviceName();
  Q_INVOKABLE QString getDeviceType();
  Q_INVOKABLE qint64 getStorageFree();
  Q_INVOKABLE qint64 getStorageCapability();
};

#define DICINS Singleton<NFS::DeviceInfoCollector>::getInstancePointer()

NFS_NAMESPACE_END

// Register the type for QVariant QVariant::fromValue(const T &value)
// you can check the doc on this page:
// http://doc.qt.io/qt-5/qvariant.html#fromValue
Q_DECLARE_METATYPE(NFS::DeviceIpAddress)
Q_DECLARE_METATYPE(NFS::DeviceIpAddressList)

#endif  // NETWORKFILESSENDER_DEVICE_INFO_COLLECTOR_H
