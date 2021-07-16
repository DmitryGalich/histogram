#include "main_window_handler.h"

#include <chrono>
#include <thread>

MainWindowHandler::MainWindowHandler(
    std::function<
        void(const std::string& kFilepath,
             const std::function<
                 void(const std::vector<std::pair<std::string, int>>& kWordsTop,
                      const int kCompletionPercentage)> kIntermediateCallback,
             const std::function<void()> kEndingCallback)> kProcessFilepath,
    QObject* parent)
    : QObject(parent), kProcessFilepath_(kProcessFilepath) {
  emit progressValueChanged();
  emit progressBarVisabilityChanged();
}

MainWindowHandler::~MainWindowHandler() {}

void MainWindowHandler::processFilepath(const QString& kFilePath) {
  static const QString kUnnecessaryPrefix("file://");

  std::thread histogram_thread([&]() {
    kProcessFilepath_(
        (kFilePath.contains(kUnnecessaryPrefix, Qt::CaseInsensitive)
             ? kFilePath.toStdString().substr(kUnnecessaryPrefix.length())
             : kFilePath.toStdString()),

        [&](const std::vector<std::pair<std::string, int>>& kWordsTop,
            const int kCompletionPercentage) {
          RunIntermediateCallback(kWordsTop, kCompletionPercentage);
        },

        [&]() { RunEndingCallback(); });
  });
  histogram_thread.join();
}

void MainWindowHandler::RunIntermediateCallback(
    const std::vector<std::pair<std::string, int>>& kWordsTop,
    const int kCompletionPercentage) {
  words_list_.clear();
  numbers_list_.clear();

  words_list_.reserve(kWordsTop.size());
  numbers_list_.reserve(kWordsTop.size());

  axis_y_max_ = 1;

  for (size_t i = 0; i < kWordsTop.size(); i++) {
    if (kWordsTop.at(i).second > axis_y_max_)
      axis_y_max_ = kWordsTop.at(i).second;

    words_list_.append(kWordsTop.at(i).first.c_str());
    numbers_list_.append(QVariant::fromValue(kWordsTop.at(i).second));
  }

  emit wordsListChanged();
  emit numbersListChanged();
  emit axisYMaxChanged();

  progress_value_ = static_cast<float>(kCompletionPercentage) / 100;
  emit progressValueChanged();

  if (!progress_bar_visability_) {
    progress_bar_visability_ = true;
    emit progressBarVisabilityChanged();
  }
}

void MainWindowHandler::RunEndingCallback() {
  progress_value_ = 1;
  emit progressValueChanged();

  progress_bar_visability_ = false;
  emit progressBarVisabilityChanged();
}

// =============

float MainWindowHandler::getProgressValue() const {
  return progress_value_;
}

bool MainWindowHandler::getProgressBarVisability() const {
  return progress_bar_visability_;
}

QStringList MainWindowHandler::getWordsList() const {
  return words_list_;
}

QVariantList MainWindowHandler::getNumbersList() const {
  return numbers_list_;
}

int MainWindowHandler::getAxisYMax() const {
  return axis_y_max_;
}
