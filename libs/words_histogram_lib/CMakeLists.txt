cmake_minimum_required(VERSION 3.10)

# Words source module =================

set(WSM_TITLE words_source_module)

# Dummy
set(WSM_DUMMY_TARGET_TITLE ${WSM_TITLE}_dummy)
add_library(${WSM_DUMMY_TARGET_TITLE}
    include/${WSM_TITLE}/${WSM_TITLE}.h
    src/${WSM_TITLE}/${WSM_TITLE}.cpp
)
add_library(Libs::WordsHistogramLib::WordsSourceModule ALIAS ${WSM_DUMMY_TARGET_TITLE})
target_include_directories(${WSM_DUMMY_TARGET_TITLE}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/${WSM_TITLE})
target_link_libraries(${WSM_DUMMY_TARGET_TITLE}
    PUBLIC
         Qt5::Core
)

# Files implementation
set(WSM_FILES_IMPL_TARGET_TITLE ${WSM_TITLE}_files_impl)
add_library(${WSM_FILES_IMPL_TARGET_TITLE}
    include/${WSM_TITLE}/${WSM_FILES_IMPL_TARGET_TITLE}.h
    src/${WSM_TITLE}/${WSM_FILES_IMPL_TARGET_TITLE}.cpp
)
add_library(Libs::WordsHistogramLib::WordsSourceModule::FilesImpl ALIAS ${WSM_FILES_IMPL_TARGET_TITLE})
target_link_libraries(${WSM_FILES_IMPL_TARGET_TITLE}
    PRIVATE
        Libs::WordsHistogramLib::WordsSourceModule
)

# Words counter module ================

set(WCM_TITLE words_counter_module)
add_library(${WCM_TITLE}
    include/${WCM_TITLE}/${WCM_TITLE}.h
    src/${WCM_TITLE}/${WCM_TITLE}.cpp
)
add_library(Libs::WordsHistogramLib::WordsCounterModule ALIAS ${WCM_TITLE})
target_include_directories(${WCM_TITLE}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/${WCM_TITLE})
target_link_libraries(${WCM_TITLE}
    PRIVATE
        Libs::WordsHistogramLib::WordsSourceModule
)

# Words histogram lib main module ================

set(LIBRARY_TITLE words_histogram_lib)
set(MAIN_MODULE_TITLE main_module)
add_library(${MAIN_MODULE_TITLE}
    include/${LIBRARY_TITLE}.h
    src/${LIBRARY_TITLE}.cpp
)
add_library(Libs::WordsHistogramLib ALIAS ${MAIN_MODULE_TITLE})
target_include_directories(${MAIN_MODULE_TITLE}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/)
target_link_libraries(${MAIN_MODULE_TITLE}
    PUBLIC
        Libs::WordsHistogramLib::WordsCounterModule
        Libs::WordsHistogramLib::WordsSourceModule
        Libs::WordsHistogramLib::WordsSourceModule::FilesImpl
)

# Test ================================

set(TEST_TARGET_TITLE tests)
add_executable(${TEST_TARGET_TITLE}
    test/${WSM_TITLE}_tests.cpp
)
target_link_libraries(${TEST_TARGET_TITLE}
    PRIVATE
        GTest::gtest_main

        Libs::WordsHistogramLib::WordsSourceModule
        Libs::WordsHistogramLib::WordsSourceModule::FilesImpl

        Libs::WordsHistogramLib::WordsCounterModule

        Libs::WordsHistogramLib
)

# Argument to test file ===============

set(VERIFIED_FILES_FOLDER_PATH ${CMAKE_CURRENT_LIST_DIR}/share/verified_test_files/)
include_directories(${PROJECT_BINARY_DIR}/var)
configure_file(${CMAKE_CURRENT_LIST_DIR}/etc/test_config.h.cmake
    ${PROJECT_BINARY_DIR}/var/test_config.h @ONLY)
