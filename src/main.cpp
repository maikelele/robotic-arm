#include "RobotArm.hpp"
#include "Scene.hpp"
#include "Texture.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/OpenGL.hpp>

#include <algorithm>
#include <iostream>

int main()
{
    sf::ContextSettings settings = defaultContext();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "3D Robot Arm", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    initializeOpenGL();
    updateProjection(window.getSize().x, window.getSize().y);

    GLuint groundTexture = 0;
    try
    {
        groundTexture = loadTexture("assets/textures/checker.tga");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

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
        configureLights();

        drawGround(groundTexture);
        robot.draw();

        window.display();
    }

    if (groundTexture != 0)
    {
        glDeleteTextures(1, &groundTexture);
    }

    return 0;
}
