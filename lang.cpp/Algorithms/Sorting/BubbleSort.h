#pragma once
#include "../Abstractions/TypePredicates.h"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(BubbleSort)

template <class Cont>
struct BubbleSort
{
	// Check that container type provided
	static_assert(HasConstIterator<Cont>::value, "Please provide a valid container type with const iterator");

	// Check that value_type of a container is of integral type
	static_assert(HasArithmeticType<Cont>::value, "Container's elements should be of integral type");

	auto run(Cont& container) -> void
	{
		sort(container);
	}

private:

	auto sort(Cont& container) -> void
	{
		bool swapped = false;

		size_t len = container.size();

		// i = 0:len
		for (size_t i = 0; i < len; i++)
		{
			// j = 0:len-i
			for (size_t j = 0; j < len - i - 1; j++)
			{
				if (container[j] > container[j + 1])
				{
					std::swap(container[j], container[j + 1]);
					swapped = true;
				}
			}

			// If there was no swap - we done
			if (!swapped) break;
		}
	}
};
