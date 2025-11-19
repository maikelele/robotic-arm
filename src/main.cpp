#include "RobotArm.hpp"
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/OpenGL.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

namespace
{
constexpr float degToRad = 3.1415926535f / 180.f;

struct Vec3
{
    float x;
    float y;
    float z;
};

Vec3 rotateY(const Vec3& v, float degrees)
{
    const float rad = degrees * degToRad;
    const float c = std::cos(rad);
    const float s = std::sin(rad);
    return {v.x * c + v.z * s, v.y, -v.x * s + v.z * c};
}

Vec3 rotateX(const Vec3& v, float degrees)
{
    const float rad = degrees * degToRad;
    const float c = std::cos(rad);
    const float s = std::sin(rad);
    return {v.x, v.y * c - v.z * s, v.y * s + v.z * c};
}

Vec3 normalize(const Vec3& v)
{
    const float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len == 0.f)
        return {0.f, 0.f, 0.f};
    return {v.x / len, v.y / len, v.z / len};
}
}

int main()
{
    sf::ContextSettings settings = defaultContext();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "3D Robot Arm", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    initializeOpenGL();
    updateProjection(window.getSize().x, window.getSize().y);

    ShaderProgram shader;
    GLuint groundTexture = 0;
    try
    {
        shader.loadFromFiles("shaders/phong.vert", "shaders/phong.frag");
        groundTexture = loadTexture("assets/textures/checker.tga");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    shader.use();
    shader.setUniform1i("uTexture", 0);
    shader.setUniform1f("uShininess", 32.f);
    shader.setUniform3f("uAmbientColor", 0.15f, 0.15f, 0.18f);
    shader.setUniform3f("uLightColor", 0.9f, 0.9f, 0.95f);
    shader.setUniform3f("uSpecularColor", 0.9f, 0.9f, 0.9f);

    RobotArm robot;
    float cameraYaw = 35.f;
    float cameraPitch = 20.f;
    float cameraDistance = 18.f;

    std::cout << "Controls:\n"
              << "  Arrow keys: orbit camera\n"
              << "  PageUp/PageDown: zoom\n"
              << "  Q/A: rotate base\n"
              << "  W/S: shoulder\n"
              << "  E/D: elbow\n"
              << "  R/F: wrist twist\n"
              << "  T/G: open/close claw\n"
              << "  Escape: exit\n";

    sf::Clock clock;
    bool running = true;
    while (running)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                updateProjection(event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                running = false;
            }
        }

        const float dt = clock.restart().asSeconds();
        const float cameraSpeed = 40.f;
        const float zoomSpeed = 20.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cameraYaw -= cameraSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cameraYaw += cameraSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cameraPitch += cameraSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cameraPitch -= cameraSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
            cameraDistance -= zoomSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
            cameraDistance += zoomSpeed * dt;

        cameraPitch = std::max(-10.f, std::min(80.f, cameraPitch));
        cameraDistance = std::max(8.f, std::min(35.f, cameraDistance));

        robot.update(dt);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        applyCamera(cameraYaw, cameraPitch, cameraDistance);

        shader.use();
        const Vec3 worldLightDir = normalize(Vec3{-0.6f, -1.f, -0.4f});
        const Vec3 lightEye = rotateX(rotateY(worldLightDir, cameraYaw), cameraPitch);
        shader.setUniform3f("uLightDir", lightEye.x, lightEye.y, lightEye.z);

        shader.setUniform1i("uUseTexture", 1);
        drawGround(groundTexture);

        shader.setUniform1i("uUseTexture", 0);
        robot.draw();

        window.display();
    }

    if (groundTexture != 0)
    {
        glDeleteTextures(1, &groundTexture);
    }

    return 0;
}
