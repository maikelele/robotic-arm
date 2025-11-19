#include "Texture.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/OpenGL.hpp>

#include <stdexcept>

unsigned loadTexture(const std::string& path)
{
    sf::Image image;
    if (!image.loadFromFile(path))
    {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    image.flipVertically();

    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 static_cast<GLsizei>(image.getSize().x),
                 static_cast<GLsizei>(image.getSize().y),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image.getPixelsPtr());

    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}
