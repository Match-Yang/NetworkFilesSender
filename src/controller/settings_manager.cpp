//
// Created by 杨万青 on 2018/7/14.
//

#include "settings_manager.h"

#include <QDir>
#include <QStandardPaths>

#include "common/nfs_namesapce.h"

NFS_NAMESPACE_BEGIN

SettingsManager::~SettingsManager() {

}
SettingsManager* SettingsManager::setting_manager = nullptr;
SettingsManager *SettingsManager::instance() {
  if (setting_manager == nullptr) {
    setting_manager = new SettingsManager();
  }
  return setting_manager;
}
SettingsManager::SettingsManager() : QObject(nullptr) {
  settings_ = new QSettings("Siriuso", "NetworkFilesSender", this);
}
const QString SettingsManager::logPath() {
  auto ld = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/NetworkFilesSender";
  if (! QDir().exists(ld)) {
    QDir().mkpath(ld);
  }
  return ld;
}

NFS_NAMESPACE_END
