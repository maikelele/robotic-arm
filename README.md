# 3D Robot Arm

Interactive OpenGL scene built with C++ and SFML that presents a stylized robot arm standing on a textured platform. The project showcases a GLSL-based Phong lighting pipeline, programmable camera motions, texturing and hierarchical joint transforms.

## Features
- Classic OpenGL immediate-mode geometry driven by a custom GLSL shader pipeline
- Hierarchical robot arm model with base, shoulder, elbow, wrist and claw joints
- Manual joint control of the entire rig (base, shoulder, elbow, wrist, claw)
- Per-fragment Phong lighting (ambient + diffuse + specular) implemented in GLSL
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
- `assets/textures/checker.tga` – simple checkerboard texture authored for this project
- `shaders/phong.vert`, `shaders/phong.frag` – custom vertex & fragment shaders powering the lighting model

## Screenshots
Please run the executable and capture screenshots or short GIFs showing different camera angles and joint poses.
