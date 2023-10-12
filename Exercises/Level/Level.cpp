#include <algorithm>
#include "Level.h"
#include <iostream>
#include "Cell.h"
#include "../Utility/Log.h"
#include "../Player/Player.h"

Level::Level()
{
	cells = std::vector<Cell*>();
}

Level::Level(int width) : width(width)
{
	cells = std::vector<Cell*>();
}

int Level::GetCurrentLevelLength()
{
	return cells.size();
}

void Level::AddRow(std::string row)
{
	Cell* r = new Cell[width];
	for (size_t i = 0; i < width; i++)
	{
		Cell c = Cell(row[i]);
		r[i] = c;
	}
	cells.push_back(r);
}

void Level::Reverse()
{
	std::reverse(cells.begin(), cells.end());
}

void Level::ChangePlayerPosition(int newY, int newX)
{
	if (playerRef->locationY != -1)
	{
		cells[playerRef->locationY][playerRef->locationX].playerOccupied = false;
	}
	playerRef->locationY = newY;

	//clamp newX to bounds of level
	newX = std::max(std::min(newX, width - 1), 0);

	playerRef->locationX = newX;
	cells[newY][newX].playerOccupied = true;
}

bool Level::CheckPlayerInteraction()
{
	Cell cell = cells[playerRef->locationY][playerRef->locationX];
	switch (cell.content)
	{
	case CellContent::Gem:
		playerRef->score++;
		return true;
	case CellContent::Stone:
		return false;
	}
	return true;
}

void Level::Print()
{
	for (size_t y = 0; y < cells.size(); y++)
	{
		Cell* row = cells[y];
		for (size_t x = 0; x < width; x++)
		{
			std::cout << row[x].symbol << " ";
		}

		std::cout << std::endl;
	}
}

void Level::DisplayCurrentSegment(int highEnd, int lowEnd)
{
	int overflow = highEnd - (GetCurrentLevelLength() - 1);
	if (overflow > 0)
	{
		for (size_t i = 0; i < overflow; i++)
		{
			for (size_t x = 0; x < width; x++)
			{
				std::cout << "..";
			}
			std::cout << std::endl;
		}
		highEnd -= overflow;
	}


	for (int y = highEnd; y >= lowEnd; y--)
	{
		//Log(std::to_string(y));
		Cell* row = cells[y];

		for (size_t x = 0; x < width; x++)
		{
			std::cout << row[x].GetSymbol() << " ";
		}

		std::cout << std::endl;



	}
	for (size_t x = 0; x < width; x++)
	{
		std::cout << "__";
	}
	std::cout << std::endl;
}
