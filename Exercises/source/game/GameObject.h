#pragma once
#include <vector>
#include <glm.hpp>
#include <unordered_map>
#include <string>

class QuadRenderer;
class Component;

class GameObject
{
private:
	std::vector<Component*> m_Components;
	unsigned int m_GameObjectId;
	QuadRenderer* m_QuadRenderer;

protected:
	glm::vec3 m_Translation;
public:
	GameObject(unsigned int gameObjectId);
	~GameObject();

	void AddComponent(Component* newComponent);
	void UpdateComponents();

	inline unsigned int GetGameObjectId() const { return m_GameObjectId; }

	inline glm::vec3 GetTranslation() const { return m_Translation; }
	inline void SetTranslation(glm::vec3 translation) {
		m_Translation = translation; 
	}

	inline void SetQuadRenderer(QuadRenderer* quadRenderer) { m_QuadRenderer = quadRenderer; }
	inline QuadRenderer* GetQuadRenderer() const {
		return m_QuadRenderer;
	}

};