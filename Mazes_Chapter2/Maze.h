#pragma once
#include "Grid.h"

class Maze
{
public:
	Maze(Grid* grid);
	~Maze();

protected:
	Grid* _grid;

	virtual void Create_Maze() = 0;
};

