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
#include "Camera.h"

#include<iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* windows, int width, int height) 
{
	glViewport(0, 0, width, height);
}

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
Camera camera(cameraPos);
float deltaTime = 0.0f;	
float lastFrame = 0.0f;
float screenHeight = 1000;
float screeneWidth = 1000;
float lastX = screeneWidth /2.0;
float lastY = screenHeight/2.0;


void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
		camera.KeyMove(KeyWord::LEFT, deltaTime);
	if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
		camera.KeyMove(KeyWord::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		float xoffset = xpos - lastX;
		float yoffset = 0;
		float zoffset = 0;
		camera.Mouse_Movement(xoffset, yoffset, zoffset);

	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		float xoffset = 0;
		float yoffset = lastY - ypos;
		float zoffset = 0;
		camera.Mouse_Movement(xoffset, yoffset, zoffset);
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		float xoffset = 0;
		float yoffset = 0;
		float zoffset = lastY - ypos;
		camera.Mouse_Movement(xoffset, yoffset, zoffset);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		float zoffset = 0;
		camera.Mouse_Movement(xoffset, yoffset, zoffset);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (xpos - lastX > 0)
			camera.Mouse_Movement(KeyWord::RIGHT, deltaTime);
		if (xpos - lastX < 0)
			camera.Mouse_Movement(KeyWord::LEFT, deltaTime);
		if (lastY - ypos > 0)
			camera.Mouse_Movement(KeyWord::UP, deltaTime);
		if (lastY - ypos < 0)
			camera.Mouse_Movement(KeyWord::DOWN, deltaTime);
	}
	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.Mouse_Movement(yoffset);
}


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);



	glfwSwapInterval(1);
	//OpenGl设定
	glEnable(GL_BLEND);             //启用混合功能，将图形颜色同周围颜色相混合  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);        //线抗锯齿  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);       //点抗锯齿  
	glHint(GL_POINT_SMOOTH, GL_NICEST);


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

	float floor[]
	{
		-3.5f,-0.52f,-3.5f, 0.5f,0.5f,0.5f, 2.0f,2.0f,//右上 1
		 3.5f,-0.52f,-3.5f, 0.5f,0.5f,0.5f, 2.0f,0.0f,//右下 2
		 3.5f,-0.52f, 3.5f, 0.5f,0.5f,0.5f, 0.0f,0.0f,//左下 3
		-3.5f,-0.52f, 3.5f, 0.5f,0.5f,0.5f, 0.0f,2.0f //左上 4
	};
	unsigned int f_indices[] =
	{
		0,1,2, 
		2,3,0
	};
	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0,0.0,0.0),
		glm::vec3(0.0,1.0,0.0),
		glm::vec3(0.0,0.0,1.0),
		glm::vec3(1.0,0.0,0.0),
		glm::vec3(-1.0,0.0,0.1),

	};
	glm::vec3 floorPositions[] =
	{
		glm::vec3(0.0,0.0,0.0),
	};


	Transformation tranform(screeneWidth,screenHeight);
	glm::mat4 m_model = tranform.m_model;
	glm::mat4 m_projection = tranform.m_projection;
    glm::mat4 trans = glm::mat4(1.0f);
	trans = tranform.Trans("scale", glm::vec3(1, 1, 1));

    VertexArray vao;
    VertexBuffer vbo(position, sizeof(position));
    IndexBuffer ibo(indices, sizeof(indices));

    vao.Bind();
    vbo.Bind();
    ibo.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);
  
    Shader shader("NaN.shader");
	Shader shaderf("NaN_F.shader");
    shader.Bind();

    shader.SetUniformMatrix4fv("Transform", trans);
	Texture texture1("Textures/vddjfbn_4K_Albedo.jpg");
    Texture texture("Textures/wood2_2K_Albedo.jpg");
    texture.Bind();
    shader.SetUniform1i("texture0", 0);
	texture1.Bind(1);
	shader.SetUniform1i("texture1", 1);

    vao.UnBind();
    vbo.UnBind();
    ibo.UnBind();
    shader.UnBind();

	VertexArray vaof;
	VertexBuffer vbof(floor, sizeof(floor));
	IndexBuffer ibof(indices, sizeof(indices));

	vaof.Bind();
	vbof.Bind();
	ibof.Bind();
	vaof.AddBuffer(vbof, layout);

	shaderf.Bind();

	shaderf.SetUniformMatrix4fv("Transform", trans);
	shaderf.SetUniform1i("texture2", 1);
	vaof.UnBind();
	vbof.UnBind();
	ibof.UnBind();
	shaderf.UnBind();

	//VertexArray vaolight;
	//VertexBuffer vbolight(floor, sizeof(floor));
	//IndexBuffer ibolight(indices, sizeof(indices));

	//vaolight.Bind();
	//vbolight.Bind();
	//ibolight.Bind();

	//VertexBufferLayout layoutlight;
	//layoutf.Push<float>(3);
	//layoutf.Push<float>(3);
	//layoutf.Push<float>(2);
	//vaof.AddBuffer(vbof, layoutf);

	//shaderf.Bind();

	//shaderf.SetUniformMatrix4fv("Transform", trans);
	//shaderf.SetUniform1i("texture2", 1);
	//vaof.UnBind();
	//vbof.UnBind();
	//ibof.UnBind();
	//shaderf.UnBind();

    /* Loop until the user closes the window */
    Render render(sizeof(cubePositions)/sizeof(float)/3);
	Render render_F(sizeof(floorPositions) / sizeof(float) / 3);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        render.Clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
        //float radius = 5.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		/*view = LookAtmatirx(
			glm::vec3(camX*2, 2.0, camZ*2),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));*/

		//trans = tramform.Trans("rotate", float(abs(sin(glfwGetTime()))) / 2, glm::vec3(1.0, 1.0, 0.0));
		//shader.SetUnifromMatrix4fv("Transform", trans);
		 //Camera
		glm::mat4 view = camera.GetViewMaritx();

		shader.SetUniformMatrix4fv("projection", m_projection);
		shader.SetViewMatrix4fv("view", view);
		render.Draw(vao,ibo,shader,cubePositions);
		shaderf.SetUniformMatrix4fv("projection", m_projection);
		shaderf.SetViewMatrix4fv("view", view);
		render_F.Draw(vaof, ibof, shaderf, floorPositions);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}