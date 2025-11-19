#include "Scene.hpp"

#include <SFML/OpenGL.hpp>

#include <algorithm>
#include <array>
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

void configureLights()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    const GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    const GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.f};
    const GLfloat specular[] = {0.9f, 0.9f, 0.9f, 1.f};
    const GLfloat position[] = {6.f, 8.f, 4.f, 1.f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT, GL_SHININESS, 32.f);
}

void initializeOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.05f, 0.07f, 0.1f, 1.f);

    configureLights();
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
    glEnable(GL_TEXTURE_2D);
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
    glDisable(GL_TEXTURE_2D);
}
