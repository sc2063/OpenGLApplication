#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"glm/glm/glm.hpp"
#include"Render.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include<iostream>
using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }
    else
    {
        std::cout << "Init complete" << std::endl;
    }

	float position[] =
	{
		-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
		 0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		 0.5f, 0.5f,0.0f, 0.0f,0.0f,1.0f,
		-0.5f, 0.5f,0.0f, 1.0f,0.0f,0.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};

    VertexArray vao;
    VertexBuffer vbo(position, sizeof(position));
    IndexBuffer ibo(indices, size(indices));
    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout);
  
    Shader shader("NaN.shader");
    shader.Bind();
    shader.UnBind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT
			, nullptr);
        vao.Bind();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}