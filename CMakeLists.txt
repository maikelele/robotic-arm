cmake_minimum_required(VERSION 3.16)
project(robot_arm_3d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(robot_arm
    src/main.cpp
    src/RobotArm.cpp
    src/Scene.cpp
    src/Texture.cpp
)

target_link_libraries(robot_arm PRIVATE OpenGL::GL sfml-system sfml-window sfml-graphics)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
