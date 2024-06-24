#ifndef SHADER
#define SHADER
#include <string>
#include <unordered_map>

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
    std::unordered_map<std::string, unsigned int> uniformLocationCache;
public:
    Shader(const std::string& path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // set uniform
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
    int GetUniformLocation(const std::string& name);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    ShaderProgramSource ParseShader();
    unsigned int CreateShader(const std::string& vertexShader, const std:: string& fragmentShader);
};
#endif