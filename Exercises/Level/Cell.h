#pragma once

enum class CellContent
{
	Empty,
	Stone,
	Gem
};

class Cell
{

public:
	Cell();
	Cell(char symbol);
	char symbol;
	CellContent content;
	bool playerOccupied = false;
	char GetSymbol();
};
