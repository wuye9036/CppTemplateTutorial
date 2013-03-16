#include "stdafx.h"
#include <vector>

#define WRONG_CODE_ENABLED 0

// 0. Basic Form
namespace _0
{
	template <typename T> // Old fasion: template <class T>
	class ClassA
	{
		T	a;
		T*	b;
		T foo();
		void foo2(T const&);
	};

	template <int Sz>
	class ClassB
	{
		int arr[Sz];
	};

	size_t a = sizeof(ClassB<3>);
	size_t b = sizeof(ClassB<7>);

	template <typename T> void FunctionA(T const& param)
	{
	}

	template <typename T> T FunctionB()
	{
		return T();
	}
}

// 1.1 Nested in Class
namespace _1_1
{
	template <typename T> // Old fasion: template <class T>
	class ClassA
	{
		T	a;
		T*	b;
		T foo();
		template <typename U> void foo2(T const&, U const&);
	};
}

// 1.2 Instanciating 1
namespace _1_2
{
	_1_1::ClassA<int>				a;

	#if WRONG_CODE_ENABLED
	_1_1::ClassA<WhatTheFuck>		b;	// Wrong
	_1_1::ClassA					c;	// Wrong
	#endif
}

// 1.3 Instanciating 2
namespace _1_3
{
	template <typename T>
	class ClassB
	{
		T* a;
	};

	template <typename T>
	class ClassC
	{
		T a;
	};

	struct StructA; // Declared but not be defined
	ClassB<StructA> d;	// Right
#if WRONG_CODE_ENABLED
	ClassC<StructA> e;	// Wrong
#endif
}

// 1.4 Specialization, Partial Specialization, Full Specialization
namespace _1_4
{
	// Prototype of Templates I: Single Parameter
	template <typename T> class ClassD
	{
		int a;
	};

	// Specialization: Write a pattern for matching
	template <> class ClassD<int>			// 1. template <>			2. ClassD<int>
	{
		int b;
	};
	
	template <> class ClassD<float>
	{
		int c;
	};
	
	// Partial-Specialization: A partial pattern for matching
	template <typename T> class ClassD<T*>	// 1. template <typename T>	2. ClassD<T*>
	{
		int d;
	};
	
	template <> class ClassD<int*>			// 1. template <>			2. ClassD<T*>
	{
		int e;
	};
	
	// Question:
	
	// ClassD<int>::?
	// ClassD<float>::?
	// ClassD<double>::?
	// ClassD<double*>::?
	// ClassD<int*>::?
	// ClassD<int const*>::?
	
	// Prototype of Templates II: Multiple Parameter
	template <typename T, typename U> class ClassE
	{
		int a;
	};
	
	template <typename T, typename U> class ClassE<T, U*>
	{
		int b;
	};
	
	template <typename T> class ClassE<T, int>
	{
		int c;
	};
	
	template <typename T> class ClassE<T, int*>
	{
		int d;
	};
	
	template <typename U> class ClassE<int, U>
	{
		int e;
	};
	
	template <> class ClassE<int, int>
	{
		int f;
	};
	
	// Question:

	// ClassE<float, double>::?
	// ClassE<float, int>::?
	// ClassE<int, float>::?
	// ClassE<int, int*>::?
	// ClassE<int, int>::?

	// Member function specialization
	template <typename T>
	class ClassF
	{
	public:
		void foo();
	};

	template <typename T>
	void ClassF<T>::foo()
	{
	}

	template <> 
	void ClassF<int>::foo()
	{
	}

	void foo()
	{
		ClassF<int>().foo();
		ClassF<float>().foo();
	}
}

// 2.1 Function Specialization
namespace _2_1
{
	// Overload is enabled but no partial-specialization
	template <typename T> void foo(T const& x) {}
	template <typename T> void foo(T& y) {}
	void foo(int&) {}
	void foo(int) {}

	// Specialization or Overloading
	template <> void foo<bool>(bool const& x) {}

	// Overloading
	template <typename T> void foo(T const*) {}

	template <typename T, typename U> void foo2(T const&, U const&);

#if WRONG_CODE_ENABLED
	template <typename U> void foo2<int, U>(int const&, U const&);
	template <typename T, typename U> void foo2<T, U>(int const&, U const&);
#endif

	// Overloading - Looks like partial specification
	template <typename U> void foo2(int const&, U const&);
	template <typename T, typename U> void foo2(T const*, U const&);

	// Don't forgot
	// T foo(...);

	// Specialize types which cannot be inferred by parameter
	template <typename UninferableT, typename InferableT>
	UninferableT foo3(InferableT const&) { return UninferableT(); }

	void test()
	{
		
		int x = 5;
		float y = 10.0f;
		foo(y);
		int const z = 5;
		foo(z);
		foo(true);
		foo3<int>(0.0f);	// Specialize types which is uninferable.

#if WRONG_CODE_ENABLED
		foo(3);	// Ambigous
		foo(x); // Ambigous
#endif
	}
}

