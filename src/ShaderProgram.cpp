#include "ShaderProgram.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace
{
void checkCompile(GLuint shader, const std::string& path)
{
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE)
        return;

    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::string log(logLength, '\0');
    glGetShaderInfoLog(shader, logLength, nullptr, log.data());
    throw std::runtime_error("Shader compile error in " + path + ":\n" + log);
}

void checkLink(GLuint program)
{
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_TRUE)
        return;

    GLint logLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::string log(logLength, '\0');
    glGetProgramInfoLog(program, logLength, nullptr, log.data());
    throw std::runtime_error("Shader link error:\n" + log);
}
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
    m_programId = other.m_programId;
    other.m_programId = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this != &other)
    {
        destroy();
        m_programId = other.m_programId;
        other.m_programId = 0;
    }
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    destroy();
}

void ShaderProgram::destroy()
{
    if (m_programId != 0)
    {
        glDeleteProgram(m_programId);
        m_programId = 0;
    }
}

std::string ShaderProgram::loadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error("Failed to open shader: " + path);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string& source)
{
    const char* src = source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

void ShaderProgram::loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
{
    const std::string vertexSrc = loadFile(vertexPath);
    const std::string fragmentSrc = loadFile(fragmentPath);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    checkCompile(vs, vertexPath);
    checkCompile(fs, fragmentPath);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    checkLink(program);

    destroy();
    m_programId = program;
}

void ShaderProgram::use() const
{
    glUseProgram(m_programId);
}

GLint ShaderProgram::uniformLocation(const char* name) const
{
    return glGetUniformLocation(m_programId, name);
}

void ShaderProgram::setUniform3f(const char* name, float x, float y, float z) const
{
    glUniform3f(uniformLocation(name), x, y, z);
}

void ShaderProgram::setUniform1f(const char* name, float value) const
{
    glUniform1f(uniformLocation(name), value);
}

void ShaderProgram::setUniform1i(const char* name, int value) const
{
    glUniform1i(uniformLocation(name), value);
}
