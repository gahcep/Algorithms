#pragma once

#include <memory>

#include "../Abstractions/ISortingBase.h"

using namespace std;

enum class SortingType
{
	Quicksort
};

class SortingFactory
{
public:

	static unique_ptr<ISortingBase> Create(SortingType type);
};