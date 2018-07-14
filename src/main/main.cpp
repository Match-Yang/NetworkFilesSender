#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

#include "plog/log.h"
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>

#include "controller/settings_manager.h"
#include "controller/device_info_collector.h"

int main(int argc, char *argv[]) {

  auto log_file = NFS::SETTINGSINS->logPath() + "/NetworkFilesSender.log";
  static plog::RollingFileAppender<plog::TxtFormatter> file_appender(log_file.toUtf8().data(), 8000, 3);
  static plog::ColorConsoleAppender<plog::TxtFormatter> console_appender;
#ifdef QT_DEBUG
  plog::init(plog::debug, &file_appender).addAppender(&console_appender);
#else
  plog::init(plog::warning, &file_appender).addAppender(&console_appender);
#endif

  LOGI << "Config file store at: " << NFS::SETTINGSINS->path();
  LOGI << "Log file store at: " << NFS::SETTINGSINS->logPath();
  auto info = NFS::DeviceInfoCollector().getDeviceInfomation();
  LOGW << info.m_storage_capability;
  LOGW << info.m_storage_free;
  LOGW << info.m_ip_address;
  LOGW << info.m_devide_type;
  LOGW << info.m_devide_name;

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
