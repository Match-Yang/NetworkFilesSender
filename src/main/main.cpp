#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include "plog/log.h"

#include "controller/device_info_collector.h"
#include "controller/discover_manager.h"
#include "controller/settings_manager.h"

int main(int argc, char *argv[]) {
  auto log_file = NFS::SETTINGSINS->logPath() + "/NetworkFilesSender.log";
  static plog::RollingFileAppender<plog::TxtFormatter> file_appender(
      log_file.toUtf8().data(), 8000, 3);
  static plog::ColorConsoleAppender<plog::TxtFormatter> console_appender;
#ifdef QT_DEBUG
  plog::init(plog::debug, &file_appender).addAppender(&console_appender);
#else
  plog::init(plog::warning, &file_appender).addAppender(&console_appender);
#endif

  LOGI << "Config file store at: " << NFS::SETTINGSINS->path();
  LOGI << "Log file store at: " << NFS::SETTINGSINS->logPath();
  auto info = NFS::DICINS->getIpAddresses();
  for (auto v : info) {
    NFS::DeviceIpAddress ip;
    if (v.canConvert<NFS::DeviceIpAddress>()) {
      ip = v.value<NFS::DeviceIpAddress>();
      qDebug() << "[ " << ip.m_address << " , " << ip.m_name << " ]";
    }
  }
  qDebug() << NFS::DICINS->getDeviceType();

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  //  qmlRegisterType<NFS::DeviceIpAddress>("com.siriuso.controller", 1, 0,
  //  "DeviceIpAddress");
  //  qmlRegisterType<NFS::DeviceIpAddressList>("com.siriuso.controller", 1, 0,
  //  "DeviceIpAddressList");

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("device_info_collector",
                                           NFS::DICINS);
  engine.rootContext()->setContextProperty("discover_manager",
                                           NFS::DISCOVERINS);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty()) return -1;

  return app.exec();
}
