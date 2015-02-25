#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

#include "../TPL/DataLoader.hpp"

#include "../Algorithms/Abstractions/GenericSortBase.h"

#include "../Algorithms/Sorting/QuickSort.h"
//#include "../Algorithms/Sorting/MergeSort.h"
#include "../Algorithms/Sorting/BubbleSort.h"
#include "../Algorithms/Sorting/SelectionSort.h"
#include "../Algorithms/Sorting/InsertionSort.h"

using std::vector;

int main(int argc, char** argv)
{
	// Load input data for sorting algorithms
	DataLoader::Loader<float> loader("../InputData/sorting.txt");
	
	// Set up the reader
	loader.delimeter(';');

	// Load data from the file
	loader.read_vector(DataLoader::Flags::NullOpts, DataLoader::Flags_Vector_Parse::ItemsAtOnce, DataLoader::Kind::Vector);

	// Check state
	if (!loader.is_ok())
	{
		loader.refresh();
		exit(1);
	}

	// Load data from the reader
	vector<float> vec_random{ 0 };
	vector<float> vec_random2{ 0 };
	loader.arg_vector(0, vec_random);
	loader.arg_vector(0, vec_random2);

	GenericSort<vector<float>, BubbleSort> bs(vec_random);
	GenericSort<vector<float>, InsertionSort> is(vec_random);
	GenericSort<vector<float>, SelectionSort> ss(vec_random);
	GenericSort<vector<float>, QuickSort> qs(vec_random);
	
	bs.RunSort();
	is.RunSort();
	ss.RunSort();
	qs.RunSort();

	auto n = 0;

	//// InsertionSort
	//auto isort = unique_ptr<InsertionSort>(new InsertionSort());
	//isort->Run(vec_random);

	//// SelectionSort
	//auto ssort = unique_ptr<SelectionSort>(new SelectionSort());
	//ssort->Run(vec_random);

	//// BubbleSort
	//auto bsort = unique_ptr<BubbleSort>(new BubbleSort());
	//bsort->Run(vec_random);

	//// QuickSort
	//auto qsort = unique_ptr<QuickSort>(new QuickSort());
	//qsort->Run(vec_random);

	//// MergeSort
	//auto msort = unique_ptr<MergeSort>(new MergeSort());
	//msort->Run(vec_random);

	//// Fibonacci
	//auto fibo = unique_ptr<Fibonacci>(new Fibonacci());
	//auto found_num = fibo->NaiveSolve(7);

	//found_num = fibo->ArraySolve(70, true);
	//found_num = fibo->FindLastDigit(18);

	//auto v = 0;
}