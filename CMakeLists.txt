cmake_minimum_required(VERSION 3.5)

project(Eshmun LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

set(VTK_DIR "$HOME/vtk-inst")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(Eshmun ${PROJECT_SOURCES})
target_link_libraries(Eshmun PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Eshmun PRIVATE ${VTK_LIBRARIES})