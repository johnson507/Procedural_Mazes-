#pragma once
#include "Grid.h"
#include "Maze.h"

class BinaryTree_Maze : public Maze
{
public:
	BinaryTree_Maze(Grid* grid);
	~BinaryTree_Maze();

private:
	virtual void Create_Maze() override;
};

