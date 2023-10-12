#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>
#include "../game/GameObject.h"
#include "../game/QuadRenderer.h"
#include "VertexBuffer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	//Bind per Frame
	shader.Bind();
	va.Bind();
	ib.Bind();

	//Draw Call
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DynamicBatchRender(glm::mat4 proj, glm::mat4 view, const std::vector<GameObject*>& gameObjects)
{
	glm::mat4 mvp = proj * view;// *model;

		for (auto i : m_DynamicallyBatchedTypes)
		{
			int count = 0;
			for (const auto& gO : gameObjects)
			{
				if (i == gO->GetGameObjectId())
					++count;
			}

			if (count == 0)
				continue;

			std::vector<glm::vec2> vertices = std::vector<glm::vec2>(count * 8);
			std::vector<unsigned int> indices = std::vector<unsigned int>(count * 6);

			unsigned int positionArrayIndex = 0, indexArrayIndex = 0, vertexCounter = 0;
			Shader* shader = nullptr;

			for (const auto& gO : gameObjects)
			{
				if (i != gO->GetGameObjectId())
					continue;

				QuadRenderer* quadRenderer = gO->GetQuadRenderer();
				if(quadRenderer == nullptr)
				{
					std::cout << "Game Object was marked as dynamically batched, but does not contain a QuadRenderer" << std::endl;
					continue;
				}

				shader = quadRenderer->GetShader();
				if(shader == nullptr)
				{
					std::cout << "quadRenderer had no shader assigned to it" << std::endl;
					return;
				}

				QuadUVCoords quadTexCoords = quadRenderer->GetTextureCoords();

				glm::vec3 translation = gO->GetTranslation();
				vertices[positionArrayIndex++] = glm::vec2(-0.5f + translation.x, -0.5f + translation.y);
				vertices[positionArrayIndex++] = quadTexCoords.lL;
				vertices[positionArrayIndex++] = glm::vec2(0.5f + translation.x, -0.5f + translation.y);
				vertices[positionArrayIndex++] = quadTexCoords.rL;
				vertices[positionArrayIndex++] = glm::vec2(0.5f + translation.x, 0.5f + translation.y);
				vertices[positionArrayIndex++] = quadTexCoords.rU;
				vertices[positionArrayIndex++] = glm::vec2(-0.5f + translation.x, 0.5f + translation.y);
				vertices[positionArrayIndex++] = quadTexCoords.lU;
				indices[indexArrayIndex++] = vertexCounter + 0;
				indices[indexArrayIndex++] = vertexCounter + 1;
				indices[indexArrayIndex++] = vertexCounter + 2;
				indices[indexArrayIndex++] = vertexCounter + 2;
				indices[indexArrayIndex++] = vertexCounter + 3;
				indices[indexArrayIndex++] = vertexCounter + 0;
				vertexCounter += 4;
			}

			VertexBuffer vb(vertices.data(), vertexCounter * (2 + 2) * sizeof(float));
			IndexBuffer ib(indices.data(), indexArrayIndex);

			VertexArray va;
			VertexBufferLayout vbl;
			vbl.Push<float>(2);
			vbl.Push<float>(2);
			va.AddBuffer(vb, vbl);

			shader->Bind();
			shader->SetUniformMat4f("u_MVP", mvp);
			Draw(va, ib, *shader);
		}
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);

}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	//fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	//	(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	//	type, severity, message);
	if (type == GL_DEBUG_TYPE_OTHER /* && severity == GL_DEBUG_SEVERITY_LOW*/)
	{
		return;
	}

	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: " << message << std::endl;

	std::cout << "severity: ";
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;

	std::cout << "type: ";
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: " << id << std::endl;

	std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}
