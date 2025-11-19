#pragma once

#include <SFML/Window/Keyboard.hpp>

struct RobotJoints
{
    float baseRotation = 0.f;
    float shoulder = 20.f;
    float elbow = 0.f;
    float wrist = 0.f;
    float claw = 10.f;
};

class RobotArm
{
public:
    void update(float dt);
    void draw() const;

private:
    RobotJoints m_joints;
};
