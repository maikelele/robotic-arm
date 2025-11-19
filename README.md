# 3D Robot Arm

Interactive OpenGL scene built with C++ and SFML that presents a stylized robot arm standing on a textured platform. The project showcases the fixed-function rendering pipeline, programmable camera motions, Phong lighting and hierarchical joint transforms.

## Features
- Classic OpenGL (fixed pipeline) rendering embedded in an SFML window
- Hierarchical robot arm model with base, shoulder, elbow, wrist and claw joints
- Manual joint control of the entire rig (base, shoulder, elbow, wrist, claw)
- Phong lighting (ambient + diffuse + specular) with per-face normals
- Textured ground plane loaded from an external TGA image
- Keyboard orbit controls for the camera with adjustable zoom

## Requirements
- C++17 compiler
- CMake >= 3.16
- SFML 2.5 (system, window, graphics modules)
- OpenGL development libraries

All dependencies are available in common Linux distributions (e.g. `sudo apt install build-essential cmake libsfml-dev`).

## Building & Running
```bash
cmake -S . -B build
cmake --build build
./build/robot_arm
```

### Controls
- `Arrow keys` – orbit camera around the arm
- `PageUp / PageDown` – zoom in/out
- `Q/A` – rotate base (manual mode)
- `W/S` – move the shoulder joint
- `E/D` – move the elbow joint
- `R/F` – twist the wrist
- `T/G` – open or close the claw fingers
- `Esc` – quit

## Assets
- `assets/textures/checker.tga` – simple checkerboard texture authored for this project.

## Screenshots
Please run the executable and capture screenshots or short GIFs with your preferred tool while demonstrating both animation and interactive control modes.
