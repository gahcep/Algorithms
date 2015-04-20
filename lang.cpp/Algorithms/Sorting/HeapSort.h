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
		sort(container);
	}

private:

	auto sort(Cont& container) -> void
	{
		bool swapped = false;

		size_t len = container.size();

		Heap<Cont> binary_heap;
		binary_heap.make_heap(container);

		container.clear();
		while (!binary_heap.empty())
			container.push_back(binary_heap.extract_min());
	}
};
