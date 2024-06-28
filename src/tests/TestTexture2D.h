#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime);
        void OnRender();
        void OnImGuiRender();

    private:
        glm::vec3 translationA, translationB;
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;
        glm::mat4 proj;
        glm::mat4 view;
    };
}