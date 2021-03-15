# Tests need to be added as executables first
add_executable(test_eshmun
    tst_testeshmun.cpp
)

# Using C++17
target_compile_features(test_eshmun PRIVATE cxx_std_17)


target_link_libraries(test_eshmun PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME test_eshmun COMMAND test_eshmun)