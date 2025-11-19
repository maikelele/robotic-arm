#pragma once

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#include <SFML/OpenGL.hpp>

#include <string>

class ShaderProgram
{
public:
    ShaderProgram() = default;
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;
    ~ShaderProgram();

    void loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    GLuint id() const { return m_programId; }

    void setUniform3f(const char* name, float x, float y, float z) const;
    void setUniform1f(const char* name, float value) const;
    void setUniform1i(const char* name, int value) const;

private:
    GLuint m_programId = 0;

    static GLuint compileShader(GLenum type, const std::string& source);
    static std::string loadFile(const std::string& path);
    GLint uniformLocation(const char* name) const;
    void destroy();
};
