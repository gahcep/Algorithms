#pragma once

#include <vector>
#include <iostream>

#include "../Abstractions/SortingBase.h"

using namespace std;

class MergeSort : SortingBase
{

public:
	
	void Run(vector<int>& vec) override;

	void DoSort(vector<int>& arr, int begin, int end);

	vector<int> SortAndMerge(vector<int> arrInput, int beginPos, int endPos);

	vector<int> Combine(vector<int> sub1, vector<int> sub2);
};

