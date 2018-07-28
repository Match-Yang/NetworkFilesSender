//
// Created by 杨万青 on 2018/7/14.
//

#include "settings_manager.h"

#include <QDir>
#include <QStandardPaths>

#include "common/nfs_namesapce.h"

NFS_NAMESPACE_BEGIN

SettingsManager::SettingsManager() : QObject(nullptr) {
  settings_ = new QSettings("Siriuso", "NetworkFilesSender", this);
}

const QString SettingsManager::logPath() {
  auto ld =
      QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) +
      "/NetworkFilesSender";
  if (!QDir().exists(ld)) {
    QDir().mkpath(ld);
  }
  return ld;
}

const QVariant SettingsManager::value(const QString &group,
                                      const QString &key) {
  return value(group, key, QVariant());
}

const QVariant SettingsManager::value(const QString &group, const QString &key,
                                      const QVariant &default_value) {
  settings_->beginGroup(group);
  QVariant v = settings_->value(key, default_value);
  settings_->endGroup();
  return v;
}

const void SettingsManager::setValue(const QString &group, const QString &key,
                                     const QVariant &value) {
  settings_->beginGroup(group);
  settings_->setValue(key, value);
  settings_->endGroup();
  emit valueChanged(group, key, value);
}

const QStringList SettingsManager::allKeys() const {
  return settings_->allKeys();
}

const QStringList SettingsManager::allKeys(const QString &group) const {
  settings_->beginGroup(group);
  auto k = settings_->allKeys();
  settings_->endGroup();
  return k;
}

SettingsManager::~SettingsManager() {}

NFS_NAMESPACE_END
