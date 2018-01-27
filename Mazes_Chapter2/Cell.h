#include <vector>
#include <map>

using namespace std;
class Distances;

#pragma once
class Cell
{
public:
	Cell(int x, int y);
	~Cell();

	void Link(Cell* linkToCell);

	void Unlink(Cell* unlinkCell);

	bool Check_IfLinked(Cell* cellToCheck);
	vector<Cell*>::iterator Find_LinkedCell(Cell * cellToCheck);
	Distances Distance();

	Cell* north = nullptr;
	Cell* south = nullptr;
	Cell* east = nullptr;
	Cell* west = nullptr;

	//Getters
#pragma region Getters

	//char* Get_Vector()
	//{
	//	return "(" + _row + "," + _column + ")";
	//}

	int Get_Row() const
	{
		return _x;
	}
	int Get_Column() const
	{
		return _y;
	}

	vector<Cell*>* Get_LinkedCells() const
	{
		return _linked_Cells;
	}
	vector<Cell*>* Get_NeighborCells() const
	{
		return _neighbor_Cells;
	}

#pragma endregion

private:
	int _x;
	int _y;

	vector<Cell*>* _neighbor_Cells = nullptr;
	vector<Cell*>* _linked_Cells = nullptr;
};

class Distances
{
public:
	Distances(Cell* root);
	~Distances();


	vector<Cell*>* Get_Cells();//returns the keys of the map

	float operator[](Cell* index);//returns the distance of a cell from the root

	void Set_Cell(Cell* cell, float distance);

	bool Contains_Cell(Cell* cell);
	Distances Find_ShortestPath(Cell* goal);
	map<Cell*, float>::iterator Find_FurthestCell();

private:
	map<Cell*, float> _cells;//maps the cell to its distance from the root cell
	Cell* _root;
};