#pragma once

#include <vector>

using namespace std;

class SortingBase
{
public:
	
	virtual void Run(vector<int>&) = 0;

	//virtual void Print() const = 0;
};