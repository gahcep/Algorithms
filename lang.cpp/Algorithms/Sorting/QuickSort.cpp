#include "QuickSort.h"

void QuickSort::Run(vector<int>& vec)
{
	DoSort(vec, 0, vec.size() - 1);

	return;
}

void QuickSort::DoSort(vector<int>& arr, int beginPos, int endPos)
{
	// We are done when boundaries are wrong
	if (beginPos >= endPos)
		return;
	int pivotPos = Partition(arr, beginPos, endPos);
	DoSort(arr, beginPos, pivotPos -1);
	DoSort(arr, pivotPos + 1, endPos);
}

int QuickSort::Partition(vector<int>& arr, int left, int rigth)
{
	int i = left;
	int j = rigth + 1;

	int pivot = arr[left];

	// Pivot is first element
	while (true)
	{
		// Run from left to right looking values greater than our Pivot
		while (arr[++i] < pivot)
		{
			// Reach the end?
			if (i == rigth)
				break;
		}

		// Look for values less than initial element (pivot)
		while (arr[--j] > pivot)
		{
			// Reach the begining?
			if (j == left)
				break;
		}

		// Do we need to do anything?
		if (i >= j)
			break;

		// Exchange items variables i and j point to
		int tmp = arr[j];
		arr[j] = arr[i];
		arr[i] = tmp;
	}

	arr[left] = arr[j];
	arr[j] = pivot;

	// Take j as Pivot Position
	return j;
}