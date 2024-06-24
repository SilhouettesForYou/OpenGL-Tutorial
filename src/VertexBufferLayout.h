#include "Renderer.h"
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    unsigned int stride;
    std::vector<VertexBufferElement> elements;

public:
    VertexBufferLayout()
        : stride {0} {}

    void Push(unsigned int count)
    {
        elements.push_back({ GL_FLOAT, count, GL_FALSE });
        stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    inline const std::vector<VertexBufferElement> GetElements() const
    {
        return elements;
    }

    inline unsigned int GetStride() const
    {
        return stride;
    }
};