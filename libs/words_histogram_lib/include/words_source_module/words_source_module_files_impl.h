#ifndef WORDS_SOURCE_MODULE_FILES_IMPL
#define WORDS_SOURCE_MODULE_FILES_IMPL

#include "words_source_module.h"

#include <string>

namespace libs {
namespace words_histogram_lib {
namespace words_source_module {

class FilesImpl : public WordsSourceModule {
 public:
  FilesImpl() = delete;
  FilesImpl(const std::string& kPath, const int kSinglePacketPreferedSize = 50);
  virtual ~FilesImpl() override = default;

  void GetData(const std::function<void(const QStringList& kWordsList,
                                        const int kCompletionPercentage)>
                   kProcessWordsList) override final;
  WordsSourceModule::WordsSourceModuleType GetType() const override final;

 private:
  const int kSinglePacketPreferedSize_;
  const std::string kPath_;
};

}  // namespace words_source_module
}  // namespace words_histogram_lib
}  // namespace libs

#endif
