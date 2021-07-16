#ifndef WORDS_COUNTER_MODULE
#define WORDS_COUNTER_MODULE

#include <memory>
#include <unordered_map>
#include <vector>

#include <QString>

#include "words_source_module.h"

namespace libs {
namespace words_histogram_lib {
namespace words_counter_module {

class WordsCounterModule {
 public:
  WordsCounterModule() = default;

  void MakeWordsTop(
      const std::unique_ptr<words_source_module::WordsSourceModule>
          kWordsModule,
      const std::function<
          void(const std::vector<std::pair<std::string, int>>& kWordsTop,
               const int kCompletionPercentage)> kIntermediateCallback,
      const int kTopSize = 15);

 private:
  std::unordered_map<std::string, int> words_holder_;
};

}  // namespace words_counter_module
}  // namespace words_histogram_lib
}  // namespace libs

#endif
