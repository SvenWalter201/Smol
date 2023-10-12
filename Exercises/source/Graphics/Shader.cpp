#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& filepath) : m_RendererId(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererId = CreateShader(source.VertexSource, source.Fragmentsource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

ShaderProgramSource Shader::ParseShader(const std::string& file)
{
	std::fstream stream;
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	stream.open(file, std::ios::in);
	if (stream.is_open())
	{
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str() };
	}
	std::cout << "file not found" << std::endl;
	return { ss[0].str(), ss[1].str() };

}

unsigned int Shader::CreateShader(const std::string& vert, const std::string& frag)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vert, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(frag, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;

}




unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//error handling for shader
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if(location == -1)
	{
		std::cout << "Location of Uniform " << name << " not found" << std::endl;
	}
	
	m_UniformLocationCache[name] = location;
	return location;
}





void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

