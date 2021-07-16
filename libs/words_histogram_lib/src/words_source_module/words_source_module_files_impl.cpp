#include "words_source_module_files_impl.h"

#include <iostream>

#include <QFile>

namespace libs {
namespace words_histogram_lib {
namespace words_source_module {

FilesImpl::FilesImpl(const std::string& kPath,
                     const int kSinglePacketPreferedSize)
    : kSinglePacketPreferedSize_(kSinglePacketPreferedSize), kPath_(kPath) {
  type_ = WordsSourceModuleType::kFileType;
}

void FilesImpl::GetData(
    const std::function<void(const QStringList& kWordsList,
                             const int kCompletionPercentage)>
        kProcessWordsList) {
  const auto kGetTextBlock = [](QTextStream& text_stream, QString& text_block,
                                const int kSinglePacketPreferedSize) {
    text_block = text_stream.read(kSinglePacketPreferedSize);

    // Block stops in the middle of the word. Need to finish the last word
    if (!text_block.back().isSpace()) {
      while (!text_stream.atEnd()) {
        // Reading by symbols
        auto symbol = text_stream.read(1);
        if (symbol.back().isSpace()) {
          break;
        }

        text_block += symbol;
      }
    }

    text_block = text_block.toLower();
  };

  const auto kGetWordsList = [](QString& text_block, QStringList& words_list) {
    text_block.replace(QRegExp("[^\\w\\s]"), nullptr);
    words_list = text_block.split(QChar::Space);

    // Removing empty strings
    words_list.removeAll({});
  };
  // ===================================================

  QFile file(kPath_.c_str());
  if (!file.open(QIODevice::ReadOnly))
    throw std::runtime_error("Can't open file: " + kPath_);

  QTextStream text_stream(&file);
  QString text_block("");
  QStringList words_list("");

  while (!text_stream.atEnd()) {
    kGetTextBlock(text_stream, text_block, kSinglePacketPreferedSize_);
    kGetWordsList(text_block, words_list);

    kProcessWordsList(words_list, 100 * text_stream.pos() / file.size());
  }

  file.close();
}

WordsSourceModule::WordsSourceModuleType FilesImpl::GetType() const {
  return type_;
}

}  // namespace words_source_module
}  // namespace words_histogram_lib
}  // namespace libs
