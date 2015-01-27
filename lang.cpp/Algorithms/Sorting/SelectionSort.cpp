#include "SelectionSort.h"

void SelectionSort::Run(vector<int>& vec)
{
	DoSort(vec, 0, vec.size() - 1);

	return;
}

void SelectionSort::DoSort(vector<int>& arr, int beginPos, int endPos)
{
	int min_idx = 0;
	int tmp = 0;

	// We are done when boundaries are wrong
	if (beginPos >= endPos)
		return;

	for (int i = 0; i < arr.size(); i++)
	{
		// Take i value as new min
		min_idx = i;

		// Search for min value among remaining items
		for (int j = i + 1; j < arr.size(); j++)
		{
			if (arr[j] < arr[min_idx])
				// Save new index
				min_idx = j;
		}

		// If we found number less then min, do swap
		if (arr[i] != arr[min_idx])
		{
			tmp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = tmp;
		}
	}
}
