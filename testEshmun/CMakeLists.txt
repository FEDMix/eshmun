cmake_minimum_required(VERSION 3.5)

project(testEshmun LANGUAGES CXX)

include_directories("../eshmun")

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(QT NAMES Qt5 Qt6 COMPONENTS Gui Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Test REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing(true)

add_executable(testEshmun tst_testeshmun.cpp)
add_test(NAME testEshmun COMMAND testEshmun)

# enable the
target_link_libraries(testEshmun PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
    )

