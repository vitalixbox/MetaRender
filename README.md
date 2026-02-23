MetaRender is a modular graphics lab engine created as a research platform for studying different graphics technologies such as OpenGL, Vulakan and foundations of computer graphics. It is also a place to explore larger graphics architectures like game engines, and even revisit old-school versions of OpenGL.

<img src="docs/images/metarender_demo.gif" width="500">

The idea started in 2026 when I began re-studying the classic [NeHe OpenGL tutorials](https://nehe.gamedev.net/) from the 2000s. After completing about a dozen of them, I decided to build a graphics laboratory around these experiments, with reusable core subsystems such as logging, input handling, and a GUI.

## Features

- Modular C++17 architecture
- Pluggable rendering pipelines (Now only old-school OpenGL 2.1)
- Scene-based system for isolated graphics experiments (e.g. NeHe-style lessons) 
- Runtime UI built with ImGui for tweaking parameters and switching scenes
- Configurable engine settings
- Reusable core subsystems: logging, input abstraction

## Quick Start

The project is currently tested only with Visual Studio. 
- Open `CMakeLists.txt` in Visual Studio as a CMake project  
- Build the project  
- Run it

## Next Steps

- Finish NeHe lessons
- Read book "Game Engine Architecture" and implement a game engine architecture on top of the existing graphics lab
- Implement a Vulkan rendering pipeline
- Implement software rasterizer for educational purposes
- Explore other graphics technologies and techniques, e.g. ray tracing, compute shaders, etc.
- Make some projects with the engine, e.g. game prototypes, graphics demos, demos for demoscene, etc.
