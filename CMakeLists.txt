cmake_minimum_required(VERSION 3.8)

project(Eshmun)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List source files & resources
file (GLOB Sources *.cpp)
file (GLOB Headers *.h)
file (GLOB Resources *.qrc)
file (GLOB UIs *.ui)

# Find package Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Use Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find package VTK
find_package(VTK
    9.0
    REQUIRED
    COMPONENTS
        GUISupportQt
        IOLegacy
        CommonCore
        FiltersSources
        GUISupportQt
        RenderingCore
        IOImage
        InteractionStyle)

# Build executable
add_executable(Eshmun ${Sources} ${Headers} ${Resources} ${UIs})

target_link_libraries(Eshmun PRIVATE Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES})

vtk_module_autoinit(
    TARGETS Eshmun
    MODULES ${VTK_LIBRARIES})
