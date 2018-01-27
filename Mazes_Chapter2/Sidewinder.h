#pragma once
#include "Maze.h"

class Sidewinder : public Maze
{
public:
	Sidewinder(Grid* grid);
	~Sidewinder();

private:
	virtual void Create_Maze() override;
};

