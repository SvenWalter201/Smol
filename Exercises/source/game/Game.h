#pragma once
#include <vector>

class GameObject;
class Level;
class InputHandler;

class Game
{
private:
	Level* m_Level;
	InputHandler* m_Input;
	std::vector<GameObject*> m_GameObjects;
	float m_DeltaTime = 0.0f;

public:
	Game();
	~Game();
	void SetCurrentLevel(Level& level);
	void Setup();
	void Update();
	inline std::vector<GameObject*> GetGameObjects() { return m_GameObjects; }
};

