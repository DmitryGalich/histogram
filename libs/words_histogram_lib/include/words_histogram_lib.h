#ifndef WORDS_HISTOGRAM_MAIN_MODULE
#define WORDS_HISTOGRAM_MAIN_MODULE

#include <functional>
#include <memory>

#include "words_counter_module.h"

#include "words_source_module.h"
#include "words_source_module_files_impl.h"

namespace libs {
namespace words_histogram_lib {

void CreateHistogram(
    const std::string& kFilepath,
    const std::function<
        void(const std::vector<std::pair<std::string, int>>& kWordsTop,
             const int kCompletionPercentage)> kIntermediateCallback,
    const std::function<void()> kEndingCallback,
    const int kTopSize = 15);

}  // namespace words_histogram_lib
}  // namespace libs

#endif
