set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        resources.qrc
        annotation.cpp
        annotation.h
        annotation.ui
        scenewidget.cpp
        scenewidget.h
)

# Find package Qt
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Find package VTK
find_package(VTK
    9.0
    REQUIRED
    COMPONENTS
        CommonCore
        GUISupportQt
        InteractionStyle
        IOImage
        IOLegacy
        RenderingCore)

add_library(libEshmun
    ${PROJECT_SOURCES}
)
add_executable(eshmun
    main.cpp
)

target_compile_features(eshmun PRIVATE cxx_std_17)

target_link_libraries(libEshmun PRIVATE
    Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES}
)
target_link_libraries(eshmun PRIVATE
    Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES}
    libEshmun
)
