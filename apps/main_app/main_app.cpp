#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "main_app_config.h"
#include "main_window_handler.h"
#include "words_histogram_lib.h"

void ProcessFilepath(
    const std::string& kFilepath,
    const std::function<
        void(const std::vector<std::pair<std::string, int>>& kWordsTop,
             const int kCompletionPercentage)> kIntermediateCallback,
    const std::function<void()> kEndingCallback) {
  try {
    libs::words_histogram_lib::CreateHistogram(kFilepath, kIntermediateCallback,
                                               kEndingCallback, 15);

  } catch (const std::exception kException) {
    std::cerr << std::this_thread::get_id() << " " << kException.what()
              << std::endl;
  }
}

int main(int argc, char* argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  app.setOrganizationName("Organization");
  app.setOrganizationDomain("Domain");

  const std::string kMainQMLFilePath =
      MAIN_APP_QML_FOLDER_PATH + std::string("main.qml");
  const QUrl url(kMainQMLFilePath.c_str());

  QQmlApplicationEngine engine;

  MainWindowHandler main_window_handler(ProcessFilepath);
  engine.rootContext()->setContextProperty("MainWindowHandler",
                                           &main_window_handler);

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                   [url](QObject* obj, const QUrl& objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
