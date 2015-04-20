#pragma once
#include "../Abstractions/TypePredicates.h"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(MergeSort)

template <class Cont>
struct MergeSort
{
	// Check that container type provided
	static_assert(HasConstIterator<Cont>::value, "Please provide a valid container type with const iterator");

	// Check that value_type of a container is of integral type
	static_assert(HasArithmeticType<Cont>::value, "Container's elements should be of integral type");

	// Check that container has random access iterator
	static_assert(HasRandomAccessIterator<Cont>::value,
		"Please provide a valid container type with random access iterator");

	auto run(Cont& container) -> void
	{
		auto result = SortAndMerge(container, 0, container.size() - 1);
		std::swap(container, result);
	}

private:

	auto SortAndMerge(Cont& container, typename Cont::value_type beginPos, typename Cont::value_type endPos) -> Cont
	{
		if (container.size() == 1)
			return container;

		if (container.size() == 2)
		{
			if (container[0] > container[1])
				std::swap(container[0], container[1]);

			return container;
		}

		size_t midPos = (size_t)(container.size() / 2);

		Cont inSub1(midPos);
		Cont inSub2(container.size() - midPos);

		std::copy(container.begin(), container.begin() + midPos, inSub1.begin());
		std::copy(container.begin() + midPos, container.end(), inSub2.begin());

		// Halving input array
		auto sub1 = SortAndMerge(inSub1, 0, midPos - 1);
		auto sub2 = SortAndMerge(inSub2, midPos, container.size() - 1);

		// Combine sorted arrays
		return Combine(sub1, sub2);
	}

	auto Combine(Cont sub1, Cont sub2) -> Cont
	{
		Cont output;

		auto len = sub1.size() + sub2.size();
		output.reserve(len);

		size_t i = 0, j = 0;
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
};

