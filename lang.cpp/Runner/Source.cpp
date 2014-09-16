#include <iostream>
#include "../Algorithms/Factory/SortFactory.h"

using namespace std;

int main(int argc, char** argv)
{
	auto sorting = SortingFactory::Create(SortingType::Quicksort);
	sorting.get()->Sort();
}