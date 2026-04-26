## Project README

### Overview
This project is a simple 3D engine implemented in C. It includes support for rendering triangles on different platforms, including Linux, Windows, Wine, and WebAssembly.

### Features
- Triangle rendering
- Basic window creation (Linux, Windows)
- Wireframe triangle rendering

### Project Structure
```
<Project>/
├── build/              # .exe files produced by Main.c
├── src/                # source code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration
└── Makefile.web        # Emscripten Build configuration
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - Linux: X11 for windowing, libpng/libjpeg for image handling
  - Windows: WINAPI
  - Wine: WINAPI
  - WebAssembly: Emscripten

## Build & Run

### Building on Linux
```sh
cd <Project>
make -f Makefile.linux all
```
- `all`: Builds the project and creates an executable.
- `do`: Cleans, builds, and runs the executable.
- `clean`: Removes build artifacts.

### Running on Linux
```sh
make -f Makefile.linux exe
```

### Building on Windows
```sh
cd <Project>
make -f Makefile.windows all
```
- `all`: Builds the project and creates an executable.
- `do`: Cleans, builds, and runs the executable.
- `clean`: Removes build artifacts.

### Running on Windows
```sh
make -f Makefile.windows exe
```

### Building for Wine
```sh
cd <Project>
make -f Makefile.wine all
```
- `all`: Builds the project and creates an executable.
- `do`: Cleans, builds, and runs the executable using WINE.
- `clean`: Removes build artifacts.

### Running on WebAssembly
```sh
cd <Project>
make -f Makefile.web all
```
- `all`: Builds the project and creates an HTML file for running in a web browser.
- `do`: Cleans, builds, and runs the HTML file using emrun.
- `clean`: Removes build artifacts.

### Build Options
You can also specify additional options:
- `-d` or `--debug`: Compiles with debugging information.
  ```sh
  make -f Makefile.linux alldebug
  ```
- `-g` or `--gdb`: Runs the executable under GDB for debugging.
  ```sh
  make -f Makefile.linux debug
  ```

This README provides a basic overview of the project, its structure, and how to build and run it on different platforms.