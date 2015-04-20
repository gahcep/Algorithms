#pragma once
#include <vector>
#include <initializer_list>
#include <stdexcept>

#include "../Abstractions/TypePredicates.h"

template <class Cont>
class Heap
{
	// Allow only integral or floating-point types
	static_assert(std::is_arithmetic<typename Cont::value_type>::value, "Given type not allowed");

	// Check that container has random access iterator
	static_assert(HasRandomAccessIterator<Cont>::value,
		"Please provide a valid container type with random access iterator");
public:

	using T = typename Cont::value_type;

	// Default ctor
	Heap() {};
	// Custom ctor
	Heap(std::initializer_list<T> values) { make_heap(values); }
	// Custom ctor
	Heap(Cont& values) { make_heap(values); }
	// Copy ctor
	Heap(const Heap& other) 
	{
		heap_.resize(other.size());
		std::copy(other.heap_.begin(), other.heap_.end(), heap_.begin());
	}
	// Copy assign op
	Heap& operator=(const Heap& other)
	{
		if (this == &other) return *this;

		heap_.resize(other.size());
		std::copy(other.heap_.begin(), other.heap_.end(), heap_.begin());

		return *this;
	}
	// Move ctor
	Heap(Heap&& other)
	{
		heap_.resize(other.size());
		std::swap(other.heap_, heap_);
	}
	// Move assign op
	Heap& operator=(Heap&& other)
	{
		if (this == &other) return *this;

		heap_.resize(other.size());
		std::swap(other.heap_, heap_);

		return *this;
	}

	inline auto empty() const -> bool { return heap_.size() == 0; }
	inline auto size() const -> size_t { return heap_.size(); }

	auto is_heap(std::initializer_list<T> list) -> bool;
	auto is_heap(Cont& list) -> bool;

	auto has_childs(size_t idx) const -> std::pair<bool, bool>;
	auto get_childs(size_t idx) const -> std::pair<T, T>;

	auto make_heap(std::initializer_list<T> values) -> void;
	auto make_heap(Cont& values) -> void;
	auto make_heap(Cont&& values) -> void;

	auto insert(T key) -> void;
	
	auto get_min() const -> T;
	auto extract_min() -> T;

	auto parent(size_t idx) const -> T;
	auto left(size_t idx) const -> std::pair<bool, T>;
	auto right(size_t idx) const -> std::pair<bool, T>;

	auto print() const -> void;

private:

	auto sift_up(size_t idx) -> void;
	auto sift_down(size_t idx) -> void;
	auto make_heap() -> void;

	Cont heap_;

};

template <class Cont>
auto Heap<Cont>::print() const -> void
{
	if (empty())
		std::cout << "Heap is empty" << std::endl;

	for (auto x& : heap_)
		std::cout << x << " " << std::endl;
}

template <class Cont>
auto Heap<Cont>::sift_up(size_t idx) -> void
{
	if (heap_.empty()) return;

	if (idx >= heap_.size())
		throw std::length_error("sift_down(): Index out of range");

	size_t parent;
	while (idx > 0)
	{
		parent = (idx - 1) / 2;
		if (heap_[parent] < heap_[idx])
			return;
		std::swap(heap_[parent], heap_[idx]);
		idx = parent;
	}
}

template <class Cont>
auto Heap<Cont>::sift_down(size_t idx) -> void
{
	if (heap_.empty()) return;

	if (idx >= heap_.size())
		throw std::length_error("sift_down(): Index out of range");

	size_t left = 2 * idx + 1;
	size_t right = left + 1;

	size_t idx_min = idx;

	if (left < heap_.size() && heap_[left] < heap_[idx_min])
		idx_min = left;

	if (right < heap_.size() && heap_[right] < heap_[idx_min])
		idx_min = right;

	if (idx_min != idx)
	{
		std::swap(heap_[idx], heap_[idx_min]);
		sift_down(idx_min);
	}
}

