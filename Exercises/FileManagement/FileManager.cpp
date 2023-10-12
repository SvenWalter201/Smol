#include <fstream>
#include <string>
#include <iostream>
#include "FileManager.h"
#include "../Level/Level.h"

bool ReadLevel(const char* filepath, Level& level)
{
	std::cout << filepath << std::endl;
	std::fstream file;
	file.open(filepath, std::ios::in);
	if (file.is_open())
	{
		size_t width = 0;
		std::string line;
		while (std::getline(file, line))
		{
			//initialize width to length of first line
			if (width == 0)
			{
				width = line.length();
				level.width = width;
			}

			if (line.length() != width)
			{
				file.close();
				std::cout << "File has lines of differing lengths. Make sure, that every line has the same length" << std::endl;
				return false;
			}
			level.AddRow(line);
		}
		file.close();
		return true;
	}

	return false;
}