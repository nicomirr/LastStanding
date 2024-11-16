#include "MathsPlus.h"

int MathsPlus::Lerp(int start, int end, float t)
{
	return static_cast<int> (start + (end - start) * t);
}