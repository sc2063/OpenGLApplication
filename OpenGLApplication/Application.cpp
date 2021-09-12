#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"Render.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Transformation.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include<iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* windows, int width, int height) 
{
	glViewport(0, 0, width, height);
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    float screenHeight = 800;
    float screeneWidth = 800;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screeneWidth, screenHeight, "NaN lab", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    
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

		-0.5f,-0.5f,-0.5f, 0.0f,0.1f,0.0f, 1.0f,1.0f,//右上 0
		 0.5f,-0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 1
		 0.5f, 0.5f,-0.5f, 0.0f,0.0f,1.0f, 0.0f,0.0f,//左下 2
		-0.5f, 0.5f,-0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,//左上 3

        -0.5f,-0.5f, 0.5f, 0.0f,0.5f,0.0f, 1.0f,1.0f,//右上 4
		 0.5f,-0.5f, 0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 5
		 0.5f, 0.5f, 0.5f, 0.0f,0.0f,1.0f, 0.0f,0.0f,//左下 6
		-0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,//左上 7

		-0.5f, 0.5f, 0.5f, 0.0f,0.1f,0.0f, 1.0f,1.0f,//右上 8
		-0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 9
		-0.5f,-0.5f,-0.5f, 0.0f,0.4f,1.0f, 0.0f,0.0f,//左下 10
		-0.5f,-0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,//左上 11

		 0.5f, 0.5f, 0.5f, 0.0f,0.1f,0.0f, 1.0f,1.0f,//右上 12
		 0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 13
		 0.5f,-0.5f,-0.5f, 0.8f,0.0f,1.0f, 0.0f,0.0f,//左下 14
		 0.5f,-0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,//左上 15

		-0.5f, 0.5f,-0.5f, 0.0f,0.1f,0.0f, 1.0f,1.0f,//右上 16
		 0.5f, 0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 17
		 0.5f, 0.5f, 0.5f, 0.8f,0.0f,1.0f, 0.0f,0.0f,//左下 18
		-0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,//左上 19

		-0.5f,-0.5f,-0.5f, 0.0f,0.1f,0.0f, 1.0f,1.0f,//右上 20
		 0.5f,-0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下 21
		 0.5f,-0.5f, 0.5f, 0.8f,0.0f,1.0f, 0.0f,0.0f,//左下 22
		-0.5f,-0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f //左上 23

	};

	unsigned int indices[] =
	{
		0,1,2, 4,5,6,  8,9,10, 12,13,14, 16,17,18, 20,21,22,
		2,3,0, 6,7,4, 10,11,8, 14,15,12, 18,19,16, 22,23,20
	};
	glm::mat4 m_model = glm::mat4(1.0f); 
	//glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_projection = glm::mat4(1.0f);
    m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
    m_projection = glm::perspective(glm::radians(45.0f), float(screeneWidth) / float(screenHeight), 0.1f, 100.0f);

    Transformation tramform;
    glm::mat4 trans = glm::mat4(1.0f);
	trans = tramform.Trans("scale", glm::vec3(0.8, 0.8, 0.8));

    //Camera
    glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
    glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		               glm::vec3(0.0f, 0.0f, 0.0f),
		               glm::vec3(0.0f, 1.0f, 0.0f));


    VertexArray vao;
    VertexBuffer vbo(position, sizeof(position));
    IndexBuffer ibo(indices, size(indices));
    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);
  
    Shader shader("NaN.shader");
    shader.Bind();

    shader.SetUnifromMatrix4fv("Transform", trans);


    Texture texture("Textures/wood2_2K_Albedo.jpg");
    texture.Bind();
    shader.SetUnifrom1i("texture1", 0);

    vao.UnBind();
    vbo.UnBind();
    ibo.UnBind();
    shader.UnBind();
    /* Loop until the user closes the window */
    Render render;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        render.Clear();
        float radius = 5.0f;
		float camX = sin(glfwGetTime()) * radius*2;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), 
                           glm::vec3(0.0, 0.0, 0.0), 
                           glm::vec3(0.0, 1.0, 0.0));

        trans = tramform.Trans("rotate",float(abs(sin(glfwGetTime())))/2,glm::vec3(1.0,1.0,0.0));
        render.Draw(vao, ibo, shader);
        shader.SetUnifromMatrix4fv("Transform", trans);
		shader.SetUnifromMatrix4fv("model", m_model);
		shader.SetUnifromMatrix4fv("projection", m_projection);
        shader.SetViewMatrix4fv("view", view);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}