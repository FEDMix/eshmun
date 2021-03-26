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
        IOImage
        IOLegacy
        RenderingCore
        ImagingSources)

target_link_libraries(test_eshmun PRIVATE
<<<<<<< HEAD
    EshmunCore
    Qt5::Gui
    Qt5::Test
    Qt5::Widgets
=======
    libEshmun
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
    ${VTK_LIBRARIES}
>>>>>>> main
)

# If you register a test, then ctest and make test will run it.
# Adding test parameters so the tests can run without a screen on ci
set (test_parameters -platform offscreen)
add_test(NAME test_eshmun COMMAND test_eshmun ${test_parameters})
