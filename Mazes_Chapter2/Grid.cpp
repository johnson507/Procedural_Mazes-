#include "stdafx.h"
#include "Grid.h"
#include <algorithm>
#include "Utilities.h"

Grid::Grid(int rows, int columns)
{
	_row_Count = rows;
	_column_Count = columns;

	Prepare_Grid();
	Configure_Cells();
}


Grid::~Grid()
{
}

Cell * Grid::Find_Random_Cell()
{
	int rand_x = Utilties::Random_Int(0, _row_Count);
	int rand_y = Utilties::Random_Int(0, _column_Count);

	return matrix->operator()(rand_x, rand_y);
}

string Grid::Print_Grid()
{
	//Generate the upper boundry
	string result = string("+");

	for (size_t i = 0; i < _row_Count; i++)
		result += "---+";

	result += "\n";

	for (size_t y = 0; y < _column_Count; y++)
	{
		string top = "|";//starting at far left, so always a wall
		string bottom = "+";

		for (size_t x = 0; x < _row_Count; x++)
		{
			Cell* currentCell = matrix->operator()(x, y);

			if (currentCell == nullptr)
				continue;

			string body = Cell_Contents(currentCell);
			string east_boundry = currentCell->Check_IfLinked(currentCell->east) ? " " : "|";//if linked to east, then dont build wall

			top += body + east_boundry;//the corridor of the cell

			string south_boundry = currentCell->Check_IfLinked(currentCell->south) ? "   " : "---";//a floor
			string corner = "+";

			bottom += south_boundry + corner;
		}

		result += top + "\n";
		result += bottom + "\n";
	}

	return result;
}


void Grid::Prepare_Grid()
{
	matrix = new Matrix<Cell>(_row_Count, _column_Count);
}

void Grid::Configure_Cells()
{
	auto set_neighbors = [this](auto currentCell)
	{
		int x = currentCell->Get_Row();
		int y = currentCell->Get_Column();

		currentCell->north = matrix->operator()(x, y - 1);
		currentCell->south = matrix->operator()(x, y + 1);
		currentCell->west = matrix->operator()(x - 1, y);
		currentCell->east = matrix->operator()(x + 1, y);
	};


	for_each(matrix->begin(), matrix->end(), set_neighbors);
}

string Grid::Cell_Contents(Cell * cell)
{
	return "   ";
}

Distances_Grid::Distances_Grid(int rows, int columns) : Grid(rows, columns)
{
}

Distances_Grid::~Distances_Grid()
{
}

string Distances_Grid::Cell_Contents(Cell * cell)
{
	string body = "   ";

	if (distances != nullptr)
	{
		string count = to_string(static_cast<int>(distances->operator[](cell)));

		if (count.size() > 1)
		{
			body.erase(body.size() - count.size());
			body.append(count);
		}
		else if (count != "0")
			body = " " + count + " ";
	}

	return body;
}
