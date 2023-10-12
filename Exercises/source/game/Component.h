#pragma once

class GameObject;

class Component
{
protected:
	GameObject* m_Owner;
public:
	Component(GameObject* owner);
	virtual ~Component();
	virtual void Update();
};