#ifndef INDEXBUFFER
#define INDEXBUFFER
class IndexBuffer
{
private:
    unsigned int rendererID;
    unsigned int count;
public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;
};
#endif