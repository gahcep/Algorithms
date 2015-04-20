// main.cpp
#define CATCH_CONFIG_MAIN
#include <vector>
#include <algorithm>
#include "../TPL/philsquared/catch.hpp"
#include "../TPL/DataLoader.hpp"
#include "../Algorithms/Abstractions/GenericSortBase.h"
#include "../Algorithms/Sorting/QuickSort.h"
#include "../Algorithms/Sorting/MergeSort.h"
#include "../Algorithms/Sorting/BubbleSort.h"
#include "../Algorithms/Sorting/SelectionSort.h"
#include "../Algorithms/Sorting/InsertionSort.h"
#include "../Algorithms/Sorting/HeapSort.h"

TEST_CASE("Sort Empty Array", "[Sorting]")
{
	std::vector<float> vec_empty{};

	SECTION("BubbleSort")
	{
		GenericSort<vector<float>, BubbleSort> bs(vec_empty);
		bs.RunSort();
		REQUIRE(vec_empty.size() == 0);
	}

	SECTION("InsertionSort")
	{
		GenericSort<vector<float>, InsertionSort> is(vec_empty);
		is.RunSort();
		REQUIRE(vec_empty.size() == 0);
	}

	SECTION("SelectionSort")
	{
		GenericSort<vector<float>, SelectionSort> ss(vec_empty);
		ss.RunSort();
		REQUIRE(vec_empty.size() == 0);
	}

	SECTION("QuickSort")
	{
		GenericSort<vector<float>, QuickSort> qs(vec_empty);
		qs.RunSort();
		REQUIRE(vec_empty.size() == 0);
	}

	SECTION("MergeSort")
	{
		GenericSort<vector<float>, MergeSort> ms(vec_empty);
		ms.RunSort();
		REQUIRE(vec_empty.size() == 0);
	}

	SECTION("HeapSort")
	{
		GenericSort<vector<float>, HeapSort> hs(vec_empty);
		REQUIRE_THROWS_AS(hs.RunSort(), std::length_error);
	}
}

TEST_CASE("One-Item Array", "[Sorting]")
{
	std::vector<float> vec_one{10000};

	SECTION("BubbleSort")
	{
		GenericSort<vector<float>, BubbleSort> bs(vec_one);
		bs.RunSort();
		REQUIRE(vec_one.size() == 1);
	}

	SECTION("InsertionSort")
	{
		GenericSort<vector<float>, InsertionSort> is(vec_one);
		is.RunSort();
		REQUIRE(vec_one.size() == 1);
	}

	SECTION("SelectionSort")
	{
		GenericSort<vector<float>, SelectionSort> ss(vec_one);
		ss.RunSort();
		REQUIRE(vec_one.size() == 1);
	}

	SECTION("QuickSort")
	{
		GenericSort<vector<float>, QuickSort> qs(vec_one);
		qs.RunSort();
		REQUIRE(vec_one.size() == 1);
	}

	SECTION("MergeSort")
	{
		GenericSort<vector<float>, MergeSort> ms(vec_one);
		ms.RunSort();
		REQUIRE(vec_one.size() == 1);
	}

	SECTION("HeapSort")
	{
		GenericSort<vector<float>, HeapSort> hs(vec_one);
		hs.RunSort();
		REQUIRE(vec_one.size() == 1);
	}
}

