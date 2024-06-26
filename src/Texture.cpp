#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string &path)
    : rendererID{0}, filePath{path}, localBuffer{nullptr}, width{0}, height{0}, dpi{0}
{
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(path.c_str(), &width, &height, &dpi, 4);
    GLCall(glGenTextures(1, &rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // 渲染区域所要采样的纹理比实际的纹理要大，需要将原纹理进行放大
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (localBuffer)
        stbi_image_free(localBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &rendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}
