#pragma once

#include "Cell.h"
#include "Matrix.h"
#include <string>

using namespace std;


class Grid
{
public:
	Grid(int rows, int columns);
	~Grid();

	Cell* Find_Random_Cell();
	string Print_Grid();

	//string operator>>() {};

#pragma region  Getters

	int Get_Size() const
	{
		return _column_Count * _row_Count;
	}

	int Get_Column_Count() const
	{
		return _column_Count;
	}
	int Get_Row_Count() const
	{
		return _row_Count;
	}

	Matrix<Cell>* Get_Matrix()
	{
		return matrix;
	}

#pragma endregion


private:

	Matrix<Cell>* matrix = nullptr;

	int _column_Count;
	int _row_Count;

	void Prepare_Grid();
	void Configure_Cells();

	virtual string Cell_Contents(Cell* cell);
};


class Distances_Grid : public Grid
{
public:
	Distances_Grid(int rows, int columns);
	~Distances_Grid();

	Distances* distances = nullptr;

private:
	virtual string Cell_Contents(Cell* cell) override;

};