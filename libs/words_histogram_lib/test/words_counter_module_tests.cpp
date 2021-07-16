#include "files_impl.h"
#include "words_counter_module.h"
#include "words_source_module.h"

#include <gtest/gtest.h>

#include "words_counter_test_config.h"

TEST(FilesCounterTests, SuccessLoading) {
  try {
    using namespace libs::words_histogram_lib::words_counter_module;
    using namespace libs::words_histogram_lib::words_source_module;

    WordsCounterModule module;
    module.MakeWordsTop(std::make_unique<FilesImpl>(
        50, WORDS_COUNTER_VERIFIED_FILES_FOLDER_PATH +
                static_cast<std::string>("test_file.txt")));

  } catch (const std::exception* kException) {
    std::cerr << kException->what() << std::endl;
  }
}
