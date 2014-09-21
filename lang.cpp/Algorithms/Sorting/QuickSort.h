#pragma once

#include <vector>
#include <iostream>

#include "../Abstractions/SortingBase.h"

using namespace std;

class QuickSort : SortingBase
{

public:

	void Run(vector<int>& vec) override;

	//void Print() const override;

	void DoSort(vector<int>& arr, int begin, int end);

	int Partition(vector<int>& arr, int beginPos, int endPos);
};