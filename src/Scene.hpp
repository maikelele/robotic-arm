#pragma once

#include <SFML/Window/ContextSettings.hpp>

void initializeOpenGL();
void configureLights();
void updateProjection(int width, int height);
void applyCamera(float yaw, float pitch, float distance);
void drawGround(unsigned textureId);

sf::ContextSettings defaultContext();
