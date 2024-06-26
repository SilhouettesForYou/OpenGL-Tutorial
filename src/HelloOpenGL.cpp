#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK)
        return -1;
    
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.0f, -0.5f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push(2);
        layout.Push(2);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);

        Shader shader("../../../../res/Shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("../../../../res/Textures/test.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        // unbind buffer
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        Renderer renderer;

        float r = 0.8f;
        float inc = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            // binding multiple objects
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            
            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                r = -0.05f;
            else if (r < 0.0f)
                r = 0.05f;
            r += inc;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}