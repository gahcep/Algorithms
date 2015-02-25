#pragma once
#include "../Abstractions/TypePredicates.h"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(SelectionSort)

template <class Cont>
struct SelectionSort
{
	// Check that container type provided
	static_assert(HasConstIterator<Cont>::value, "Please provide a container type");

	// Check that value_type of a container is of integral type
	static_assert(HasArithmeticType<Cont>::value, "Container's elements should be of integral type");

	auto run(Cont & container) -> void
	{
		sort(container, 0, container.size() - 1);
	}

private:

	auto sort(Cont & container, typename Cont::value_type beginPos, typename Cont::value_type endPos) -> void
	{
		Cont::value_type min_idx = 0;
		Cont::value_type tmp = 0;

		// We are done when boundaries are wrong
		if (beginPos >= endPos)
			return;

		size_t len = container.size();

		for (int i = 0; i < len; i++)
		{
			// Take i value as new min
			min_idx = i;

			// Search for min value among remaining items
			for (int j = i + 1; j < len; j++)
			{
				if (container[j] < container[min_idx])
					// Save new index
					min_idx = j;
			}

			// If we found number less then min, do swap
			if (container[i] != container[min_idx])
			{
				tmp = container[i];
				container[i] = container[min_idx];
				container[min_idx] = tmp;
			}
		}
	}
};