TEST_CASE("Generic Array", "[Sorting]")
{
	// Load input data for sorting algorithms
	DataLoader::Loader<int> loader("../InputData/sorting.txt");
		
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
	vector<int> vec_generic{ 0 };
	loader.arg_vector(0, vec_generic);
	size_t len = vec_generic.size();

	SECTION("BubbleSort")
	{
		GenericSort<vector<int>, BubbleSort> bs(vec_generic);
		bs.RunSort();
		std::swap(bs.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}

	SECTION("InsertionSort")
	{
		GenericSort<vector<int>, InsertionSort> is(vec_generic);
		is.RunSort();
		std::swap(is.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}

	SECTION("SelectionSort")
	{
		GenericSort<vector<int>, SelectionSort> ss(vec_generic);
		ss.RunSort();
		std::swap(ss.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}

	SECTION("QuickSort")
	{
		GenericSort<vector<int>, QuickSort> qs(vec_generic);
		qs.RunSort();
		std::swap(qs.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}

	SECTION("MergeSort")
	{
		GenericSort<vector<int>, MergeSort> ms(vec_generic);
		ms.RunSort();
		std::swap(ms.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}

	SECTION("HeapSort")
	{
		GenericSort<vector<int>, HeapSort> hs(vec_generic);
		hs.RunSort();
		std::swap(hs.Sorted(), vec_generic);
		REQUIRE(vec_generic.size() == len);
		REQUIRE(std::is_sorted(vec_generic.begin(), vec_generic.end()));
	}
}

TEST_CASE("Heap Creation via Initialization list", "[Construction][Heap][Trees]")
{
	auto ilist = { 1, 2, 1, 3, 6, 7, 10, 19, 111, 116 };
	Heap<std::vector<int>> hp(ilist);

	REQUIRE(hp.size() == ilist.size());
	REQUIRE(hp.empty() == false);
}

TEST_CASE("Heap Creation via Copy Ctor", "[Construction][Heap][Trees]")
{
	auto ilist = { 1, 2, 1, 3, 6, 7, 10, 19, 111, 116 };
	Heap<std::vector<int>> hp(Heap<std::vector<int>>{ilist});

	REQUIRE(hp.size() == ilist.size());
	REQUIRE(hp.empty() == false);
}

TEST_CASE("Make Heap", "[Construction][Heap][Trees]")
{
	int min_val = -15;
	auto ilist = { 1, 2, min_val, 3, 6, 7, 10, 19, 111, 116 };
	std::vector<int> vec_heap{ 3, 1, min_val, 44, 1, 567, 3, 4, 54, 54, 567, 56, 578 };

	Heap<std::vector<int>> hp;

	SECTION("Make Heap via std::vector")
	{
		hp.make_heap(vec_heap);
		REQUIRE(hp.size() == vec_heap.size());
		REQUIRE(hp.empty() == false);
		REQUIRE(hp.get_min() == min_val);
	}

	SECTION("Make Heap via std::move and std::vector")
	{
		size_t len = vec_heap.size();
		hp.make_heap(std::move(vec_heap));
		REQUIRE(vec_heap.empty() == true);
		REQUIRE(hp.size() == len);
		REQUIRE(hp.empty() == false);
		REQUIRE(hp.get_min() == min_val);
	}

	SECTION("Make Heap via initializer list")
	{
		hp.make_heap(ilist);
		REQUIRE(hp.size() == ilist.size());
		REQUIRE(hp.empty() == false);
		REQUIRE(hp.get_min() == min_val);
	}
}

TEST_CASE("Insert and Extract from Heap", "[Methods][Heap][Trees]")
{
	std::vector<int> vec_heap{ 3, 1, -5, 44, 1, 567, 3, 4, 54, 54, 567, 56, 578 };
	Heap<std::vector<int>> hp;
	hp.make_heap(vec_heap);

	hp.insert(-444);
	hp.insert(8);
	hp.insert(1000);

	REQUIRE(hp.get_min() == -444);

	hp.extract_min();
	REQUIRE(hp.get_min() == -5);
}

TEST_CASE("Check if a List is a Heap", "[Methods][Heap][Trees]")
{
	Heap<std::vector<int>> hp;

	REQUIRE(hp.is_heap({ 1, 2, 1, 3, 6, 7, 10, 19, 111, 116 }) == true);
	REQUIRE(hp.is_heap({ 1, 1, 1, 1, 1, 1, 1 }) == true);
	REQUIRE(hp.is_heap({ 1, 1, 1, 1, 1, 1, 0 }) == false);
}

TEST_CASE("Heap Navigation", "[Methods][Heap][Trees]")
{
	std::vector<int> vec_heap{ 3, 1, -5, 44, 1, 567, 3, 4, 54, 54, 567, 56, 578 };
	Heap<std::vector<int>> hp;
	hp.make_heap(vec_heap);

	// Not existing index
	REQUIRE_THROWS_AS(hp.parent(100), std::length_error);
	// Root itself
	REQUIRE(hp.parent(0) == hp.get_min());
	// Real index
	REQUIRE(hp.parent(2) == -5);
	
	// Not existing index
	REQUIRE_THROWS_AS(hp.left(100), std::length_error);
	// Has left node
	REQUIRE((hp.left(1).first == true && hp.left(1).second == 4));
	// Doesn't have left node
	REQUIRE((hp.left(7).first == false));
	
	// Not existing index
	REQUIRE_THROWS_AS(hp.right(100), std::length_error);
	// Has right node
	REQUIRE((hp.right(2).first && hp.right(2).second == 3));
	// Doesn't have right node
	REQUIRE((hp.left(6).first == false));
	
	// Check childs
	auto pair = hp.has_childs(5);
	REQUIRE((pair.first == true && pair.second == true));
	pair = hp.has_childs(11);
	REQUIRE((pair.first == false && pair.second == false));
}