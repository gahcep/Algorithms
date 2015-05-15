#pragma once

#include <vector>
#include <type_traits>

#include "TypePredicates.h"

using std::vector;

template<class Derived, class Cont, template <class> class Kind>
class Base
{
private:

	static_assert(HasConstIterator<Cont>::value, "Please provide a container type");

	static_assert(HasArithmeticType<Cont>::value, "Container's elements should be of integral type");

	static_assert(HasRunMethod<Kind<Cont>, Cont>::value, "Sorting algorithm must have <run> method defined");

public:

	Kind<Cont> kind;

	auto RunSort() -> void
	{
		// Take const reference
		const Derived& derived = static_cast<const Derived&>(*this);

		// [#]
		// However the inner container can be changed
		kind.run(const_cast<Cont&>(derived.cont));
	};

	auto Sorted() const -> Cont
	{
		// Take const reference
		const Derived& derived = static_cast<const Derived&>(*this);

		return derived.cont;
	}
};

//template<class Cont, template <class, class> class Kind> <-- second parameter will accept [vector]

template<class Cont, template <class> class Kind>
class GenericSort : public Base<GenericSort<Cont, Kind>, Cont, Kind>
{
	// Stores data and provides unified way to invoke sorting functions
	// according to a given algorithm kind
	static_assert(HasProperAlgoType<Cont, Kind<Cont>>::value, "Unknown algorithm type");

	// In order for the Base to see protected members of this class (in [#] line above)
	friend class Base<GenericSort<Cont, Kind>, Cont, Kind>;

public:

	explicit GenericSort(const Cont& container) : cont(container)
	{
		auto a = 0;
	};

	explicit GenericSort(Cont&& container) : cont(std::move(container))
	{
		auto a = 0;
	};

protected:

	Cont cont{};

};
