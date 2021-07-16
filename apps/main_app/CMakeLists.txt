add_subdirectory(ui)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set(MAIN_APP_TARGET main_app)
add_executable(${MAIN_APP_TARGET}
    ${MAIN_APP_TARGET}.cpp
    ui/qml/qml.qrc
)

target_link_libraries(${MAIN_APP_TARGET}
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Charts
        Qt5::QuickControls2

        Apps::MainApp::UI::MainWindowHandler

        Libs::WordsHistogramLib
)

# Argument to test file ===============

set(MAIN_APP_QML_FOLDER_PATH ${CMAKE_CURRENT_LIST_DIR}/ui/qml/)
include_directories(${PROJECT_BINARY_DIR}/var)
configure_file(${PROJECT_SOURCE_DIR}/etc/main_app_config.h.cmake
    ${PROJECT_BINARY_DIR}/var/main_app_config.h @ONLY)
