find_package(QT NAMES Qt5 COMPONENTS Widgets Gui Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui Test REQUIRED)

# Tests need to be added as executables first
add_executable(test_eshmun
    tst_eshmun.cpp
)

# Using C++17
target_compile_features(test_eshmun PRIVATE cxx_std_17)

# Find package VTK
find_package(VTK
    9.0
    REQUIRED
    COMPONENTS
        CommonCore
        GUISupportQt
        InteractionStyle
        InteractionImage
        IOImage
        IOLegacy
        RenderingCore
        RenderingImage
        ImagingSources)

target_link_libraries(test_eshmun PRIVATE
    EshmunCore
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
    ${VTK_LIBRARIES}
)

add_test(NAME test_eshmun COMMAND test_eshmun)
