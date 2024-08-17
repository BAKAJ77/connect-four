# Connect Four

## About
This is a simple connect four game programmed in C++ along with the use of SDL3 and Nlohmann JSON.

## Requirements
All you will need to build this project is:
- CMake, of version `3.24.1` or higher
- A C++ compiler

If you don't have CMake installed on your computer, you can download the latest version from their official website [here](https://cmake.org/download/).

## Building
**For Windows-based systems:**
```
git clone --recursive https://github.com/BAKAJ77/chip8-emulator.git
md build
cd build
cmake ..
```
**For MacOS-based systems:**
```
git clone --recursive https://github.com/BAKAJ77/chip8-emulator.git
mkdir build
cd build
cmake ..
```

This should generate the project files required for you to be able to build the project yourself, though you can make CMake build the project for you by running the following command: </br>
```
cmake --build .
```

The above command builds a debug version of the application; to build a release version, you simply need to do:

**For Windows-based systems:**
```
cmake --build . --config Release
```
**For MacOS-based systems:**
```
cmake --build . -DCMAKE_BUILD_TYPE=Release
```

## Controls
- `R` - Resets the entire game grid.
