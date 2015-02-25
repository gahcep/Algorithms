#pragma once

#include "../Sorting/BubbleSort.h"

#include <vector>
#include <type_traits>

using namespace std;

class SortingBase
{
public:
	
	virtual void Run(vector<int>&) = 0;
};

// --------------------------------------

template <class Inst, class Cont>
struct HasRunMethod
{
private:
	typedef char match_type;
	typedef long unmatch_type;

	template <class U, U>
	class checker {};

	template <class _Inst, class _Cont>
	static match_type verify(checker<void (_Inst::*) (_Cont&), &_Inst::run>*);

	template <class _Inst, class _Cont>
	static unmatch_type verify(...);

public:
	const static bool value = (sizeof(verify<Inst, Cont>(nullptr)) == sizeof(match_type));
};

// --------------------------------------

template <class Cont>
struct HasConstIterator
{
private:
	typedef char match_type;
	typedef long unmatch_type;

	template<class T>
	static match_type checker(typename T::const_iterator *);

	template<class T>
	static unmatch_type checker(...);

public:

	const static bool value = (sizeof(checker<Cont>(nullptr)) == sizeof(match_type));
};

// --------------------------------------

template<class Cont, class Kind>
struct HasProperAlgoType
{
	static const bool value = false;
};

template<class Cont>
struct HasProperAlgoType<Cont, BubbleSort<Cont>>
{
	static const bool value = true;
};

// --------------------------------------

template <class Cont>
struct HasArithmeticType
{
	static const bool value = std::is_arithmetic<Cont::value_type>::value;
};

// --------------------------------------

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
		const Derived & derived = static_cast<const Derived &>(*this);

		// [#]
		// However the innner container can be changed
		kind.run(const_cast<Cont&>(derived.cont));
	};
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

	explicit GenericSort(const Cont & container) : cont(container) 
	{
		auto a = 0;
	};

	explicit GenericSort(Cont && container) : cont(std::move(container)) 
	{
		auto a = 0;
	};

protected:

	Cont cont{};

};

