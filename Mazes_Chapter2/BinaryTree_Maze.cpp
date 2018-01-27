#include "stdafx.h"
#include "BinaryTree_Maze.h"
#include "Utilities.h"


/* Binary Tree Algorithm
Starting at the top left corner, go across each row, and randomly choose to link either the north cell or the east cell.

Bias: The North and East boundries are always perfectly connected.
*/


BinaryTree_Maze::BinaryTree_Maze(Grid* grid) : Maze(grid) 
{
	Create_Maze();
}


BinaryTree_Maze::~BinaryTree_Maze()
{
}

void BinaryTree_Maze::Create_Maze()
{
	for (size_t x = 0; x < _grid->Get_Row_Count(); x++)//Iterate through every cell
	{
		for (size_t y = 0; y < _grid->Get_Column_Count(); y++)
		{
			Cell* currentCell = _grid->Get_Matrix()->operator()(x, y);//Get the current cell via its index through the matrix
			vector<Cell*>* neighbors = currentCell->Get_NeighborCells();//the current cell's neighbors

			if (currentCell->north != nullptr)
				neighbors->push_back(currentCell->north);
			if (currentCell->east != nullptr)
				neighbors->push_back(currentCell->east);

			if (neighbors->size() > 0)
				currentCell->Link(neighbors->at(Utilties::Random_Int(0, neighbors->size() - 1)));//choose a random cell to link to
		}
	}

}

