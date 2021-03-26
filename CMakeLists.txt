cmake_minimum_required(VERSION 3.5)

project(eshmun LANGUAGES CXX)

# Prepend current directory to the include path
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Generate a compile_commands.json file for use with vscode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Tell CMake to run uic, moc and rcc when necessary
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Packages for main program
find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Packages for test code
find_package(QT NAMES Qt5 COMPONENTS Gui Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Test REQUIRED)

enable_testing(true)

# The executable code is here
add_subdirectory(src)

# Test code is here
add_subdirectory(test)
