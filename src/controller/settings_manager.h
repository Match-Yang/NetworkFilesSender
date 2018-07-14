//
// Created by 杨万青 on 2018/7/14.
//

#ifndef NETWORKFILESSENDER_SETTINGS_MANAGER_H
#define NETWORKFILESSENDER_SETTINGS_MANAGER_H

#include <QObject>
#include <QSettings>

#include "common/nfs_namesapce.h"
#include <common/singleton_template.h>

NFS_NAMESPACE_BEGIN

class SettingsManager : public QObject {
 Q_OBJECT
 public:
  explicit SettingsManager();
  ~SettingsManager();

 const QString path() const{return settings_->fileName();}
 const QString logPath();

 private:

 private:
  QSettings *settings_;
};

#define SETTINGSINS Singleton<NFS::SettingsManager>::getInstancePointer()

NFS_NAMESPACE_END

#endif //NETWORKFILESSENDER_SETTINGS_MANAGER_H
