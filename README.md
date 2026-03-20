MetaRender is a modular graphics lab engine created as a research platform for studying different graphics technologies such as OpenGL, Vulkan and foundations of computer graphics. It is also a place to explore larger graphics architectures like game engines, and even revisit old-school versions of OpenGL.

<img src="docs/images/metarender_demo.gif" width="500">

The idea started in 2026 when I began re-studying the classic [NeHe OpenGL tutorials](https://nehe.gamedev.net/) by Jeff Molofee from the 2000s. After completing about a dozen of them, I decided to build a graphics laboratory around these experiments, with reusable core subsystems such as logging, input handling, and a GUI.

## Features

- Modular C++17 architecture
- Pluggable rendering pipelines (Currently supports only legacy OpenGL 2.1)
- Scene-based system for isolated graphics experiments (e.g. NeHe-style lessons) 
- Runtime UI built with ImGui for tweaking parameters and switching scenes
- Configurable engine settings
- Reusable core subsystems: logging, input abstraction

## QuickStart

Get repository:
1. `git@github.com:vitalixbox/MetaRender.git`
2. `git submodule update --init --recursive` project uses some vendored sources.

### Prerequisites

#### MacOS

```sh
brew install cmake
brew install ninja
brew install vcpkg
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
export VCPKG_ROOT="$HOME/vcpkg"
brew install just
```

#### Linux

TBD

#### Windows

```sh
winget install Kitware.CMake
winget install Ninja-build.Ninja
winget install Microsoft.vcpkg
# Set VCPKG_ROOT system wide
[System.Environment]::SetEnvironmentVariable(  
"VCPKG_ROOT",  
"C:\vcpkg",  
"User"  
)
winget install --id Casey.Just --exact
```

### Build and  Run

```sh
# Using justfile
just configure
just run

# Useing cmake
cmake --preset x64-release
cmake --build --preset x64-release --target run
```
