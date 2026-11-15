# RRayTracer

A custom C++ ray tracer built to explore geometry intersection, shading, lighting, texture mapping, and recursive rendering effects.

This project is a lightweight educational renderer focused on core ray tracing concepts rather than a full production graphics engine.

## Features

- Ray tracing against:
  - infinite planes
  - spheres
  - polygons and mesh geometry
- Material system with:
  - diffuse shading
  - specular highlights
  - reflection
  - refraction
- UV texture support through image loading
- Several light types:
  - point lights
  - spot lights
  - area lights
  - directional lights
- Camera with adjustable position, orientation, and focal distance
- Recursive ray tracing for reflection and refraction
- PNG output generation

## Repository structure

- `src/` - core renderer source files
- `resources/` - textures, OBJ files, and output images
- `RRayTracer.sln` - Visual Studio solution
- `RRayTracer/` - project files for the Windows C++ build
- `.gitignore` - repository ignore rules

## Tech stack

- C++
- Visual Studio solution/project files
- Custom vector/matrix math utilities
- Image loading via stb
- OBJ loading support

## Getting started

### Prerequisites

- Windows
- Visual Studio 2019 or later
- Desktop development with C++

### Build steps

1. Clone the repository:
   ```bash
   git clone https://github.com/trentriek/RRayTracer.git
   cd RRayTracer
