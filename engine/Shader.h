#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{

private:
	
	unsigned int m_RendererID;
	std::unordered_map<std::string, int>m_UniformLocationCache;
	//caching for uniforms

public:
	Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~Shader();

	void Bind()const;
	void Unbind() const;

	//Set uniforms
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	int GetUniformLocation(const std::string& name);

private:
	ShaderProgramSource ParseShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	

};

