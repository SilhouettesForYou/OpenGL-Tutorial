#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct ShaderProgramSource
{
    std::string VertexShaderSource;
    std::string FragmentShaderSource;
};

class Shader
{
private:
    unsigned int rendererID;
    std::string filePath;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader(const std::string& path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // set uniform
    void SetUniform1i(const std::string& name, int v);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    int GetUniformLocation(const std::string& name);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    ShaderProgramSource ParseShader();
    unsigned int CreateShader(const std::string& vertexShader, const std:: string& fragmentShader);
};