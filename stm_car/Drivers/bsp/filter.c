

#include "filter.h"


float RCFilter(float data, float data_L, float p)
{
	return data * p + (1 - p) * data_L;
}

