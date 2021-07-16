#include "words_counter_module.h"

#include <algorithm>

namespace libs {
namespace words_histogram_lib {
namespace words_counter_module {

void WordsCounterModule::MakeWordsTop(
    const std::unique_ptr<words_source_module::WordsSourceModule> kWordsModule,
    const std::function<
        void(const std::vector<std::pair<std::string, int>>& kWordsTop,
             const int kCompletionPercentage)> kIntermediateCallback,
    const int kTopSize) {
  if (!kWordsModule)
    throw std::invalid_argument("Words module is null");

  words_holder_.clear();
  std::unordered_map<std::string, int>::iterator it;

  kWordsModule->GetData([&](const QStringList& kWordsList,
                            const int kCompletionPercentage) {
    // Filling holder
    for (const auto& kWord : kWordsList) {
      it = words_holder_.find(kWord.toStdString());
      if (it == words_holder_.end())
        words_holder_.insert({kWord.toStdString(), 1});
      else
        words_holder_.at(kWord.toStdString())++;
    }

    // Creating words top
    std::vector<std::pair<std::string, int>> words_top(kTopSize);
    std::partial_sort_copy(words_holder_.begin(), words_holder_.end(),
                           words_top.begin(), words_top.end(),
                           [](std::pair<std::string, int> const& l,
                              std::pair<std::string, int> const& r) {
                             return l.second > r.second;
                           });

    // Removing empty elements
    words_top.erase(std::remove(words_top.begin(), words_top.end(),
                                std::pair<std::string, int>{"", 0}),
                    words_top.end());

    // Alphabet sorting
    std::sort(
        words_top.begin(), words_top.end(),
        [](std::pair<std::string, int> const& l,
           std::pair<std::string, int> const& r) { return l.first < r.first; });

    kIntermediateCallback(words_top, kCompletionPercentage);
  });
}

}  // namespace words_counter_module
}  // namespace words_histogram_lib
}  // namespace libs
