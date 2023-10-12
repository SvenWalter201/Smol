#pragma once
#include <vector>
#include <string>
class Player;
class Cell;

class Level
{
public:
	Level();
	Level(int width);

	Player* playerRef;

	int width;
	int GetCurrentLevelLength();
	std::vector<Cell*> cells;
	void AddRow(std::string row);
	void Reverse();
	void ChangePlayerPosition(int newY, int newX);
	bool CheckPlayerInteraction();
	void Print();
	void DisplayCurrentSegment(int from, int to); //from = higher, to = lower
};