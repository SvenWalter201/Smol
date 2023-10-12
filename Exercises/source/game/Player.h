#pragma once
#include "Component.h"


class Player : public Component
{

public:
	Player(GameObject* owner);
	~Player();

	virtual void Update() override;
};