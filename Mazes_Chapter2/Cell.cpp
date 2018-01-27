#include "stdafx.h"
#include "Cell.h"
#include <algorithm>

Cell::Cell(int x, int y)
{
	_x = x;
	_y = y;
	_linked_Cells = new vector<Cell*>();
	_neighbor_Cells = new vector<Cell*>();
}


Cell::~Cell()
{
	//delete all the pointers BUT not the data

	vector<Cell*>::iterator it = _linked_Cells->begin();

	while (it != _linked_Cells->end())
	{
		*it = nullptr;
		++it;
	}

	it = _neighbor_Cells->begin();

	while (it != _neighbor_Cells->end())
	{
		*it = nullptr;
		++it;
	}

	delete _linked_Cells;
	delete _neighbor_Cells;
}

void Cell::Link(Cell * linkToCell)
{
	if (linkToCell == nullptr)
		return;//we cant link to nothing.

	if (!Check_IfLinked(linkToCell))//doesnt contain, then add
		_linked_Cells->push_back(linkToCell);//link new cell to the main cell

	if (!linkToCell->Check_IfLinked(this))
		linkToCell->_linked_Cells->push_back(this);//link main cell to the new cell
}

void Cell::Unlink(Cell * unlinkCell)
{
	vector<Cell*>::iterator mainIt = Find_LinkedCell(unlinkCell);

	if (Check_IfLinked(unlinkCell))// contains the cell to break linkage to
		_linked_Cells->erase(mainIt);//unlink input cell to the main cell


	mainIt = unlinkCell->Find_LinkedCell(this);

	if (unlinkCell->Check_IfLinked(this))
		unlinkCell->_linked_Cells->erase(mainIt);//unlink main cell to the input cell
}

//Return a bool if the input cell is linked to the this cell
bool Cell::Check_IfLinked(Cell * cellToCheck)
{
	return Find_LinkedCell(cellToCheck) == _linked_Cells->end() ? false : true;//if we went to end, then not linked
}

//Return an iterator to the input cell that is linked to this cell
vector<Cell*>::iterator Cell::Find_LinkedCell(Cell * cellToCheck)
{
	return	find(_linked_Cells->begin(), _linked_Cells->end(), cellToCheck);
}

Distances Cell::Distance()
{
	Distances distances(this);//stores all distances relative 
	vector<Cell*> frontier = { this };//the open list of cells

	while (frontier.size() > 0)
	{
		vector<Cell*> new_Frontier;//the unvisited cells linked to the current cells in the frontier

		for (auto it = frontier.begin(); it != frontier.end(); ++it)
		{
			Cell* currentCell = *it;

			for (auto linkedCell = currentCell->Get_LinkedCells()->begin(); linkedCell != currentCell->Get_LinkedCells()->end(); ++linkedCell)
			{
				if (distances.Contains_Cell(*linkedCell))
					continue;
				else
				{
					distances.Set_Cell(*linkedCell, distances[currentCell] + 1);
					new_Frontier.push_back(*linkedCell);
				}
			}
		}

		frontier = new_Frontier;
	}

	return distances;
}

Distances::Distances(Cell* root)
{
	_root = root;
	_cells[root] = 0;
}

Distances::~Distances()
{
}

vector<Cell*>* Distances::Get_Cells()
{
	vector<Cell*> keys;

	for (auto it = _cells.begin(); it != _cells.end(); it++)
		keys.push_back(it->first);

	return &keys;
}

float Distances::operator[](Cell* index)
{
	return _cells[index];
}

bool Distances::Contains_Cell(Cell* cell)
{
	if (_cells.find(cell) == _cells.end())//doesnt exist 
		return false;
	else//exists
		return true;
}

Distances Distances::Find_ShortestPath(Cell * goal)
{
	Cell* current = goal;
	Distances path(_root);//the root of the distances class this function is in
	path.Set_Cell(current, _cells[current]);

	while (current != _root)
	{
		for (auto linkedNeighborCell = current->Get_LinkedCells()->begin(); linkedNeighborCell != current->Get_LinkedCells()->end(); ++linkedNeighborCell)
		{
			if (_cells[*linkedNeighborCell] < _cells[current])
			{
				path.Set_Cell(*linkedNeighborCell, _cells[*linkedNeighborCell]);
				current = *linkedNeighborCell;
				break;
			}
		}
	}

	return path;
}

map<Cell*, float>::iterator Distances::Find_FurthestCell()
{
	float max_Distance = 0;
	map<Cell*, float>::iterator max_Cell;
	map<Cell*, float>::iterator pair;

	for (pair = _cells.begin(); pair != _cells.end(); ++pair)
	{
		if (pair->second > max_Distance)
		{
			max_Cell = pair;
			max_Distance = pair->second;
		}
	}


	return max_Cell;
}

void Distances::Set_Cell(Cell * cell, float distance)
{
	_cells[cell] = distance;
}
