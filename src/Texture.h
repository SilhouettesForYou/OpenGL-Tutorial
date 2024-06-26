#ifndef TEXTURE
#define TEXTURE

#include "Renderer.h"

class Texture
{
private:
    unsigned int rendererID;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, dpi;
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
};

#endif