set(PROJECT_SOURCES
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
        components/PreviewAnnotation/previewannotation.h
        components/PreviewAnnotation/previewannotation.cpp
        components/PreviewAnnotation/previewannotation.ui
        components/AnnotationPreview/annotationpreview.h
        components/AnnotationPreview/annotationpreview.cpp
        components/AnnotationPreview/annotationpreview.ui
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
        RenderingCore
        ImagingSources)

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
