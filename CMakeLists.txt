cmake_minimum_required(VERSION 3.24.1)
project(ConnectFour VERSION 1.0.0 LANGUAGES C CXX)

# Set CMake macro variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # Enable the use of project solution folders

# Define project include directories, and the project source code files
set(CF_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/external/SDL_ttf/external/SDL/include" "${PROJECT_SOURCE_DIR}/external/SDL_ttf/include"
    "${PROJECT_SOURCE_DIR}/external/json/include" "${PROJECT_SOURCE_DIR}/src")

set(CF_HEADER_FILES "src/ConfigHandler.h" "src/AppWindow.h" "src/GraphicsRenderer.h" "src/Button.h" "src/GameGrid.h")
set(CF_SOURCE_FILES "src/Main.cpp" "src/ConfigHandler.cpp" "src/AppWindow.cpp" "src/GraphicsRenderer.cpp" "src/Button.cpp" "src/GameGrid.cpp")

set(BUILD_SHARED_LIBS OFF) # Force SDL and SDL_ttf to be built statically
option(CF_BUILD_TESTS "Specifies whether or not the project tests should be built" ON)

# Define executable target and configure the target
add_executable(ConnectFour "${CF_HEADER_FILES}" "${CF_SOURCE_FILES}")
target_include_directories(ConnectFour PUBLIC "${CF_INCLUDE_DIRECTORIES}")
target_compile_definitions(ConnectFour PUBLIC "$<$<CONFIG:Debug>:CF_DEBUG_MODE>")

set_target_properties(ConnectFour PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>"
    LIBRARY_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>"
    ARCHIVE_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>")

add_subdirectory("external/SDL_ttf/external/SDL")
add_subdirectory("external/SDL_ttf")
add_subdirectory("external/json")

target_link_libraries(ConnectFour PRIVATE SDL3-static SDL3_ttf-static)

if (MSVC)
    target_compile_options(ConnectFour PRIVATE "/std:c++17") # Force MSVC to use C++17 standard
    target_link_options(ConnectFour PRIVATE "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS>")
endif()
    
if (WIN32)
    target_compile_definitions(ConnectFour PUBLIC "CF_WIN64")
endif()

# Enable CTest module and include the project tests
include(CTest)
enable_testing()

add_subdirectory("tests")