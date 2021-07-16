#include "words_histogram_lib.h"

#include <iostream>
#include <thread>

#include "words_counter_module.h"

namespace libs {
namespace words_histogram_lib {

void CreateHistogram(
    const std::string& kFilepath,
    const std::function<
        void(const std::vector<std::pair<std::string, int>>& kWordsTop,
             const int kCompletionPercentage)> kIntermediateCallback,
    const std::function<void()> kEndingCallback,
    const int kTopSize) {
  words_counter_module::WordsCounterModule counter;
  counter.MakeWordsTop(
      std::make_unique<words_source_module::FilesImpl>(kFilepath),
      [&](const std::vector<std::pair<std::string, int>>& kWordsTop,
          const int kCompletionPercentage) {
        kIntermediateCallback(kWordsTop, kCompletionPercentage);
      },
      kTopSize);
  kEndingCallback();
}

}  // namespace words_histogram_lib
}  // namespace libs
