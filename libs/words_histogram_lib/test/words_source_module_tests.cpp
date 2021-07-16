#include <gtest/gtest.h>

#include "test_config.h"

#include "words_source_module.h"
#include "words_source_module_files_impl.h"

#include "words_counter_module.h"

#include "words_histogram_lib.h"

TEST(WordsSourceModule, SuccessLoading) {
  try {
    using namespace libs::words_histogram_lib::words_source_module;

    std::unique_ptr<WordsSourceModule> files_worker =
        std::make_unique<FilesImpl>(VERIFIED_FILES_FOLDER_PATH +
                                    static_cast<std::string>("test_file.txt"));
    if (!files_worker)
      std::runtime_error("Module is null");

    ASSERT_EQ(files_worker->GetType(),
              WordsSourceModule::WordsSourceModuleType::kFileType);

    files_worker->GetData(
        [&](const QStringList& kWordsList, const int kCompletionPercentage) {
          std::cout << std::endl;
          std::cout << "Process: " << kCompletionPercentage << "%" << std::endl;
          for (const auto& word : kWordsList)
            std::cout << word.toStdString() << std::endl;
        });

  } catch (const std::exception* kException) {
    std::cerr << kException->what() << std::endl;
    FAIL();
  }
}

TEST(WordsCounterModule, SuccessLoading) {
  try {
    using namespace libs::words_histogram_lib::words_counter_module;
    using namespace libs::words_histogram_lib::words_source_module;

    WordsCounterModule words_counter_module;
    words_counter_module.MakeWordsTop(
        std::make_unique<FilesImpl>(VERIFIED_FILES_FOLDER_PATH +
                                    static_cast<std::string>("test_file.txt")),
        [&](const std::vector<std::pair<std::string, int>>& kWordsTop,
            const int kCompletionPercentage) {
          std::cout << "Completed: " << kCompletionPercentage << " %"
                    << std::endl;

          for (const auto& kElement : kWordsTop)
            std::cout << kElement.first << " : " << kElement.second
                      << std::endl;

          std::cout << std::endl;
        });

  } catch (const std::exception* kException) {
    std::cerr << kException->what() << std::endl;
    FAIL();
  }
}

TEST(MainModule, SuccessLoading) {
  try {
    using namespace libs::words_histogram_lib;

    CreateHistogram(
        VERIFIED_FILES_FOLDER_PATH + static_cast<std::string>("test_file.txt"),
        [&](const std::vector<std::pair<std::string, int>>& kWordsTop,
            const int kCompletionPercentage) {
          std::cout << "Completed: " << kCompletionPercentage << " %"
                    << std::endl;

          for (const auto& kElement : kWordsTop)
            std::cout << kElement.first << " : " << kElement.second
                      << std::endl;

          std::cout << std::endl;
        },
        [&]() { std::cout << "FINAL KEK" << std::endl; });

  } catch (const std::exception* kException) {
    std::cerr << kException->what() << std::endl;
    FAIL();
  }
}
