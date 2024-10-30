#pragma once
#include <iostream>

struct RandomNum
{	
	static int RandomRange(int minInclusive, int maxInclusive)
	{
		return minInclusive + (rand() % (maxInclusive - minInclusive + 1));
	}
};

