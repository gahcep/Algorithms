#pragma once

#include <vector>
#include <iostream>

#include "../Abstractions/SortingBase.h"

class SelectionSort : SortingBase
{

public:

	void Run(vector<int>& vec) override;

	void DoSort(vector<int>& arr, int begin, int end);
};