template <class Cont>
auto Heap<Cont>::left(size_t idx) const -> std::pair<bool, T>
{
	if (idx >= heap_.size())
		throw std::length_error("left(): Index out of range");

	std::pair<bool, T> value = std::make_pair<bool, T>(false, T{});

	size_t left = 2 * idx + 1;
	if (left < heap_.size())
	{
		value.first = true;
		value.second = heap_[left];
	}

	return value;
}

template <class Cont>
auto Heap<Cont>::right(size_t idx) const -> std::pair<bool, T>
{
	if (idx >= heap_.size())
		throw std::length_error("right(): Index out of range");

	std::pair<bool, Cont::value_type> value = std::make_pair<bool, Cont::value_type>(false, Cont::value_type{});

	size_t right = 2 * idx + 2;
	if (right < heap_.size())
	{
		value.first = true;
		value.second = heap_[right];
	}

	return value;
}

template <class Cont>
auto Heap<Cont>::parent(size_t idx) const -> T
{
	if (idx >= heap_.size())
		throw std::length_error("parent(): Index out of range");

	if (idx == 0) return heap_[0];

	return heap_[(idx - 1) / 2];
}

template <class Cont>
auto Heap<Cont>::insert(T key) -> void
{
	heap_.push_back(key);
	sift_up(heap_.size() - 1);
}

template <class Cont>
auto Heap<Cont>::get_min() const -> T
{
	return heap_[0];
}

template <class Cont>
auto Heap<Cont>::extract_min() -> T
{
	Cont::value_type value = heap_[0];
	
	heap_[0] = heap_[heap_.size() - 1];
	heap_.erase(heap_.end() - 1);
	
	sift_down(0);

	return value;
}

template <class Cont>
auto Heap<Cont>::make_heap() -> void
{
	if (heap_.size() == 0)
		throw std::length_error("make_heap(): Heap is empty");

	// No need to check last (N/2 - 1) items
	size_t bound = heap_.size() / 2 - 1;

	// Loop from (N/2 - 1) to 0
	for (size_t i = bound + 1; i-- > 0;)
		sift_down(i);
}

template <class Cont>
auto Heap<Cont>::make_heap(std::initializer_list<T> values) -> void
{
	heap_ = values;
	make_heap();
}

template <class Cont>
auto Heap<Cont>::make_heap(Cont& values) -> void
{
	heap_ = values;
	make_heap();
}

template <class Cont>
auto Heap<Cont>::make_heap(Cont&& values) -> void
{
	heap_ = std::move(values);
	make_heap();
}

template <class Cont>
auto Heap<Cont>::is_heap(std::initializer_list<T> values) -> bool
{
	return is_heap(std::move(Cont{ values }));
}

template <class Cont>
auto Heap<Cont>::is_heap(Cont& values) -> bool
{
	size_t left, right, bound = values.size() / 2 - 1;
	for (int i = 0; i <= bound; i++)
	{
		left = 2 * i + 1;
		right = left + 1;
		if (left < values.size() && values[left] < values[i])
			return false;
		if (right < values.size() && values[right] < values[i])
			return false;
	}

	return true;
}

template <class Cont>
auto Heap<Cont>::has_childs(size_t idx) const -> std::pair<bool, bool>
{
	auto idx_left = idx * 2 + 1;
	auto idx_right = idx_left + 1;

	return std::make_pair<Cont::value_type, Cont::value_type>(idx_left < heap_.size(), idx_right < heap_.size());
}

template <class Cont>
auto Heap<Cont>::get_childs(size_t idx) const -> std::pair<T, T>
{
	auto idx_left = idx * 2 + 1;
	auto idx_right = idx_left + 1;

	return std::make_pair<Cont::value_type, Cont::value_type>(
		idx_left < heap_.size() ? heap_[idx_left] : Cont::value_type{},
		idx_right < heap_.size() ? heap_[idx_right] : Cont::value_type{});
}
