#pragma once
#include "Render.h"
#include <string>


struct ShaderProgramSource 
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int ID;
	std::string FilePath;

public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind();
	void UnBind();

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type,const std::string&source);
	unsigned int GetUniformLocation(const std::string& name);
	//setUniform
};

