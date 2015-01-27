#pragma once

#include <vector>
#include <iostream>

#include "../Abstractions/SortingBase.h"

class InsertionSort : SortingBase
{

public:

	void Run(vector<int>& vec) override;

	void DoSort(vector<int>& arr, int begin, int end);
};
