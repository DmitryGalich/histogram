# Words histogram creator

**Version: 1.0.0**

Application for showing most repeatifull words in text file via histrogram form. Words in top are sorted in alphabet order.

**Development was performed with CMake flags: "Advanced list of errors" and "Warning as errors". Every development branch was squashed to single commi and merged with main branch.**

 ![Histogram](<screenshots/histogram.png>).

### Requirements:
- Windows or Linux
- Qt 5.14, including QtQuick, QtCharts
- CMake 3.10 or later
- Google test 1.10 or later

### Compiling:
```bash
 git clone git@github.com:DmitryGalich/words_histogram_creator.git
 cd words_histogram_creator
 mkdir build
 cd build
cmake .. -DQt5_DIR=Path_to_Lib/Qt/5.14.2/gcc_64/lib/cmake/Qt5 -DCMAKE_BUILD_TYPE=Debug
make -j(Cores number + 1)

```
### Project structure:
- ***apps*** - Holds C++ and QML files of **business logic** of possible apps. In this version there is only one application. 
- ***libs*** - Holds **libraries** code and its **tests**. In this version there is only library for creating histogram.
- ***etc*** - Holds configuration file for asking OS about current absolute path of binary file
- ***screenshots*** - Holds (as you might notice) the screenshots for Readme.md file
