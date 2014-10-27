#include <iostream>
#include <vector>
#include <memory>

#include "../Algorithms/Sorting/QuickSort.h"
#include "../Algorithms/Sorting/MergeSort.h"
#include "../Algorithms/Fibonacci.h"

using namespace std;

int main(int argc, char** argv)
{
	vector<int> vec_random { 4, 7, 22, 5, 1, 9, 3, 87, 24, 7, 4, 3, 67, 12, 67, 23, 78, 45 };
	vector<int> vec_sorted{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	vector<int> vec_rev_sorted { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	
	// QuickSort
	//auto qsort = unique_ptr<QuickSort>(new QuickSort());
	//qsort->Run(vec_random);

	// MergeSort
	auto msort = unique_ptr<MergeSort>(new MergeSort());
	msort->Run(vec_random);

	// Fibonacci
	auto fibo = unique_ptr<Fibonacci>(new Fibonacci());
	auto found_num = fibo->NaiveSolve(7);

	found_num = fibo->ArraySolve(70, true);
	found_num = fibo->FindLastDigit(18);

	auto v = 0;

}