// 2.2 Example: Derived from template.
namespace _2_2
{
	template <typename T>
	class ClassA
	{
		T x;
	};

	template <typename T>
	class ClassB
	{
		T* x;
	};
	
	template <typename T>
	class ClassC: public ClassB<T>
	{
		T* x;
	};
	
	ClassC<int> a;

#if WRONG_CODE_ENABLED
	class ClassC: public ClassA<ClassC>
	{
	};
#endif
	
	class ClassD: public ClassB<ClassD>
	{
	};
	
	// ClassC =??= ClassD
}

// 3.1 Meta Switch-Case/If-Then-Else via Specialization
namespace _3_1
{
	bool equal(int a, int b)
	{
		return a == b;
	}
	
	// meta functions:
	// bool equal0(TypeA, TypeB)
	// {
	//		return false;
	// }
	// bool equal1(TypeA, TypeA)
	// {
	//		return true;
	// }
	// equal(A, A) == equal1(A, A) == true
	// euqla(A, B) == equal0(A, B) == false
	template <typename T, typename U>
	class Equal
	{
	public:
		static bool const value = false;
	};
	
	template <typename T>
	class Equal<T, T>
	{
	public:
		static bool const value = true;
	};
	
	bool x = Equal<int, float>::value;
	bool y = Equal<int, int>::value;
}

// 3.2 SFINAE: Substitution Failure Is Not An Error.
namespace _3_2
{
	class ClassA
	{
	};

	template <int Sz> struct Mark
	{
		char _[Sz];
	};

#if	WRONG_CODE_ENABLED
	template <typename T>
	Mark<1> TestIncrementAdd(T const& v)
	{
		T tmp = v;
		++tmp;
		return Mark<1>();
	}

	template <typename T>
	Mark<2> TestIncrementAdd(T const& v)
	{
		return Mark<2>();
	}

	bool a = TestIncrementAdd( ClassA() ) ) == sizeof(Mark<1>);
#endif

	// Right case: From Wiki
	class ClassB
	{
	public:
		typedef int Marker;
	};
 
	template <typename T> void test(typename T::Marker) { }
	template <typename T> void test(T) { }
 
	void DoTest()
	{
		test<ClassB>(10);	// Call #1.
		test<int>(10);		// Call #2. SFINAE for test(T::Marker).
	}
}

// 3.3 Application: Type Traits
namespace _3_3
{
	template <typename T, typename U> class is_same;
	
	
	template <typename B, typename D> class is_base_of;
	// is_base_of
	// 1. B is class, D is also class.
	// 2. D* could be convert to B*
	// 3. B != D

	// Fundamentals
	typedef char Accepted;
	typedef int  Rejected;

	class B
	{
	};

	class D: public B
	{
	};

	class D2: public D
	{
	};

	// Type is a class
	template <typename T>
	class is_class
	{
	private:
		// SFINAE
		template <typename U> static Accepted test( int U::* );
		template <typename U> static Rejected test(...);

	public:
		static const bool value = sizeof( test<T>(0) ) == sizeof(Accepted);
	};

	bool a = is_class<int>::value;
	bool b = is_class<B>::value;

	// B* could be convert to D*
	template <typename Source, typename Dest>
	class Convertible
	{
	private:
		// Not SFINAE
		static Accepted test(Dest*);
		static Rejected test(...);
	public:
		static const bool value = sizeof( test(static_cast<Source*>(NULL)) ) == sizeof(Accepted);
	};

	bool c = Convertible<B, D>::value;
	bool d = Convertible<D, B>::value;
	bool e = Convertible<B, int>::value;

	// B != D
	using _3_1::Equal;

	template <typename Base, typename Derived>
	class is_base_of
	{
	public:
		static bool const value = 
			is_class<Base>::value &&
			is_class<Derived>::value &&
			Convertible<Base, Derived>::value &&
			!Equal<Base, Derived>::value;
	};

	bool f = is_base_of<B, D2>::value;
	bool g = is_base_of<D2, D>::value;
	bool h = is_base_of<B, int>::value;
	bool i = is_base_of<float, int>::value;

	// Questions:
	// remove_reference
	// remove_pointer
	// remove all qualifiers
}

// 3.4 Application: "Recursive" and Meta-Programming
namespace _3_4
{
	// sum a, a+1, ..., b-1, b
	int basic_algo(int a, int b)
	{
		int result = 0;
		for (int i = a; i <= b; ++i)
		{
			result += i;
		}
		return result;
	}

	// Template could not support variable

	// sum [a, b] without variable
	int recursive_algo(int a, int b)
	{
		if (a == b)
		{
			return b;
		}
		return a + recursive_algo(a+1, b);
	}

	// Translate to meta-programming
	template <int a, int b>
	class MetaSum
	{
	public:
		static int const value = MetaSum<a+1, b>::value + a;
	};

	template <int a>
	class MetaSum<a, a>
	{
	public:
		static int const value = a;
	};

