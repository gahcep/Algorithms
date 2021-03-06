#pragma once
#include <vector>
#include <type_traits>
#include <iterator>

/*
	PROPER_SORTING_ALGORITHM:
	Part 1: Declaration of an algorithm
	Part 2: Partial template specialization for the algorithm
*/

#define PROPER_SORTING_ALGORITHM(_X_) \
									  \
									template <class Cont> struct _X_; \
									\
									template<class Cont> \
									struct HasProperAlgoType<Cont, _X_<Cont>> \
									{ \
										static const bool value = true; \
									};

/* Check for [auto run(Cont& container) -> void] method */
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

template<class Cont>
struct HasRandomAccessIterator
{
	using Iter = typename Cont::iterator;

	const static bool value = std::is_same<typename std::iterator_traits<Iter>::iterator_category, std::random_access_iterator_tag>::value;
};

template<class Cont, class Kind>
struct HasProperAlgoType
{
	static const bool value = false;
};

template <class Cont>
struct HasArithmeticType
{
	static const bool value = std::is_arithmetic<Cont::value_type>::value;
};