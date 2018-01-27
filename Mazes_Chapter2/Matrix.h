#include <vector>

using namespace std;

#pragma once

template<class T>
class Matrix
{
public:

	Matrix(int rows, int columns)
	{
		_dataList = new vector<T*>();

		_rows = rows;
		_columns = columns;

		T* newData = nullptr;

		for (size_t x = 0; x < rows; x++)
		{
			for (size_t y = 0; y < columns; y++)
			{
				newData = new T(x, y);//MAKE GENERIC!

				_dataList->push_back(newData);
			}
		}

	};

	~Matrix()
	{	//delete the items in the data and the pointers
		for (size_t i = 0; i < _dataList->size(); i++)
		{
			delete	_dataList->at(i);
			_dataList->at(i) = nullptr;
		}

		delete _dataList;
	};

	typename vector<T*>::iterator begin() { return _dataList->begin(); }
	typename vector<T*>::iterator end() { return _dataList->end(); }

	T* operator()(int x, int y) { return Find_By_Index(x, y); }

private:
	vector<T*>* _dataList;

	int _rows;
	int _columns;

	T* Find_By_Index(int x, int y)
	{
		if ((x < 0 || y < 0) || (x >= _rows || y >= _columns))
			return nullptr;

		int index = (x * _columns) + y;

		return  _dataList->at(index);
	}

};

