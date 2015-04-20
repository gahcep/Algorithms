#pragma once
#include <iostream>
#include "../Abstractions/TypePredicates.h"
#include "../Trees/BinaryHeap.hpp"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(HeapSort)

template <class Cont>
struct HeapSort
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
		sort(container, 0, container.size() - 1);
	}

private:

	auto sort(Cont& container, typename Cont::value_type beginPos, typename Cont::value_type endPos) -> void
	{
		bool swapped = false;

		// We are done when boundaries are wrong
		if (beginPos >= endPos)
			return;

		size_t len = container.size();

		Heap<Cont> binary_heap;
		binary_heap.make_heap(container);

		container.clear();
		while (!binary_heap.empty())
		{
			std::cout << binary_heap.get_min() << std::endl;
			container.push_back(binary_heap.extract_min());
		}
	}
};
