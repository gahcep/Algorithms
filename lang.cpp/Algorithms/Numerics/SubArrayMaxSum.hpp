#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

/*
	Time complexity: O(n^3)
	Space complexity: O(1)

	Example: Array Size: 9 items; Additions Number: 285
	Example: Array Size: 10 items; Additions Number: 385
*/
template <class T>
auto mss_naive_bad(std::vector<T> values) -> T
{
	int cnt{};
	T sum = std::numeric_limits<T>::min();

	for (size_t sub_arr_size = 1; sub_arr_size <= values.size(); sub_arr_size++)
	{
		for (size_t start_index = 0; start_index < values.size(); start_index++)
		{
			T tmp = 0;
			
			for (size_t i = 0; (i < sub_arr_size) && (start_index + i) < values.size(); i++)
			{
				cnt++;
				tmp += values[start_index + i];
			}
			
			sum = sum < tmp ? tmp : sum;
		}
	}

	std::cout << "Array Size: " << values.size() << "; Additions Number: " << cnt << '\n';

	return sum;
};

/*
	Time complexity: O(n^2)
	Space complexity: O(1)

	Example: Array Size: 9 items; Additions Number: 45
	Example: Array Size: 10 items; Additions Number: 55
*/
template <class T>
auto mss_naive_good(std::vector<T> values) -> T
{
	int cnt{};
	T sum = std::numeric_limits<T>::min();

	for (size_t start_index = 0; start_index < values.size(); start_index++)
	{
		T tmp = 0;
		for (size_t i = start_index; i < values.size(); i++)
		{
			cnt++;
			tmp += values[i];
			sum = sum < tmp ? tmp : sum;
		}
	}

	std::cout << "Array Size: " << values.size() << "; Additions Number: " << cnt << '\n';

	return sum;
};

/*
	Time complexity: O(n*log(n))
	Space complexity: O(k) [recursion calls overhead]

	Example: Array Size: 9 items; Additions Number: 29
	Example: Array Size: 10 items; Additions Number: 34
*/

static int dac_cnt{0};

template<class T>
int max(T a, T b, T c) { return std::max(std::max(a, b), c); }

template <class T>
auto mss_divide_conquer(std::vector<T> values) -> T
{
	dac_cnt = 0;
	return mss_divide_conquer_sub(values, 0, values.size() - 1);
}

template <class T>
auto mss_divide_conquer_sub(std::vector<T>& values, int idx_begin, int idx_end) -> T
{
	// Base case
	if (idx_begin == idx_end)
		return values[idx_begin];

	auto idx_medium = idx_begin + (idx_end - idx_begin) / 2;

	return max<T>(
		mss_divide_conquer_sub(values, idx_begin, idx_medium),
		mss_divide_conquer_sub(values, idx_medium + 1, idx_end),
		mss_divide_conquer_cross(values, idx_begin, idx_medium, idx_end));
}

template <class T>
auto mss_divide_conquer_cross(std::vector<T>& values, int idx_begin, int idx_medium, int idx_end) -> T
{
	T sum, left_sum, right_sum;

	left_sum = std::numeric_limits<T>::min();
	right_sum = std::numeric_limits<T>::min();

	// Left sub-array
	sum = T{};
	for (int i = idx_medium; i >= idx_begin; i--)
	{
		dac_cnt++;
		sum += values[i];
		left_sum = std::max(sum, left_sum);
	}

	// Right sub-array
	sum = T{};
	for (int i = idx_medium + 1; i <= idx_end; i++)
	{
		dac_cnt++;
		sum += values[i];
		right_sum = std::max(sum, right_sum);
	}

	return left_sum + right_sum;
}

/*
	Time complexity: O(n)
	Space complexity: O(1)

	Example: Array Size: 9 items; Additions Number: 9
	Example: Array Size: 10 items; Additions Number: 10

	Note: array should contain at least one positive item
*/

template <class T>
auto mss_kadane(std::vector<T> values) -> T
{
	T sum{};
	T res{};

	for (int i = 0; i < values.size(); i++)
	{
		// In order to retrieve sub-array itself, push items accordingly to temp vector
		sum += values[i];
		
		// Resets sum if it becomes negative: if (sum < 0) { sum = 0; }
		sum = std::max(0, sum);
		
		res = std::max(res, sum);
	}

	return res;
}