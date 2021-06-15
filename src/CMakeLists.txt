# Find package Qt

# Packages for main program
find_package(QT NAMES Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

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
        RenderingCore
        RenderingImage
        ImagingSources)

add_library(EshmunCore
    pages/selectPatient/mainwindow.cpp
    pages/selectPatient/mainwindow.h
    pages/selectPatient/mainwindow.ui
    resources.qrc
    pages/patientView/annotation.cpp
    pages/patientView/annotation.h
    pages/patientView/annotation.ui
    components/VTKWidget/scenewidget.cpp
    components/VTKWidget/scenewidget.h
    components/dataloader/imageloader.cpp
    components/dataloader/imageloader.h
)

target_compile_features(EshmunCore PRIVATE cxx_std_17)

target_link_libraries(EshmunCore PRIVATE
    Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES}
)

add_executable(eshmun
    main.cpp
)

target_compile_features(eshmun PRIVATE cxx_std_17)

target_link_libraries(eshmun PRIVATE
    Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES}
    EshmunCore
)
