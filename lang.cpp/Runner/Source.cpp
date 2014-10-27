#include <iostream>
#include <vector>
#include <memory>

#include "../Algorithms/Sorting/QuickSort.h"
#include "../Algorithms/Fibonacci.h"

using namespace std;

int main(int argc, char** argv)
{
	vector<int> vec{ 4, 7, 22, 5, 1, 9, 3, 87, 24, 7, 4, 3, 67, 12, 67, 23, 78, 45 };
	
	// QuickSort
	auto qsort = unique_ptr<QuickSort>(new QuickSort());
	qsort.get()->Run(vec);
	// Fibonacci
	auto fibo = unique_ptr<Fibonacci>(new Fibonacci());
	auto found_num = fibo->NaiveSolve(7);

	found_num = fibo->ArraySolve(70, true);
	found_num = fibo->FindLastDigit(18);

	auto v = 0;

}