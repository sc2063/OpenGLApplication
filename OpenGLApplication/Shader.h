#pragma once
#include "Render.h"
#include <string>
#include <unordered_map>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

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
	std::unordered_map<std::string, unsigned int>UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void UnBind() const;

	//setUniform
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
	void SetViewMatrix4fv(const std::string& name, const glm::mat4& matrix);
	void SetUniform3f(const std::string& name, const float v1, const float v2, const float v3);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type,const std::string&source);
	unsigned int GetUniformLocation(const std::string& name);

};

