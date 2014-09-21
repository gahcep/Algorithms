#include <iostream>
#include <vector>
#include <memory>

#include "../Algorithms/Sorting/QuickSort.h"

using namespace std;

int main(int argc, char** argv)
{
	vector<int> vec{ 4, 7, 22, 5, 1, 9, 3, 87, 24, 7, 4, 3, 67, 12, 67, 23, 78, 45 };
	
	// QuickSort
	auto qsort = unique_ptr<QuickSort>(new QuickSort());
	qsort.get()->Run(vec);
}