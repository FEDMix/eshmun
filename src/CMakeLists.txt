add_executable(eshmun
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    annotation.cpp
    annotation.h
    annotation.ui
)

target_compile_features(eshmun PRIVATE cxx_std_17)

target_link_libraries(eshmun PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)