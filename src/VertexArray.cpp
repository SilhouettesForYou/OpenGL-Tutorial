#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &rendererID));
    GLCall(glBindVertexArray(rendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto& elements =  layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.GetStride(), (const void*)offset));
        // 需要指定属性相对于数组起点`0`的偏移量
        // 这里的layout的布局是 position | uv
        // position的偏移量是 0，那么 uv 的偏移量是 position 分量大小乘上类型的大小
        offset += element.count * sizeof(float);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(rendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
