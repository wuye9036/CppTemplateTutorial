#include <tuple>
#include <type_traits>
#include <iostream>

using std::tuple;
using std::integral_constant;
using std::is_same;

template <int... values> struct to_int_types{
	typedef tuple< integral_constant<int, values>... > type;
};

template <typename Pivot> struct Less {
	template <typename X> struct Apply {
		static bool const value = X::value < Pivot::value;
	};
};

template <typename Pivot> struct GE {
	template <typename X> struct Apply {
		static bool const value = X::value >= Pivot::value;
	};
};

template <typename x, bool realAdd, typename tuple>         struct Tuple_PushFront {};
template <typename x, typename... tupleElems> struct Tuple_PushFront<x, true, tuple<tupleElems...>> {
	typedef tuple<x, tupleElems...> type;
};
template <typename x, typename... tupleElems> struct Tuple_PushFront<x, false, tuple<tupleElems...>> {
	typedef tuple<tupleElems...> type;
};

template <typename Pred, typename tuple> struct Filter;
template <typename Pred> struct Filter< Pred, tuple<> > {
	typedef tuple<> type;
};
template <typename Pred, typename Head, typename... Ts> struct Filter< Pred, tuple<Head, Ts...> > {
	typedef typename Tuple_PushFront<
		Head, Pred::template Apply<Head>::value, typename Filter<Pred, tuple<Ts...>>::type
	>::type type;
};

template <typename... Tuples> struct ConcatenateTuple {};
template <typename    Tuple0> struct ConcatenateTuple<Tuple0> {
	typedef Tuple0 type;
};

template <typename Tuple0, typename Tuple1> struct ConcatenateTuple<Tuple0, Tuple1> {
	template <typename TupleA> struct ConcatenateImpl {};
	template <typename... TAs> struct ConcatenateImpl< tuple<TAs...> > {
		template <typename TupleB> struct Apply;
		template <typename... TBs> struct Apply< tuple<TBs...> > {
			typedef tuple<TAs..., TBs...> type;
		};
	};
	typedef typename ConcatenateImpl<Tuple0>::template Apply<Tuple1>::type type;
};
template <typename FirstTuple, typename... Follows> struct ConcatenateTuple<FirstTuple, Follows...> {
	typedef typename ConcatenateTuple<
		FirstTuple, typename ConcatenateTuple<Follows...>::type
	>::type type;
};

template <typename tuple> struct QuickSort {};
template <>               struct QuickSort< tuple<  > > { typedef tuple<  > type; };
template <typename T0>    struct QuickSort< tuple<T0> > { typedef tuple<T0> type; };
template <typename Head, typename... Ts>
struct QuickSort< tuple<Head, Ts...> > {
	typedef typename Filter< Less<Head>, tuple<Ts...> >::type LeftElems;
	typedef typename Filter< GE  <Head>, tuple<Ts...> >::type RightElems;
	typedef typename ConcatenateTuple<
		typename QuickSort<LeftElems>::type, tuple<Head>, typename QuickSort<RightElems>::type
	>::type type;
};

void StaticTest()
{
	typedef to_int_types<1, 2, 3>::type lst_1_3;
	typedef to_int_types<3, 2, 1>::type lst_3_1;
	typedef to_int_types<3, 7, 1, 6, 5, 22, 5>::type lst;
	typedef to_int_types<1, 3, 5, 5, 6, 7, 22>::type sorted_lst;

	typedef integral_constant<int, 1>::type i1;
	typedef integral_constant<int, 2>::type i2;
	typedef integral_constant<int, 3>::type i3;

	static_assert(Less<i2>::Apply<i1>::value == true, "");
	static_assert(Less<i1>::Apply<i1>::value == false, "");
	static_assert(Less<i1>::Apply<i2>::value == false, "");

	static_assert(GE<i2>::Apply<i3>::value == true, "");
	static_assert(GE<i2>::Apply<i2>::value == true, "");
	static_assert(GE<i3>::Apply<i2>::value == false, "");

	static_assert(is_same<Tuple_PushFront<i1, true,  tuple<i2>>::type, tuple<i1, i2>>::value, "");
	static_assert(is_same<Tuple_PushFront<i2, true,  tuple<i1>>::type, tuple<i2, i1>>::value, "");
	static_assert(is_same<Tuple_PushFront<i2, false, tuple<i1>>::type, tuple<i1>>::value,     "");

	static_assert(is_same<Filter<Less<i2>, lst_1_3>::type, tuple<i1>>::value, "");

	static_assert(is_same<QuickSort<lst_1_3  >::type, lst_1_3>::value, "");
	static_assert(is_same<QuickSort<lst_3_1  >::type, lst_1_3>::value, "");
	static_assert(is_same<QuickSort<tuple<>  >::type, tuple<>>::value, "");
	static_assert(is_same<QuickSort<tuple<i1>>::type, tuple<i1>>::value, "");
	static_assert(is_same<QuickSort<lst      >::type, sorted_lst>::value, "");
}
