#pragma once

#include <string>
#include <unordered_map>
#include "glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string Fragmentsource;
};

class Shader
{
private:
	unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	//caching for uniforms

	unsigned int m_Users;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float x, float y, float z, float w);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	inline unsigned int RemoveUser() { m_Users--; return m_Users; }
	inline void AddUser() { m_Users++; }

private:
	int GetUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& file);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int CreateShader(const std::string& vert, const std::string& frag);
};