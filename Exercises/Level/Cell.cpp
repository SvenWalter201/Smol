#include "Cell.h"
#include "../Utility/Log.h"

Cell::Cell() {}

Cell::Cell(char symbol) : symbol(symbol)
{
	switch (symbol)
	{
	case 'o':
		content = CellContent::Empty;
		break;
	case 'x':
		content = CellContent::Stone;
		break;
	case '^':
		content = CellContent::Gem;
		break;
	default:
		Log("unknown symbol");
		content = CellContent::Empty;
		break;
	}
}

char Cell::GetSymbol()
{
	if (playerOccupied)
		return 'Y';
	switch (content)
	{
	case CellContent::Empty:
		return ' ';
	case CellContent::Stone:
		return 'x';
	case CellContent::Gem:
		return '^';

	default:
		return 'H';
	}
}

