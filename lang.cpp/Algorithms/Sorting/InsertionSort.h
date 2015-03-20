#pragma once
#include "../Abstractions/TypePredicates.h"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(InsertionSort)

template <class Cont>
struct InsertionSort
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
		Cont::value_type next = 0;
		size_t j = 0;

		// We are done when boundaries are wrong
		if (beginPos >= endPos)
			return;

		size_t len = container.size();

		// Loop over all items excluding first one
		for (size_t i = 1; i < len; i++)
		{
			// Extract next item
			next = container[i]; // i is the same as j

			// <j> determines the starting point for inner loop
			j = i;

			// Transit items in sorting part of the array that greater than <next> to the right
			while (j > 0 && next < container[j - 1])
			{
				// Shifting item in the sorted part of the array one position right 
				// We don't care about value in container[j], because it's saved in <next> variable
				container[j] = container[j - 1];
				j--;
			}

			// Insert <next> item
			container[j] = next;
		}
	}
};
