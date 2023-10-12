#pragma once
#include "Component.h"
#include <glm.hpp>

class Shader;

struct QuadUVCoords
{
	glm::vec2 lL;
	glm::vec2 rL;
	glm::vec2 rU;
	glm::vec2 lU;

};




class QuadRenderer : public Component
{
private:
	QuadUVCoords m_TexCoords;
	unsigned int m_TextureId;
	Shader* m_Shader;
	GameObject* m_Owner;
public:
public:
	QuadRenderer(GameObject* owner);
	~QuadRenderer();

	virtual void Update() override;
	inline void SetTextureId(unsigned int textureId) { m_TextureId = textureId; }
	inline unsigned int GetTextureId() const { return m_TextureId; }

	void SetTexCoordsByAtlasIndex(unsigned int atlasIdx, unsigned int atlasWidth, unsigned int atlasHeight);
	inline void SetTextureCoords(QuadUVCoords texCoords) { m_TexCoords = texCoords; }
	inline QuadUVCoords GetTextureCoords() const { return m_TexCoords; }

	void AssignShader(Shader* shader);
	inline Shader* GetShader() { return m_Shader; }
};