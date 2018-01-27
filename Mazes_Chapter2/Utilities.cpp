#include "stdafx.h"
#include "Utilities.h"

int Utilties::Random_Int(int min, int max)
{
	random_device seed;
	mt19937 PRNG(seed());

	uniform_int_distribution<int> range_distribution(min, max);

	return range_distribution(PRNG);

}
