// Mazes_Chapter2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cell.h"
#include "Grid.h"
#include <iostream>
#include "BinaryTree_Maze.h"
#include "Sidewinder.h"
#include <stdlib.h>

using namespace std;

void Display_LongestPath(Distances_Grid* grid);
void Display_All(Distances_Grid* grid);
void Display_ShortestPath(Distances_Grid* grid, int goalX, int goalY);
void Display_ClearGrid(Grid* grid);

int main()
{
	bool isLooping = true;
	string inputMaze = "";
	string inputCellBody = "";
	Grid* grid = nullptr;
	 

	while (isLooping)
	{
		//with numbers or not; longest path, shortest path

		cout << "CELL BODY TYPE\n\n[0] Clear Cells\n[1] All Distances\n[2] Shortest Path\n[3] Longest Path" << endl;
		cin >> inputCellBody;

		if (grid != nullptr)//clear the old grid
			delete grid;

		if (inputCellBody == "0")//normal grid
			grid = new Grid(12, 12);
		else if (inputCellBody == "1" || inputCellBody == "2" || inputCellBody == "3")//show the distances
			grid = new Distances_Grid(12, 12);


		system("cls");

		cout << "CHOOSE MAZE ALGORITHM\n\n[0] Binary Tree\n[1] Sidewider\n" << endl;
		cin >> inputMaze;


		if (inputMaze == "0")
			BinaryTree_Maze binaryTree_Maze(grid);
		else if (inputMaze == "1")
			Sidewinder sidewinder_Maze(grid);

		system("cls");

		if (inputCellBody == "0")
			Display_ClearGrid(grid);
		else if (inputCellBody == "1")
			Display_All(static_cast<Distances_Grid*>(grid));
		else if (inputCellBody == "2")
		{
			int goalX, goalY;
			cout << "Enter goal cell X coord: ";
			cin >> goalX;

			cout << "Enter goal cell Y coord: ";
			cin >> goalY;

			Display_ShortestPath(static_cast<Distances_Grid*>(grid), goalX, goalY);
		}
		else if (inputCellBody == "3")
			Display_LongestPath(static_cast<Distances_Grid*>(grid));
	}

	cin.get();
	cin.get();
	return 0;
}

void Display_ClearGrid(Grid* grid)
{
	cout << grid->Print_Grid() << endl;
}


void Display_All(Distances_Grid* grid)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances to be the node's 


	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}

void Display_ShortestPath(Distances_Grid* grid, int goalX, int goalY)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances to be the node's 


	grid->distances = &distances;

	distances = distances.Find_ShortestPath(grid->Get_Matrix()->operator()(goalX, goalY));
	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}

void Display_LongestPath(Distances_Grid* grid)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances

	auto new_start_It = distances.Find_FurthestCell();//from the starting cell
	Cell* new_start = new_start_It->first;//furthest cell from the original start cell
	float max_distance = new_start_It->second;

	distances = new_start->Distance();//calculate new distances from the furthest cell
	auto goal_It = distances.Find_FurthestCell();
	Cell* newGoal = goal_It->first;


	distances = distances.Find_ShortestPath(newGoal);//find the path to the furthest cell now
	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}

