#include "Scene.hpp"

#include <SFML/OpenGL.hpp>

#include <cmath>

namespace
{
constexpr float degToRad = 3.1415926535f / 180.f;
}

sf::ContextSettings defaultContext()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    return settings;
}

void initializeOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.05f, 0.07f, 0.1f, 1.f);
}

void updateProjection(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float aspect = static_cast<float>(width) / static_cast<float>(height ? height : 1);
    const float nearPlane = 0.1f;
    const float farPlane = 100.f;
    const float fov = 60.f;
    const float top = nearPlane * std::tan(fov * 0.5f * degToRad);
    const float bottom = -top;
    const float right = top * aspect;
    const float left = -right;
    glFrustum(left, right, bottom, top, nearPlane, farPlane);
}

void applyCamera(float yaw, float pitch, float distance)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, -2.f, -distance);
    glRotatef(pitch, 1.f, 0.f, 0.f);
    glRotatef(yaw, 0.f, 1.f, 0.f);
}

void drawGround(unsigned textureId)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBegin(GL_QUADS);
    glNormal3f(0.f, 1.f, 0.f);
    const float tile = 8.f;
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-12.f, 0.f, -12.f);
    glTexCoord2f(tile, 0.f);
    glVertex3f(12.f, 0.f, -12.f);
    glTexCoord2f(tile, tile);
    glVertex3f(12.f, 0.f, 12.f);
    glTexCoord2f(0.f, tile);
    glVertex3f(-12.f, 0.f, 12.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}
