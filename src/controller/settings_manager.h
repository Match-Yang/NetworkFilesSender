//
// Created by 杨万青 on 2018/7/14.
//

#ifndef NETWORKFILESSENDER_SETTINGS_MANAGER_H
#define NETWORKFILESSENDER_SETTINGS_MANAGER_H

#include <QObject>
#include <QSettings>

#include <common/singleton_template.h>
#include "common/nfs_namesapce.h"

NFS_NAMESPACE_BEGIN

class SettingsManager : public QObject {
  Q_OBJECT
 public:
  explicit SettingsManager();
  ~SettingsManager();

  const QString path() const { return settings_->fileName(); }
  const QString logPath();
  Q_INVOKABLE const QVariant value(const QString &group, const QString &key);
  Q_INVOKABLE const QVariant value(const QString &group, const QString &key,
                                   const QVariant &default_value);
  Q_INVOKABLE const void setValue(const QString &group, const QString &key,
                                  const QVariant &value);
  Q_INVOKABLE const QStringList allKeys() const;
  Q_INVOKABLE const QStringList allKeys(const QString &group) const;

 signals:
  void valueChanged(const QString &group, const QString &key,
                    const QVariant &value);

 private:
  QSettings *settings_;
};

#define SETTINGSINS Singleton<NFS::SettingsManager>::getInstancePointer()

NFS_NAMESPACE_END

#endif  // NETWORKFILESSENDER_SETTINGS_MANAGER_H
