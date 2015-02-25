#pragma once

#include <vector>
#include <type_traits>

using std::vector;

class SortingBase
{
public:
	
	virtual void Run(vector<int>&) = 0;
};
