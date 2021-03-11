cmake_minimum_required(VERSION 3.5)

project(Eshmun LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

#========================= INCLUSION OF Qt ==========================#

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#========================= INCLUSION OF VTK ==========================#

set(VTK_DIR $ENV{VTK_DIR})
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#========================= INCLUSION OF ITK ==========================#

set(ITK_DIR $ENV{ITK_DIR})
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Eshmun
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Eshmun SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Eshmun
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Eshmun PRIVATE Qt5::Widgets)

target_link_libraries(Eshmun PRIVATE ${VTK_LIBRARIES})

target_link_libraries(Eshmun PRIVATE ${ITK_LIBRARIES})
