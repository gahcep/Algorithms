#include "BubbleSort.h"

void BubbleSort::Run(vector<int>& vec)
{
	DoSort(vec, 0, vec.size() - 1);

	return;
}

void BubbleSort::DoSort(vector<int>& arr, int beginPos, int endPos)
{
	bool swapped = false;

	// We are done when boundaries are wrong
	if (beginPos >= endPos)
		return;
	
	size_t len = arr.size();

	// i = 0:len
	for (int i = 0; i < len; i++)
	{
		// j = 0:len-i
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				swapped = true;
			}
		}

		// If there was no swap - we done
		if (!swapped) break;
	}
}
