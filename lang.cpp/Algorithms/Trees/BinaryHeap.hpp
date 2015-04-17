#include <vector>
#include <initializer_list>
#include <stdexcept>

template <class T>
class Heap
{
	// Allow only integral or floating-point types
	static_assert(std::is_arithmetic<T>::value, "Given type not allowed");

public:

	// Default ctor
	Heap() { };
	// Custom ctor
	Heap(std::initializer_list<T> values) { make_heap(values); }
	// Custom ctor
	Heap(std::vector<T>& values) { make_heap(values); }
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
	auto is_heap(std::vector<T>& list) -> bool;

	auto has_childs(size_t idx) const -> std::pair<bool, bool>;
	auto get_childs(size_t idx) const -> std::pair<T, T>;

	auto make_heap(std::initializer_list<T> values) -> void;
	auto make_heap(std::vector<T>& values) -> void;
	auto make_heap(std::vector<T>&& values) -> void;

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

	std::vector<int> heap_;

};

template <class T>
auto Heap<T>::print() const -> void
{
	if (empty())
		std::cout << "Heap is empty" << std::endl;

	for (auto x& : heap_)
		std::cout << x << " " << std::endl;
}

template <class T>
auto Heap<T>::sift_up(size_t idx) -> void
{
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

template <class T>
auto Heap<T>::sift_down(size_t idx) -> void
{
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

template <class T>
auto Heap<T>::left(size_t idx) const -> std::pair<bool, T>
{
	if (idx >= heap_.size())
		throw std::length_error("left(): Index out of range");

	std::pair<bool, T> value = std::make_pair<bool, T>(false, T{});

	size_t left = 2 * parent + 1;
	if (left < heap_.size())
	{
		value.first = true;
		value.second = heap_[left];
	}

	return value;
}

template <class T>
auto Heap<T>::right(size_t idx) const -> std::pair<bool, T>
{
	if (idx >= heap_.size())
		throw std::length_error("right(): Index out of range");

	std::pair<bool, T> value = std::make_pair<bool, T>(false, T{});

	size_t right = 2 * parent + 2;
	if (right < heap_.size())
	{
		value.first = true;
		value.second = heap_[right];
	}

	return value;
}

template <class T>
auto Heap<T>::parent(size_t idx) const -> T
{
	if (idx >= heap_.size())
		throw std::length_error("parent(): Index out of range");

	if (idx == 0) return heap_[0];

	return heap_[(idx - 1) / 2];
}

template <class T>
auto Heap<T>::insert(T key) -> void
{
	heap_.push_back(key);
	sift_up(heap_.size() - 1);
}

template <class T>
auto Heap<T>::get_min() const -> T
{
	return heap_[0];
}

template <class T>
auto Heap<T>::extract_min() -> T
{
	T value = heap_[0];
	
	heap_[0] = heap_[heap_.size() - 1];
	heap_.erase(heap_.end() - 1);
	
	sift_down(0);

	return value;
}

template <class T>
auto Heap<T>::make_heap() -> void
{
	if (heap_.size() == 0)
		throw std::length_error("make_heap(): Heap is empty");

	// No need to check last (N/2 - 1) items
	size_t bound = heap_.size() / 2 - 1;

	// Loop from (N/2 - 1) to 0
	for (size_t i = bound + 1; i-- > 0;)
		sift_down(i);
}

template <class T>
auto Heap<T>::make_heap(std::initializer_list<T> values) -> void
{
	heap_ = values;
	make_heap();
}

template <class T>
auto Heap<T>::make_heap(std::vector<T>& values) -> void
{
	heap_ = values;
	make_heap();
}

template <class T>
auto Heap<T>::make_heap(std::vector<T>&& values) -> void
{
	heap_ = std::move(values);
	make_heap();
}

template <class T>
auto Heap<T>::is_heap(std::initializer_list<T> values) -> bool
{
	return is_heap(std::move(std::vector<T>{ values }));
}

template <class T>
auto Heap<T>::is_heap(std::vector<T>& values) -> bool
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
}

template <class T>
auto Heap<T>::has_childs(size_t idx) const -> std::pair<bool, bool>
{
	auto idx_left = idx * 2 + 1;
	auto idx_right = idx_left + 1;

	return std::make_pair<T, T>(idx_left < heap_.size(), idx_right < heap_.size());
}

template <class T>
auto Heap<T>::get_childs(size_t idx) const -> std::pair<T, T>
{
	auto idx_left = idx * 2 + 1;
	auto idx_right = idx_left + 1;

	return std::make_pair<T, T>(
		idx_left < heap_.size() ? heap_[idx_left] : T{}, 
		idx_right < heap_.size() ? heap_[idx_right] : T{});
}
