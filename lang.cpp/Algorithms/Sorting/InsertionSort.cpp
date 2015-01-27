#include "InsertionSort.h"

void InsertionSort::Run(vector<int>& vec)
{
	DoSort(vec, 0, vec.size() - 1);

	return;
}

void InsertionSort::DoSort(vector<int>& arr, int beginPos, int endPos)
{
	int next = 0;
	int j = 0;

	// We are done when boundaries are wrong
	if (beginPos >= endPos)
		return;

	// Loop over all items excluding first one
	for (int i = 1; i < arr.size(); i++)
	{
		// Extract next item
		next = arr[i];

		// <j> determines the starting point for inner loop
		j = i;

		// Transit items in sorting part of the array that greater than <next> to the right
		while (j > 0 && next < arr[j - 1])
		{
			arr[j] = arr[j - 1];
			j--;
		}

		// Insert <next> item
		arr[j] = next;
	}
}
