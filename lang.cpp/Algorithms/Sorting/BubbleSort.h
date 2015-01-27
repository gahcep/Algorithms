#pragma once

#include <vector>
#include <iostream>

#include "../Abstractions/SortingBase.h"

class BubbleSort : SortingBase
{

public:

	void Run(vector<int>& vec) override;

	void DoSort(vector<int>& arr, int begin, int end);

	void DoSortOptimized(vector<int>& arr, int begin, int end);
};

