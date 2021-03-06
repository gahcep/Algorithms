#pragma once
#include "../Abstractions/TypePredicates.h"

// Include in <HasProperAlgoType> type
PROPER_SORTING_ALGORITHM(QuickSort)

template <class Cont>
struct QuickSort
{
	// Check that container type provided
	static_assert(HasConstIterator<Cont>::value, "Please provide a container type");

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

	auto sort(Cont& container, long beginPos, long endPos) -> void
	{
		if (beginPos >= endPos)
			return;

		long pivotPos = Partition(container, beginPos, endPos);
		sort(container, beginPos, pivotPos - 1);
		sort(container, pivotPos + 1, endPos);
	}

	auto Partition(Cont& container, long left, long right) -> typename Cont::value_type
	{
		long i = left;
		long j = right + 1;

		Cont::value_type pivot = container[left];

		// Pivot is first element
		while (true)
		{
			// Run from left to right looking for values greater than our Pivot
			while (container[++i] < pivot)
			{
				// Reach the end?
				if (i == right)
					break;
			}

			// Run from right to left looking for values less than ut Pivot
			while (container[--j] > pivot)
			{
				// Reach the beginning?
				if (j == left)
					break;
			}

			// Do we need to do anything?
			if (i >= j)
				break;

			// Exchange items variables i and j point to
			std::swap(container[j], container[i]);
		}

		container[left] = container[j];
		container[j] = pivot;

		// Take j as a new Pivot
		return j;
	}
};