	int a = MetaSum<1, 10>::value;
}

// 3.5 Application: Meta-Fibonacci
namespace _3_5
{
	template <int Index>
	class Fibonacci
	{
	public:
		static int const value = Fibonacci<Index - 1>::value + Fibonacci<Index - 2>::value;
	};

	template <>
	class Fibonacci<0>
	{
	public:
		static int const value = 0;
	};

	template <>
	class Fibonacci<1>
	{
	public:
		static int const value = 1;
	};

	int a = Fibonacci<8>::value;
}

// 4   Directive word: typename and template
namespace _4
{
	// typename T::type x;
	// ??? typename ???

	// typename T::template U<type> x;
	// ??? template ???

	class ClassA
	{
	public:
		typedef int NestedType;
	};

	class ClassB
	{
	public:
		typedef ClassA::NestedType NestedType;
	};

	template <typename T>
	class ClassC
	{
	public:
#if WRONG_CODE_ENABLED
		typedef T::NestedType NestedType;
#endif
		typedef typename T::NestedType NestedType;
		typedef typename std::vector<T>::iterator iterator;
	};

	class ClassD
	{
	public:
		template <typename U, typename V> class NestedType;
	};

	template <typename T>
	class ClassE
	{
	public:
		template <typename U> class NestedType;
	};

	template <typename T, typename U>
	class ClassF
	{
#if WRONG_CODE_ENABLED
		typedef typename T::NestedType<U> NestedType;
#endif
		typedef typename T::template NestedType<U, int> NestedType;
		typedef typename ClassE<T>::template NestedType<U> NestedType2;
	};

	ClassC<ClassB> a;
	ClassF<ClassD, float> b;
}

// 5.1 How to Construct Meta Operators
namespace _5_1
{
	// Expression = Value/Data Structure + Operator/Operations

	// Value in Templates:
	//	 Integral Constant (bool, char, unsigned, ...)
	//	 Type (typename)

	// 1. Trick: Constant <--> Type
	template <int i>
	class int_
	{
	public:
		static int const value = i;
	};

	int a = int_<5>::value;

	// This trick could work with overloading
	template <typename T>
	void Do(T* obj, int_<2>)
	{
	}

	template <typename T>
	void Do(T* obj, int_<1>)
	{
	}

	void foo()
	{
		Do( static_cast<int*>(nullptr), int_<1>() );
	}

	template <typename T, int i> void DoAnotherWay(T* obj)
	{
	}

	// Boolean is more useful than integral in general.
	template <bool v>
	class bool_
	{
	public:
		static bool const value = v;
	};

	typedef bool_<true>		true_;
	typedef bool_<false>	false_;
	
#if WRONG_CODE_ENABLED
	// Aha, function cannot support partial specialization.
	template <typename T> void DoAnotherWay<T, 1>(T* obj) {}
	template <typename T> void DoAnotherWay<T, 2>(T* obj) {}
#endif

	// 2. Operators:
	// add
	
	template <typename T, typename U>
	class add_
	{
	public:
		typedef int_<T::value + U::value> type;
		static int const value = type::value;
	};

#if WRONG_CODE_ENABLED
	// conflict
	template <int x, int y>
	class add_
	{
	public:
		typedef int_<x+y> type;
		static int const value = type::value;
	};
#endif
	template <int x, int y>
	class add_c
	{
	public:
		typedef int_<x+y> type;
		static int const value = type::value;
	};

	typedef add_< int_<2>, int_<3> >::type sum;
	int b = sum::value;

	typedef add_< int_<2>, int_<3> >::type sum_c;
	int c = sum_c::value;

	// another solution
	template <typename T, typename U>
	class add2_: public int_<T::value+U::value>
	{
	};
	int d = add2_< int_<2>, int_<3> >::value;

	// Other operators: sub, not, or, and ...
}

// 5.2 Example of Meta Programming: Meta-Vector
namespace _5_2
{
	// Array: elem[count]
	// Meta Array ?

	// Recursively Definition
	// 'Null' terminated
	template <typename HeadT, typename TailT>
	class pair_
	{
		typedef HeadT head;
		typedef TailT tail;
	};

	class Nil;
	
	// Try Use It to Definition
	typedef pair_< int, pair_<float, pair_<double, Nil> > > vector_3;

	template <typename T0, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil>
	class make_vector_
	{
		typedef pair_< T0, make_vector_<T1, T2, T3> > type;
	};

	template <>
	class make_vector_<Nil, Nil, Nil, Nil>
	{
		typedef Nil type;
	};

	template <typename T0, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil>
	class vector_: public make_vector_<T0, T1, T2, T3>::type
	{
	};

	typedef vector_<double, float, int> vector3;

	// Let's meta-program further
	//
	// push_back	?	tip: push_back<Vector, Element>::type
	// pop			?
	// find			?
	// size			?
}

// 6.1 Template-Template Class

// 6.2 High order function, closure and STL allocator rebind

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

