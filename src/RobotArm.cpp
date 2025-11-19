#include "RobotArm.hpp"

#include <SFML/OpenGL.hpp>

#include <algorithm>

namespace
{
void drawCube()
{
    static const GLfloat vertices[][3] = {
        {-0.5f, -0.5f, 0.5f},  {0.5f, -0.5f, 0.5f},  {0.5f, 0.5f, 0.5f},   {-0.5f, 0.5f, 0.5f},
        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},  {-0.5f, 0.5f, -0.5f}};
    static const GLint faces[][4] = {
        {0, 1, 2, 3},
        {1, 5, 6, 2},
        {5, 4, 7, 6},
        {4, 0, 3, 7},
        {3, 2, 6, 7},
        {4, 5, 1, 0}};
    static const GLfloat normals[][3] = {
        {0.f, 0.f, 1.f},
        {1.f, 0.f, 0.f},
        {0.f, 0.f, -1.f},
        {-1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, -1.f, 0.f}};

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i)
    {
        glNormal3fv(normals[i]);
        for (int idx = 0; idx < 4; ++idx)
        {
            const auto* vertex = vertices[faces[i][idx]];
            glVertex3fv(vertex);
        }
    }
    glEnd();
}
}

void RobotArm::update(float dt)
{
    const float jointSpeed = 55.f;
    const float minClawAngle = 6.f;
    const float maxClawAngle = 40.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_joints.baseRotation += jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_joints.baseRotation -= jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_joints.shoulder += jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_joints.shoulder -= jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_joints.elbow += jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_joints.elbow -= jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        m_joints.wrist += jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        m_joints.wrist -= jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        m_joints.claw += jointSpeed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        m_joints.claw -= jointSpeed * dt;

    m_joints.claw = std::clamp(m_joints.claw, minClawAngle, maxClawAngle);
}

void RobotArm::draw() const
{
    const float columnHeight = 2.f;
    const float upperArmLength = 3.5f;
    const float forearmLength = 3.f;

    glPushMatrix();
    glRotatef(m_joints.baseRotation, 0.f, 1.f, 0.f);

    glColor3f(0.8f, 0.2f, 0.2f);
    glPushMatrix();
    glScalef(2.4f, 0.5f, 2.4f);
    drawCube();
    glPopMatrix();

    glColor3f(0.7f, 0.7f, 0.75f);
    glPushMatrix();
    glTranslatef(0.f, columnHeight * 0.5f, 0.f);
    glScalef(1.f, columnHeight, 1.f);
    drawCube();
    glPopMatrix();

    glTranslatef(0.f, columnHeight, 0.f);
    glRotatef(m_joints.shoulder, 1.f, 0.f, 0.f);

    glPushMatrix();
    glTranslatef(0.f, upperArmLength * 0.5f, 0.f);
    glScalef(0.7f, upperArmLength, 0.7f);
    drawCube();
    glPopMatrix();

    glTranslatef(0.f, upperArmLength, 0.f);
    glRotatef(m_joints.elbow, 1.f, 0.f, 0.f);

    glPushMatrix();
    glTranslatef(0.f, forearmLength * 0.5f, 0.f);
    glScalef(0.6f, forearmLength, 0.6f);
    drawCube();
    glPopMatrix();

    glTranslatef(0.f, forearmLength, 0.f);
    glRotatef(m_joints.wrist, 0.f, 0.f, 1.f);

    glPushMatrix();
    glScalef(0.4f, 0.6f, 0.4f);
    drawCube();
    glPopMatrix();

    glColor3f(0.9f, 0.9f, 0.4f);
    const float clawLength = 1.f;
    const float clawPivotOffset = 0.35f;

    glPushMatrix();
    glTranslatef(clawPivotOffset, 0.3f, 0.f);
    glRotatef(m_joints.claw, 0.f, 0.f, 1.f);
    glTranslatef(0.f, clawLength * 0.5f, 0.f);
    glScalef(0.2f, clawLength, 0.2f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-clawPivotOffset, 0.3f, 0.f);
    glRotatef(-m_joints.claw, 0.f, 0.f, 1.f);
    glTranslatef(0.f, clawLength * 0.5f, 0.f);
    glScalef(0.2f, clawLength, 0.2f);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}
