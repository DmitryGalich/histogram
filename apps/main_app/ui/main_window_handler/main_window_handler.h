#ifndef MAIN_WINDOW_HANDLER
#define MAIN_WINDOW_HANDLER

#include <QObject>
#include <QVariant>
#include <QVariantList>

#include <functional>

class MainWindowHandler : public QObject {
  Q_OBJECT

  Q_PROPERTY(
      float progressValue READ getProgressValue NOTIFY progressValueChanged)
  Q_PROPERTY(bool progressBarVisability READ getProgressBarVisability NOTIFY
                 progressBarVisabilityChanged)

  Q_PROPERTY(int axisYMax READ getAxisYMax NOTIFY axisYMaxChanged)

  Q_PROPERTY(QStringList wordsList READ getWordsList NOTIFY wordsListChanged)
  Q_PROPERTY(
      QVariantList numbersList READ getNumbersList NOTIFY numbersListChanged)

 public:
  MainWindowHandler(
      std::function<void(
          const std::string&,
          const std::function<
              void(const std::vector<std::pair<std::string, int>>&, const int)>,
          const std::function<void()>)> kProcessFilepath,
      QObject* parent = nullptr);
  virtual ~MainWindowHandler();

  Q_INVOKABLE void processFilepath(const QString& kFilePath);

 signals:
  void progressValueChanged();
  void progressBarVisabilityChanged();

  void axisYMaxChanged();

  void wordsListChanged();
  void numbersListChanged();

 protected:
  float getProgressValue() const;
  bool getProgressBarVisability() const;

  int getAxisYMax() const;

  QStringList getWordsList() const;
  QVariantList getNumbersList() const;

 private:
  void RunIntermediateCallback(
      const std::vector<std::pair<std::string, int>>& kWordsTop,
      const int kCompletionPercentage);
  void RunEndingCallback();

  const std::function<void(
      const std::string& kFilepath,
      const std::function<void(
          const std::vector<std::pair<std::string, int>>& kWordsTop,
          const int kCompletionPercentage)> kIntermediateCallback,
      const std::function<void()> kEndingCallback)>
      kProcessFilepath_;

  float progress_value_{0.0f};
  bool progress_bar_visability_{false};

  int axis_y_max_{1};

  QStringList words_list_{};
  QVariantList numbers_list_{};
};

#endif
