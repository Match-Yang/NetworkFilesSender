#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

#include "plog/log.h"
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>

#include "controller/settings_manager.h"

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

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
