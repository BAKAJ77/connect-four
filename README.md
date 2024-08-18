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

## Configurations
- `windowResolution` - Specifies what resolution the window should be (Default: `800x800`).
- `gridDimensions` - Specifies the number of columns and rows the grid should contain (Default: `7x6`, Min: `5 columns/rows`, Max: `10 columns/rows`).
- `winningRowLength` - Specifies the number of counters needed in a row for a player to be declared as the winner (Default: `4`, Min: `3`, Max: `6`).

## License
This project is released under the terms of the Apache 2.0 license. See [LICENSE](LICENSE) for more information or see https://www.apache.org/licenses/LICENSE-2.0.
