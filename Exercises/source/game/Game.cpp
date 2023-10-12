#include "Game.h"
#include "../../Level/Level.h"
#include "../input/Input.h"
#include "GameObject.h"
#include "QuadRenderer.h"
#include "Player.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include <iostream>

Game::Game() : m_Level(nullptr), m_Input(nullptr), m_GameObjects(std::vector<GameObject*>()), m_DeltaTime(0)
{
}

Game::~Game()
{
	//delete all gameobjects
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		delete m_GameObjects[i];
	}

	delete m_Input;
	//delete the level
}

void Game::SetCurrentLevel(Level& level)
{
	this->m_Level = &level;
}

void Game::Setup()
{
	//load level
	//load all game objects needed

	m_Input = new InputHandler();

	Shader* shader = new Shader("../../../../Exercises/resources/shaders/basic.shader");
	shader->Bind();
	Texture* texture = new Texture("../../../../Exercises/resources/textures/Gem.png");
	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);

	for (size_t i = 0; i < 20; i++)
	{
		GameObject* gO = new GameObject(0);
		int xPos = i - 10;
		gO->SetTranslation(glm::vec3(xPos, 0, 0));
		QuadRenderer* qR = new QuadRenderer(gO);
		qR->AssignShader(shader);
		gO->SetQuadRenderer(qR);
		m_GameObjects.push_back(gO);
	}

	//setup player
	{
		GameObject* playerGO = new GameObject(0);
		playerGO->SetTranslation(glm::vec3(0, 0, 0));
		QuadRenderer* qR = new QuadRenderer(playerGO);
		qR->AssignShader(shader);
		playerGO->SetQuadRenderer(qR);
		Player* player = new Player(playerGO);
		playerGO->AddComponent(player);
		m_GameObjects.push_back(playerGO);
	}
}

void Game::Update()
{
	for(int i = m_GameObjects.size() - 1; i >= 0; i--)
	{
		m_GameObjects[i]->UpdateComponents();
	}

	//update all gameobjects in a loop


}