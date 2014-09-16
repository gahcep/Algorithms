#include "SortFactory.h"
#include "../Sorting/QuickSort.h"

unique_ptr<ISortingBase> SortingFactory::Create(SortingType type)
{
	switch (type)
	{
	case SortingType::Quicksort:
		return unique_ptr<ISortingBase>(new QuickSort());

	default:
		throw new std::exception("Unknown sorting type");
	}
}