set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        resources.qrc
        annotation.cpp
        annotation.h
        annotation.ui
)

add_library(libEshmun
    ${PROJECT_SOURCES}
)
add_executable(eshmun
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    annotation.cpp
    annotation.h
    annotation.ui
    tabscreen.cpp
    tabscreen.h
    tabscreen.ui
)

target_compile_features(eshmun PRIVATE cxx_std_17)

target_link_libraries(libEshmun PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
target_link_libraries(eshmun PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    libEshmun
)
