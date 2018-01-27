#include "stdafx.h"
#include "Sidewinder.h"
#include "Utilities.h"


/*Sidewinder Algorithm
Starting at the top left corner, run across each row, randomly link upwards or east. When linking upwards, the current grouping(run) of adjacent cells ends.
When the run ends, move into the next east tile without linking. Repeat the process until done.

Bias: The north corridor is always linked.
*/

Sidewinder::Sidewinder(Grid* grid) : Maze(grid)
{
	Create_Maze();
}


Sidewinder::~Sidewinder()
{
}

void Sidewinder::Create_Maze()
{
	auto atEasternBoundry = [](Cell* cell) {return cell->east == nullptr; };//if we're at a boundry, the cell wont have a neighbor in that direction
	auto atNorthernBoundry = [](Cell* cell) {return cell->north == nullptr; };
	auto shouldCloseRun = [atEasternBoundry, atNorthernBoundry](Cell* cell)
	{ return atEasternBoundry(cell) || (!atNorthernBoundry(cell) && Utilties::Random_Int(0, 2) == 2); };//if we're at the east boundry, or randomly deceided too

	for (size_t y = 0; y < _grid->Get_Column_Count(); y++)
	{
		vector<Cell*> run;

		for (size_t x = 0; x < _grid->Get_Row_Count(); x++)
		{
			Cell* currentCell = _grid->Get_Matrix()->operator()(x, y);
			run.push_back(currentCell);

			if (shouldCloseRun(currentCell))
			{
				Cell* member = run.at(Utilties::Random_Int(0, run.size() - 1));//choose a random cell to link upwards to
				member->Link(member->north);
				run.clear();//since we went north, we clear the run and start over again
			}
			else//cant link upwards, so move to the east
				currentCell->Link(currentCell->east);
		}
	}

}
