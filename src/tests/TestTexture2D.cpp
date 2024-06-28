#include "TestTexture2D.h"
#include "Renderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace test
{
    TestTexture2D::TestTexture2D()
        : translationA{200, 200, 0}, translationB{400, 200, 0},
        proj{glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)},
        view{glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))}
    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vao = std::make_unique<VertexArray>();
        vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push(2);
        layout.Push(2);
        vao->AddBuffer(*vertexBuffer, layout);
        indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        shader = std::make_unique<Shader>("../../../../res/Shaders/Basic.shader");
        shader->Bind();
        shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        texture = std::make_unique<Texture>("../../../../res/Textures/test.png");
        texture->Bind();
        shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
    }

    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        texture->Bind();
        {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader->SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(*vao, *indexBuffer, *shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader->SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(*vao, *indexBuffer, *shader);
            }
    }

    void TestTexture2D::OnImGuiRender()
    {
        auto io = ImGui::GetIO();
        ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
}