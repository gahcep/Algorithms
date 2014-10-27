#include "MergeSort.h"
#include <cmath>
#include <iterator>

using namespace std;

void MergeSort::Run(vector<int>& vec)
{
	auto new_vec = SortAndMerge(vec, 0, vec.size() - 1);

	return;
}

vector<int> MergeSort::SortAndMerge(vector<int> arrInput, int beginPos, int endPos)
{
	if (arrInput.size() == 1)
		return arrInput;

	if (arrInput.size() == 2)
	{
		if (arrInput[0] > arrInput[1])
			swap(arrInput[0], arrInput[1]);

		return arrInput;
	}
	
	int midPos = (int)(arrInput.size() / 2);
	
	vector<int> inSub1(midPos);
	vector<int> inSub2(arrInput.size() - midPos);

	std::copy(arrInput.begin(), arrInput.begin() + midPos, inSub1.begin());
	std::copy(arrInput.begin() + midPos, arrInput.end(), inSub2.begin());
	
	// Halving input array
	auto sub1 = SortAndMerge(inSub1, 0, midPos - 1);
	auto sub2 = SortAndMerge(inSub2, midPos, arrInput.size() - 1);

	// Combine sorted arrays
	return Combine(sub1, sub2);
}

vector<int> MergeSort::Combine(vector<int> sub1, vector<int> sub2)
{
	vector<int> output;

	auto len = sub1.size() + sub2.size();
	output.reserve(len);

	int i = 0, j = 0;
	while ((i < sub1.size()) || (j < sub2.size()))
	{
		if (i == sub1.size())
		{
			while (j < sub2.size())
				output.push_back(sub2[j++]);
			break;
		};

		if (j == sub2.size())
		{
			while (i < sub1.size())
				output.push_back(sub1[i++]);
			break;
		};

		if (sub1[i] < sub2[j])
			output.push_back(sub1[i++]);
		else
			output.push_back(sub2[j++]);
	}

	return output;
}