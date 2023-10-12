#include "GameObject.h"
#include "Component.h"
#include "QuadRenderer.h"

GameObject::GameObject(unsigned int gameObjectId) : m_GameObjectId(gameObjectId), m_QuadRenderer(nullptr), m_Translation(glm::vec3())
{
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		delete m_Components[i];
	}

	if (m_QuadRenderer != nullptr)
		delete m_QuadRenderer;
}

void GameObject::AddComponent(Component* newComponent)
{
	m_Components.push_back(newComponent);
}


void GameObject::UpdateComponents()
{
	for (auto& component : m_Components)
	{
		component->Update();
	}
}

