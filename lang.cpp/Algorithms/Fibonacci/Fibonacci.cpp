#include <iostream>
#include "Fibonacci.h"

using namespace std;

long long Fibonacci::NaiveSolve(int n)
{
	/* Exponential complexity O(a^n) */
	return n <= 1 ? n : NaiveSolve(n - 2) + NaiveSolve(n - 1);
}

long long Fibonacci::ArraySolve(int n, bool print_result = false)
{
	long long arr[3] = { 0, 0, 0 };

	if (n <= 1)
		return n;

	// Initial settings
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;

	cout << "[0]:\t" << 0 << endl;
	cout << "[1]:\t" << 1 << endl;
	cout << "[2]:\t" << 1 << endl;

	for (int i = 2; i < n; i++)
	{
		arr[0] = arr[1];
		arr[1] = arr[2];
		arr[2] = arr[0] + arr[1];

		if (print_result)
		{
			cout << "[" << i + 1 << "]:\t" << arr[2] << endl;
		}
	}

	return arr[2];
}

int Fibonacci::FindLastDigit(int n)
{
	int arr[3] = { 0, 0, 0 };

	if (n <= 1)
		return n;

	// Initial settings
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;

	for (int i = 2; i < n; i++)
	{
		arr[0] = arr[1];
		arr[1] = arr[2];
		arr[2] = (arr[0] + arr[1]) % 10;
	}

	return arr[2];
}