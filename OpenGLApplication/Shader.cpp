#include "Shader.h"
#include <iostream>
#include <malloc.h>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& filepath)
	:ID(0),FilePath(filepath)
{
	ShaderProgramSource source = ParseShader(filepath);
	ID = CreateShader(source.VertexSource, source.FragmentSource);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream,line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			{
				ss[(int)type] << line << '\n';
			}
		}
	}
	return{ ss[0].str(),ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	std::cout << src << std::endl;

	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "error" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;		
	}
	else
	{
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader was complete\n" << std::endl;
	}
	return id;
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
		std::cout << "Warning uniform" << name << "does not exist" << std::endl;
	return location;
}

Shader::~Shader()
{

}

void Shader::Bind()
{
	glUseProgram(ID);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

