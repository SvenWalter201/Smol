#include "Player.h"
#include <iostream>

Player::Player(GameObject* owner) : Component(owner)
{
}

Player::~Player()
{
}

void Player::Update()
{
	//if (m_Input->GetKeyPressed('A'))
	//	std::cout << "AAAA" << std::endl;
	std::cout << "Player Update Called" << std::endl;
}
