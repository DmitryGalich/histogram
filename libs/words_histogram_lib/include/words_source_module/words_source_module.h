#ifndef WORDS_SOURCE_MODULE
#define WORDS_SOURCE_MODULE

#include <functional>

#include <QTextStream>

namespace libs {
namespace words_histogram_lib {
namespace words_source_module {

class WordsSourceModule {
 public:
  enum class WordsSourceModuleType { kFileType = 0 };

  virtual ~WordsSourceModule() {}

  virtual void GetData(
      const std::function<void(const QStringList& kWordsList,
                               const int kCompletionPercentage)>
          kProcessWordsList) = 0;
  virtual WordsSourceModuleType GetType() const = 0;

 protected:
  WordsSourceModuleType type_;
};

}  // namespace words_source_module
}  // namespace words_histogram_lib
}  // namespace libs

#endif
