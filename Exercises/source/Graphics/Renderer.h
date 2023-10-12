#pragma once

#include<glm.hpp>
#include <GL/glew.h>
#include <vector>
class VertexArray;
class IndexBuffer;
class Shader;
class GameObject;

#define ASSERT(x) if(!(x)) __debugbreak();

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);

class Renderer
{
private:
	std::vector<unsigned int> m_DynamicallyBatchedTypes;
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void DynamicBatchRender(glm::mat4 proj, glm::mat4 view, const std::vector<GameObject*>& gameObjects);
	void Clear() const;

	inline void AddTypeForDynamicallyBatchedRendering(unsigned int type) 
		{ m_DynamicallyBatchedTypes.push_back(type);  }
};