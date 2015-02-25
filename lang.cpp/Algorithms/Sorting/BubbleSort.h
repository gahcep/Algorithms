#pragma once

//template <class Cont>
//struct HasConstIterator
//{
//private:
//	typedef char match_type;
//	typedef long unmatch_type;
//
//	template<class T>
//	static match_type checker(typename T::const_iterator *);
//
//	template<class T>
//	static unmatch_type checker(...);
//
//public:
//
//	const static bool value = (sizeof(checker<Cont>(0)) == sizeof(match_type));
//};

template <class Cont>
struct BubbleSort
{
	// Check that container type provided
	//static_assert(HasConstIterator<Cont>::value, "Please provide a container type");

	// Check that value_type of a container is of integral type
	//static_assert(std::is_arithmetic<typename Cont::value_type>::value, "Container's elements should be of integral type");

	auto run(Cont & container) -> void
	{
		sort(container, 0, container.size() - 1);
	}

private:

	auto sort(Cont & container, typename Cont::value_type beginPos, typename Cont::value_type endPos) -> void
	{
		bool swapped = false;

		// We are done when boundaries are wrong
		if (beginPos >= endPos)
			return;

		size_t len = container.size();

		// i = 0:len
		for (size_t i = 0; i < len; i++)
		{
			// j = 0:len-i
			for (size_t j = 0; j < len - i - 1; j++)
			{
				if (container[j] > container[j + 1])
				{
					int tmp = container[j];
					container[j] = container[j + 1];
					container[j + 1] = tmp;

					swapped = true;
				}
			}

			// If there was no swap - we done
			if (!swapped) break;
		}
	}
};
