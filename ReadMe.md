
#  C++ Template 进阶指南

## 0. 前言

###0.1 C++另类简介：比你用的复杂，但比你想的简单

C++似乎从他为世人所知的那天开始便成为天然的话题性编程语言。在它在周围有着形形色色的赞美与贬低之词。当我在微博上透露欲写此文的意愿时，也收到了很多褒贬不一的评论。作为一门语言，能拥有这么多使用并恨着它、使用并畏惧它的用户，也算是语言丛林里的奇观了。

C++之所以变成一门层次丰富、结构多变、语法繁冗的语言，是有着多层次的原因的。Bjarne在《The Design and Evolution of C++》一书中，详细的解释了C++为什么会变成如今（C++98/03）的模样。这本书也是我和陈梓瀚一直对各位已经入门的新手强烈推荐的一本书。通过它你多少可以明白，C++的诸多语法要素之所以变成如今的模样，实属迫不得已。

模板作为C++中最有特色的语言特性，它堪称玄学的语法和语义，理所应当的成为初学者的梦魇。甚至很多工作多年的人也对C++的模板部分保有充分的敬畏。在多数的编码标准中，Template俨然和多重继承一样，成为了一般程序员（非程序库撰写者）的禁区。甚至运用模板较多的Boost，也成为了“众矢之的”。

但是实际上C++模板远没有想象的那么复杂。我们只需要换一个视角：在C++03的时候，模板本身就可以独立成为一门“语言”。它有“值”，有“函数”，有“表达式”和“语句”。除了语法比较蹩脚外，它既没有指针也没有数组，更没有C++里面复杂的继承和多态。可以说，它要比C语言要简单的多。如果我们把模板当做是一门语言来学习，那只需要花费学习OO零头的时间即可掌握。按照这样的思路，可以说在各种模板书籍中出现的多数技巧，都可以被轻松理解。

简单回顾一下模板的历史。87年的时候，泛型（Generic Programming）便被纳入了C++的考虑范畴，并直接导致了后来模板语法的产生。可以说模板语法一开始就是为了在C++中提供泛型机制。92年的时候，Alexander Stepanov开始研究利用模板语法制作程序库，后来这一程序库发展成STL，并在93年被接纳入标准中。

此时不少人以为STL已经是C++模板的集大成之作，C++模板技止于此。但是在95年的《C++ Report》上，John Barton和Lee Nackman提出了一个矩阵乘法的模板示例。可以说元编程在那个时候开始被很多人所关注。自此篇文章发表之后，很多大牛都开始对模板产生了浓厚的兴趣。其中对元编程技法贡献最大的当属Alexandrescu的《Modern C++ Design》及模板程序库Loki。这一2001年发表的图书间接地导致了模板元编程库的出现。书中所使用的Typelist等泛型组件，和Policy等设计方法令人耳目一新。但是因为全书用的是近乎Geek的手法来构造一切设施，因此使得此书阅读起来略有难度。

2002年出版的另一本书《C++ Templates》，可以说是在Template方面的集大成之作。它详细阐述了模板的语法、提供了和模板有关的语言细节信息，举了很多有代表性例子。但是对于模板新手来说，这本书细节如此丰富，让他们随随便便就打了退堂鼓缴械投降。

本文的写作初衷，就是通过“编程语言”的视角，介绍一个简单、清晰的“模板语言”。我会尽可能的将模板的诸多要素连串起来，用一些简单的例子帮助读者学习这门“语言”，让读者在编写、阅读模板代码的时候，能像 `if(exp) { dosomething(); }`一样的信手拈来，让“模板元编程”技术成为读者牢固掌握、可举一反三的有用技能。

###0.2 适宜读者群

因为本文并不是用于C++入门，例子中也多少会牵涉一些其它知识，因此如果读者能够具备以下条件，会读起来更加轻松：

* 熟悉C++的基本语法；
* 使用过STL；
* 熟悉一些常用的算法，以及递归等程序设计方法。

此外，尽管第一章会介绍一些Template的基本语法，但是还是会略显单薄。因此也希望读者能对C++ Template最基本语法形式有所了解和掌握；如果会编写基本的模板函数和模板类那就更好了。

诚如上节所述，本文并不是《C++ Templates》的简单重复，与《Modern C++ Design》交叠更少。从知识结构上，我建议大家可以先读本文，再阅读《C++ Templates》获取更丰富的语法与实现细节，以更进一步；《Modern C++ Design》除了元编程之外，还有很多的泛型编程示例，原则上泛型编程的部分与我所述的内容交叉不大，读者在读完1-3章了解模板的基本规则之后便可阅读《MCD》的相应章节；元编程部分（如Typelist）建议在阅读完本文之后再行阅读，或许会更易理解。

###0.3 版权

本文是随写随即同步到Github上，因此在行文中难免会遗漏引用。本文绝大部分内容应是直接承出我笔，但是也不定会有他山之石。所有指涉内容我会尽量以引号框记，或在上下文和边角注记中标示，如有遗漏烦请不吝指出。

全文所有为我所撰写的部分，作者均保留所有版权。如果有需要转帖或引用，还请注明出处并告知于我。

###0.4 意见、建议、喷、补遗、写作计划

* 需增加：
  * 模板的使用动机。
* 建议：
  * 比较模板和函数的差异性
  * 蓝色：C++14 Return type deduction for normal functions 的分析

## 1. Template的基本语法

###1.1 Template Class基本语法

####1.1.1 Template Class的与成员变量定义
我们来回顾一下最基本的Template Class声明和定义形式：

Template Class声明：
```C++
template <typename T> class ClassA;
```

Template Class定义：
```C++
template <typename T> class ClassA
{
	T member;
};
```

`template` 是C++关键字，意味着我们接下来将定义一个模板。和函数一样，模板也有一系列参数。这些参数都被囊括在template之后的`< >`中。在上文的例子中， `typename T`便是模板参数。回顾一下与之相似的函数参数的声明形式：

``` C++
void foo(int a);
```

`T`则可以类比为函数形参`a`，这里的“模板形参”`T`，也同函数形参一样取成任何你想要的名字；`typename`则类似于例子中函数参数类型`int`，它表示模板参数中的`T`将匹配一个类型。除了 `typename` 之外，我们再后面还要讲到，整型也可以作为模板的参数。

在定义完模板参数之后，便可以定义你所需要的类。不过在定义类的时候，除了一般类可以使用的类型外，你还可以使用在模板参数中使用的类型 `T`。可以说，这个 `T`是模板的精髓，因为你可以通过指定模板实参，将T替换成你所需要的类型。

例如我们用`ClassA<int>`来实例化模板类ClassA，那么`ClassA<int>`可以等同于以下的定义：

``` C++
// 注意：这并不是有效的C++语法，只是为了说明模板的作用
typedef class {
	int member;
} ClassA<int>;
```

可以看出，通过模板参数替换类型，可以获得很多形式相同的新类型，有效减少了代码量。这种用法，我们称之为“泛型”（Generic Programming），它最常见的应用，即是STL中的容器模板类。

####1.1.2 模板的使用

对于C++来说，类型最重要的作用之一就是用它去产生一个变量。例如我们定义了一个动态数组（列表）的模板类`vector`，它对于任意的元素类型都具有push_back和clear的操作，我们便可以如下定义这个类：

```C++
template <typename T>
class vector
{
public:
	void push_back(T const&);
	void clear();				
	
private:
	T* elements;
};
```

此时我们的程序需要一个整型和一个浮点型的列表，那么便可以通过以下代码获得两个变量：

```C++
vector<int> intArray;
vector<float> floatArray;
```

此时我们就可以执行以下的操作，获得我们想要的结果：

```C++
intArray.push_back(5);
floatArray.push_back(3.0f);
```

变量定义的过程可以分成两步来看：第一步，`vector<int>`将`int`绑定到模板类`vector`上，获得了一个“普通的类`vector<int>`”；第二步通过“vector<int>”定义了一个变量。
与“普通的类”不同，模板类是不能直接用来定义变量的。例如

```C++
vector unknownVector; // 错误示例
```

这样就是错误的。我们把通过类型绑定将模板类变成“普通的类”的过程，称之为模板实例化（Template Instantiate）。实例化的语法是：
 
```
模板名 < 模板实参1 [，模板实参2，...] >
```

看几个例子：
```C++
vector<int>
ClassA<double>

template <typename T0, typename T1> class ClassB
{
	// Class body ...
};

ClassB<int, float>
```

当然，在实例化过程中，被绑定到模板参数上的类型（即模板实参）需要与模板形参正确匹配。
就如同函数一样，如果没有提供足够并匹配的参数，模板便不能正确的实例化。
 
####1.1.3 模板类的成员函数定义

由于C++11正式废弃“模板导出”这一特性，因此在模板类的变量在调用成员函数的时候，需要看到完整的成员函数定义。因此现在的模板类中的成员函数，通常都是以内联的方式实现。
例如：

``` C++
template <typename T>
class vector
{
public:
	void clear()
	{
		// Function body
	}
	
private:
	T* elements;
};
```

当然，我们也可以将`vector<T>::clear`的定义部分放在类型之外，只不过这个时候的语法就显得蹩脚许多：

```C++
template <typename T>
class vector
{
public:
	void clear();			// 注意这里只有声明
private:
	T* elements;
};

template <typename T>
void vector<T>::clear()		// 函数的实现放在这里
{
	// Function body
}
```

函数的实现部分看起来略微拗口。我第一次学到的时候，觉得

``` C++
void vector::clear()
{
	// Function body
}
```

这样不就行了吗？但是简单想就会知道，`clear`里面是找不到泛型类型`T`的符号的。

因此，在成员函数实现的时候，必须要提供模板参数。此外，为什么类型名不是`vector`而是`vector<T>`呢？
如果你了解过模板的偏特化与特化的语法，应该能看出，这里的vector<T>在语法上类似于特化/偏特化。实际上，这里的函数定义也确实是成员函数的偏特化。特化和偏特化的概念，本文会在第二部分详细介绍。

综上，正确的成员函数实现如下所示：

``` C++
template <typename T>		// 模板参数
void vector<T> /*看起来像偏特化*/ ::clear()		// 函数的实现放在这里
{
	// Function body
}
```

###1.2 Template Function的基本语法

####1.2.1 Template Function的声明和定义

模板函数的语法与模板类基本相同，也是以关键字`template`和模板参数列表作为声明与定义的开始。模板参数列表中的类型，可以出现在参数、返回值以及函数体中。比方说下面几个例子

```C++
template <typename T> void foo(T const& v);

template <typename T> T foo();

template <typename T, typename U> U foo(T const&);

template <typename T> void foo()
{
	T var;
	// ...
}
```

无论是函数模板还是类模板，在实际代码中看起来都是“千变万化”的。这些“变化”，主要是因为类型被当做了参数，导致代码中可以变化的部分更多了。

归根结底，模板无外乎两点：

   1. 函数或者类里面，有一些类型我们希望它能变化一下，我们用标识符来代替它，这就是“模板参数”；

   2. 在需要这些类型的地方，写上相对应的标识符（“模板参数”）。

当然，这里的“可变”实际上在代码编译好后就固定下来了，可以称之为编译期的可变性。

这里多啰嗦一点，主要也是想告诉大家，模板其实是个很简单的东西。

下面这个例子，或许可以帮助大家解决以下两个问题：

  1. 什么样的需求会使用模板来解决？

  2. 怎样把脑海中的“泛型”变成真正“泛型”的代码？

```
举个例子：generic typed function ‘add’
```

在我遇到的朋友中，即便如此对他解释了模板，即便他了解了模板，也仍然会对模板产生畏难情绪。毕竟从形式上来说，模板类和模板函数都要较非模板的版本更加复杂，阅读代码所需要理解的内容也有所增多。

如何才能克服这一问题，最终视模板如平坦代码呢？

答案只有一个：无他，唯手熟尔。

在学习模板的时候，要反复做以下的思考和练习：

  1. 提出问题：我的需求能不能用模板来解决？

  2. 怎么解决？

  3. 把解决方案用代码写出来。

  4. 如果失败了，找到原因。是知识有盲点（例如不知道怎么将 `T&` 转化成 `T`），还是不可行（比如试图利用浮点常量特化模板类，但实际上这样做是不可行的）？

通过重复以上的练习，应该可以对模板的语法和含义都有所掌握。如果提出问题本身有困难，或许下面这个经典案例可以作为你思考的开始：

  1. 写一个泛型的数据结构：例如，线性表，数组，链表，二叉树；

  2. 写一个可以在不同数据结构、不同的元素类型上工作的泛型函数，例如求和；

当然和“设计模式”一样，模板在实际应用中，也会有一些固定的需求和解决方案。比较常见的场景包括：泛型（最基本的用法）、通过类型获得相应的信息（型别萃取）、编译期间的计算、类型间的推导和变换（从一个类型变换成另外一个类型，比如boost::function）。这些本文在以后的章节中会陆续介绍。

####1.2.2 模板函数的使用

我们先来看一个简单的函数模板，两个数相加：

``` C++
template <typename T> T Add(T a, T b)
{
	return a + b;
}
```

函数模板的调用格式是：

``` C++
函数模板名 < 模板参数列表 > ( 参数 )
```

例如，我们想对两个 `int` 求和，那么套用类的模板实例化方法，我们可以这么写：

``` C++
int a = 5;
int b = 3;
int result = Add<int>(a, b);
```

这时我们等于拥有了一个新函数：

``` C++
int Add<int>(int a, int b) { return a + b; }
```

这时在另外一个偏远的程序角落，你也需要求和。而此时你的参数类型是 `float` ，于是你写下：

``` C++
Add<float>(a, b);
```

一切看起来都很完美。但如果你具备程序员的最佳美德——懒惰——的话，你肯定会这样想，我在调用 `Add<int>(a, b)` 的时候， `a` 和 `b` 匹配的都是那个 `T`。编译器就应该知道那个 `T` 实际上是 `int` 呀？为什么还要我多此一举写 `Add<int>` 呢？
唔，我想说的是，编译器的作者也是这么想的。所以实际上你在编译器里面写下以下片段：

``` C++
int a = 5;
int b = 3;
int result = Add(a, b);
```

编译器会心领神会的将 `Add` 变成 `Add<int>`。但是编译器不能面对模棱两可的答案。比如你这么写的话呢？

``` C++
int  a = 5;
char b = 3;
int  result = Add(a, b);
```

第一个参数 `a` 告诉编译器，这个 `T` 是 `int`。编译器点点头说，好。但是第二个参数 `b` 不高兴了，告诉编译器说，你这个 `T`，其实是 `char`。
两个参数各自指导 `T` 的类型，编译器就不知道怎么做了。在Visual Studio 2012下，会有这样的提示：

```
error C2782: 'T _1_2_2::Add(T,T)' : template parameter 'T' is ambiguous
```

好吧，"ambigous"，这个提示再明确不过了。

不过，只要你别逼得编译器精神分裂的话，编译器其实是非常聪明的，它可以从很多的蛛丝马迹中，猜测到你真正的意图，有如下面的例子：

``` C++
template <typename T> class A {};

template <typename T> T foo( A<T> v );

A<int> v;
foo(v);	// 它能准确的猜到 T 是 int.
```

咦，编译器居然绕过了A这个外套，猜到了 `T` 匹配的是 `int`。编译器是怎么完成这一“魔法”的，我们暂且不表，2.2节时再和盘托出。

下面轮到你的练习时间了。你试着写了很多的例子，但是其中一个你还是犯了疑惑：

``` C++
float data[1024];

template <typename T> T GetValue(int i)
{
	return static_cast<T>(data[i]);
}

float a = GetValue(0);	// 出错了！
int b = GetValue(1);	// 也出错了！
```

为什么会出错呢？你仔细想了想，原来编译器是没办法去根据返回值推断类型的。函数调用的时候，返回值被谁接受还不知道呢。如下修改后，就一切正常了：

``` C++
float a = GetValue<float>(0);
int b = GetValue<int>(1);
```

嗯，是不是so easy啊？嗯，你又信心满满的做了一个练习：

你要写一个模板函数叫 `c_style_cast`，顾名思义，执行的是C风格的转换。然后出于方便起见，你希望它能和 `static_cast` 这样的内置转换有同样的写法。于是你写了一个use case。

``` C++
DstT dest = c_style_cast<DstT>(src);
```

根据调用形式你知道了，有 `DstT` 和 `SrcT` 两个模板参数。参数只有一个， `src`，所以函数的形参当然是这么写了： `(SrcT src)`。实现也很简单， `(DstT)v`。

我们把手上得到的信息来拼一拼，就可以编写自己的函数模板了：

``` C++
template <typename SrcT, typename DstT> DstT c_style_cast(SrcT v)
{
	return (DstT)(v);
}

int v = 0;
float i = c_style_cast<float>(v);
```

嗯，很Easy嘛！我们F6一下…咦！这是什么意思！

``` C++
error C2783: 'DstT _1_2_2::c_style_cast(SrcT)' : could not deduce template argument for 'DstT'
```

然后你仔细的比较了一下，然后发现 … 模板参数有两个，而参数里面能得到的只有 `SrcT` 一个。结合出错信息看来关键在那个 `DstT` 上。这个时候，你死马当活马医，把模板参数写完整了：

``` C++
float i = c_style_cast<int, float>(v);
```

嗯，很顺利的通过了。难道C++不能支持让参数推导一部分模板参数吗？

当然是可以的。只不过在部分推导、部分指定的情况下，编译器对模版参数的顺序是有限制的：先写需要指定的模板参数，再把能推导出来的模板参数放在后面。

在这个例子中，能推导出来的是 `SrcT`，需要指定的是 `DstT`。把函数模板写成下面这样就可以了：

``` C++
template <typename DstT, typename SrcT> DstT c_style_cast(SrcT v)	// 模版参数 DstT 需要人肉指定，放前面。
{
	return (DstT)(v);
}

int v = 0;
float i = c_style_cast<float>(v);  // 形象地说，DstT会先把你指定的参数吃掉，剩下的就交给编译器从函数参数列表中推导啦。
```

###1.3 整型也可是Template参数

模板参数除了类型外（包括基本类型、结构、类类型等），也可以是一个整型数（Integral Number）。这里的整型数比较宽泛，包括布尔、不同位数、有无符号的整型，甚至包括指针。我们将整型的模板参数和类型作为模板参数来做一个对比：

``` C++
template <typename T> class TemplateWithType;
template <int      V> class TemplateWithValue;
```

我想这个时候你也更能理解 `typename` 的意思了：它相当于是模板参数的“类型”，告诉你 `T` 是一个 `typename`。

按照C++ Template最初的想法，模板不就是为了提供一个类型安全、易于调试的宏吗？有类型就够了，为什么要引入整型参数呢？考虑宏，它除了代码替换，还有一个作用是作为常数出现。所以整型模板参数最基本的用途，也是定义一个常数。例如这段代码的作用：

``` C++
template <typename T, int Size> struct Array
{
	T data[Size];
};

Array<int, 16> arr;
```

便相当于下面这段代码：

``` C++
class IntArrayWithSize16
{
	int data[16];			// int 替换了 T, 16 替换了 Size
};

IntArrayWithSize16 arr;
```

其中有一点要注意的是，因为模板的匹配是在编译的时候完成的，所以实例化模板的时候所使用的参数，也必须要在编译期就能确定。例如以下的例子编译器就会报错：

``` C++
template <int i> class A {};

void foo()
{
	int x = 3;
	A<5> a;			// 正确！
	A<x> b;			// error C2971: '_1_3::A' : template parameter 'i' : 'x' : a local variable cannot be used as a non-type argument
}
```
因为x不是一个编译期常量，所以 `A<x>` 就会告诉你，x是一个局部变量，不能作为一个模板参数出现。

嗯，这里我们再来写几个相对复杂的例子：

``` C++
template <int i> class A 
{
public:
	void foo(int)
	{
	}
};
template <uint8_t a, typename b, void* c> class B {};
template <bool, void (*a)()> class C {};
template <void (A<3>::*a)(int)> class D {};

template <int i> int Add(int a)	// 当然也能用于函数模板
{
	return a + i;
}

void foo()
{
	A<5> a;
	B<
		7, A<5>, nullptr
	>				b;	// 模板参数可以是一个无符号八位整数，可以是模板生成的类；可以是一个指针。
	C<false, &foo>  c;	// 模板参数可以是一个bool类型的常量，甚至可以是一个函数指针。
	D<&A<3>::foo>   d;	// 丧心病狂啊！它还能是一个成员函数指针！
	int x = Add<3>(5);	// x == 8。因为整型模板参数无法从函数参数获得，所以只能是手工指定啦。
}

template <float a> class E {};		// ERROR: 别闹！早说过只能是整数类型的啦！
```

当然，除了单纯的用作常数之外，整型参数还有一些其它的用途。这些“其它”用途最重要的一点是让类型也可以像整数一样运算。《Modern C++ Design》给我们展示了很多这方面的例子。不过你不用急着去阅读那本天书，我们会在做好足够的知识铺垫后，让你轻松学会这些招数。

###1.4 模板形式与功能是统一的

第一章走马观花的带着大家复习了一下C++ Template的基本语法形式，也解释了包括 `typename` 在内，类/函数模板写法中各个语法元素的含义。形式是功能的外在体现，介绍它们也是为了让大家能理解到，模板之所以写成这种形式是有必要的，而不是语言的垃圾成分。

从下一章开始，我们便进入了更加复杂和丰富的世界：讨论模板的匹配规则。其中有令人望而生畏的特化与偏特化。但是，请相信我们在序言中所提到的：将模板作为一门语言来看待，它会变得有趣而简单。

## 2.  模板元编程基础
###2.1 编程，元编程，模板元编程

技术的学习是一个登山的过程。第一章是最为平坦的山脚道路。而从这一章开始，则是正式的爬坡。无论是我写作还是你阅读，都需要付出比第一章更多的代价。那么问题就是，付出更多的精力学习模板是否值得？

这个问题很功利，但是一阵见血。因为技术的根本目的在于解决需求。那C++的模板能做什么？

一个高（树）大（新）上（蜂）的回答是，C++里面的模板，犹如C中的宏、C#和Java中的自省（restropection）和反射（reflection）一样，是一个改变语言内涵，拓展语言外延的存在。

程序最根本的目的是什么？复现真实世界或人所构想的规律，减少重复工作的成本，或通过提升规模完成人所不能及之事。但是世间之事万千，有限的程序如何重现复杂的世界呢？

答案是“抽象”。论及具体手段，无外乎“求同”与“存异”：概括一般规律，处理特殊情况。这也是软件工程所追求的目标。一般规律概括的越好，我们所付出的劳动也就越少。

同样的，作为脑力劳动的产品，程序本身也是有规律性的。《Modern C++ Design》中的前言就抛出了一连串有代表性的问题：

```
如何撰写更高级的C++程式？
如何应付即使在很干净的设计中仍然像雪崩一样的不相干细节？
如何构建可复用组件，使得每次在不同程式中应用组件时无需大动干戈？
```

我们以数据结构举例。在程序里，你需要一些堆栈。这个堆栈的元素可能是整数、浮点或者别的什么类型。一份整型堆栈的代码可能是：

``` C++
class StackInt
{
public:
    void push(Int v);
    Int pop();
    Int Find(Int x)
    {
        for(Int i = 1; i <= size; )
        {
            if(data[i] == x) { return i; }
        }
    }
    // ... 其他代码 ...
};
```

如果你要支持浮点了，那么你只能将代码再次拷贝出来，并作如下修改：

``` C++
class StackFloat
{
public:
    void push(Float v);
    Float pop();
    Int Find(Float x)
    {
        for(Int i = 1; i <= size; )
        {
            if(data[i] == x) { return i; }
        }
    }
    // ... 其他代码 ...
};
```

当然也许你觉得这样做能充分体会代码行数增长的成就感。但是有一天，你突然发现：呀，`Find` 函数实现有问题了。怎么办？这个时候也许你只有两份这样的代码，那好说，一一去修正就好了。如果你有十个呢？二十个？五十个？

时间一长，你就厌倦了这样的生活。你觉得每个堆栈都差不多，但是又有点不一样。为了这一点点不一样，你付出了太多的时间。吃饭的时间，泡妞的时间，睡觉的时间，看岛国小电影顺便练习小臂力量的时间。

于是便诞生了新的技术，来消解我们的烦恼。

这个技术的名字，并不叫“模板”，而是叫“元编程”。

元（meta）无论在中文还是英文里，都是个很“抽象（abstract）”的词。因为它的本意就是“抽象”。元编程，也可以说就是“编程的抽象”。用更好理解的说法，元编程意味着你撰写一段程序A，程序A会运行后生成另外一个程序B，程序B才是真正实现功能的程序。那么这个时候程序A可以称作程序B的元程序，撰写程序A的过程，就称之为“元编程”。

回到我们的堆栈的例子。真正执行功能的，其实仍然是浮点的堆栈、整数的堆栈、各种你所需要的类型的堆栈。但是因为这些堆栈之间太相似了，仅仅有着些微的不同，我们为什么不能有一个将相似之处囊括起来，同时又能分别体现出不同之处的程序呢？很多语言都提供了这样的机会。C中的宏，C++中的模板，Python中的Duck Typing，广义上将都能够实现我们的思路。

我们的目的，是找出程序之间的相似性，进行“元编程”。而在C++中，元编程的手段，可以是宏，也可以是模板。

宏的例子姑且不论，我们来看一看模板：

``` C++
template <typename T>
class Stack
{
public:
    void push(T v);
    T pop();
    Int Find(T x)
    {
        for(Int i = 0; i <= size; ++i)
        {
            if(data[i] == x) { return i; }
        }
    }
    // ... 其他代码 ...
};

typedef Stack<int>   StackInt;
typedef Stack<float> StackFloat;
```

通过模板，我们可以将形形色色的堆栈代码分为两个部分，一个部分是不变的接口，以及近乎相同的实现；另外一部分是元素的类型，它们是需要变化的。因此同函数类似，需要变化的部分，由模板参数来反应；不变的部分，则是模板内的代码。可以看到，使用模板的代码，要比不使用模板的代码简洁许多。

如果元编程中所有的变化的量（或者说元编程的参数），都是类型，那么这样的编程，我们有个特定的称呼，叫“泛型”。

但是你会问，模板的发明，仅仅是为了做和宏几乎一样的替换工作吗？可以说是，也可以说不是。一方面，很多时候模板就是为了替换类型，这个时候作用上其实和宏没什么区别。只是宏是基于文本的替换，被替换的文本本身没有任何语义。只有替换完成，编译器才能进行接下来的处理。而模板会在分析模板时以及实例化模板时时候都会进行检查，而且源代码中也能与调试符号一一对应，所以无论是编译时还是运行时，排错都相对简单。

但是模板也和宏有很大的不同，否则此文也就不能成立了。模板最大的不同在于它是“可以运算”的。我们来举一个例子，不过可能有点牵强。考虑我们要写一个向量逐分量乘法。只不过这个向量，它非常的大。所以为了保证速度，我们需要使用SIMD指令进行加速。假设我们有以下指令可以使用：

```
Int8,16: N/A
Int32  : VInt32Mul(int32 * 4, int32 * 4)
Int64  : VInt64Mul(int64 * 2, int64 * 2)
Float  : VInt64Mul(float * 2, float * 2)
```
所以对于Int8和Int16，我们需要提升到Int32，而Int32和Int64，各自使用自己的指令。所以我们需要实现下的逻辑：

``` C++
for(v4a, v4b : vectorsA, vectorsB)
{
    if type is Int8, Int16
		VInt32Mul( ConvertToInt32(v4a), ConvertToInt32(v4b) )
	elif type is Int32
		VInt32Mul( v4a, v4b )
	elif type is Float
		...
}
```

这里的问题就在于，如何根据 `type` 分别提供我们需要的实现？这里有两个难点。首先， `if(type == xxx) {}` 是不存在于C++中的。第二，即便存在根据 `type` 的分配方法，我们也不希望它在运行时branch，这样会变得很慢。我们希望它能按照类型直接就把代码编译好，就跟直接写的一样。

嗯，聪明你果然想到了，重载也可以解决这个问题。

``` C++
GenericMul(int8  * 4, int8  * 4);
GenericMul(int16 * 4, int16 * 4);
GenericMul(int32 * 4, int32 * 4);
GenericMul(int64 * 4, int64 * 4);
// 其它 Generic Mul ...

for(v4a, v4b : vectorsA, vectorsB)
{
    GenericMul(v4a, v4b);
}

```

这样不就可以了吗？

唔，你赢了，是这样没错。但是问题是，我这个平台是你可没见过，它叫 `Deep Thought`， 特别缺心眼儿，不光有 `int8`，还有更奇怪的 `int9`, `int11`，以及可以代表世间万物的 `int42`。你总不能为之提供所有的重载吧？这简直就像你枚举了所有程序的输入，并为之提供了对应的输出一样。

好吧，我承认这个例子还是太牵强了。不过相信我，在你阅读完第二章和第三章之后，你会将这些特性自如地运用到你的程序之中。你的程序将会变成体现模板“可运算”威力的最好例子。

###2.2 模板世界的If-Then-Else：类模板的特化与偏特化

####2.2.1 根据类型执行代码
前一节的示例提出了一个要求：需要做出根据类型执行不同代码。要达成这一目的，模板并不是唯一的途径。比如之前我们所说的重载。如果把眼界放宽一些，虚函数也是根据类型执行代码的例子。此外，在C语言时代，也会有一些技法来达到这个目的，比如下面这个例子，我们需要对两个浮点做加法， 或者对两个整数做乘法：

``` C
struct Variant
{
	union
	{
		int x;
		float y;
	} data;
	uint32 typeId;
};

Variant addFloatOrMulInt(Variant const* a, Variant const* b)
{
	Variant ret;
	assert(a->typeId == b->typeId);
	if (a->typeId == TYPE_INT)
	{
		ret.x = a->x * b->x;
	}
	else
	{
		ret.y = a->y + b->y;
	}
	return ret;
}

```

更常见的是 `void*`:

``` C++
#define BIN_OP(type, a, op, b, result) (*(type const *)(result)) = (*(type const *)(a)) op (*(type const*)(b))
void doDiv(void* out, void const* data0, void const* data1, DATA_TYPE type)
{
	if(type == TYPE_INT)
	{
		BIN_OP(int, data0, *, data1, out);
	}
	else
	{
		BIN_OP(float, data0, +, data1, out);
	}
}
```

在C++中比如在 `Boost.Any` 的实现中，运用了 `typeid` 来查询类型信息。和 `typeid` 同属于RTTI机制的 `dynamic_cast`，也经常会用来做类型判别的工作。我想你应该写过类似于下面的代码：

``` C++
IAnimal* animal = GetAnimalFromSystem();

IDog* maybeDog = dynamic_cast<IDog*>(animal);
if(maybeDog)
{
	maybeDog->Wangwang();
}
ICat* maybeCat = dynamic_cast<ICat*>(animal);
if(maybeCat)
{
	maybeCat->Moemoe();
}
```

当然，在实际的工作中，我们建议把需要 `dynamic_cast` 后执行的代码，尽量变成虚函数。不过这个已经是另外一个问题了。我们看到，不管是哪种方法都很难避免 `if` 的存在。而且因为输入数据的类型是模糊的，经常需要强制地、没有任何检查的转换成某个类型，因此很容易出错。

但是模板与这些方法最大的区别并不在这里。模板无论其参数或者是类型，它都是一个编译期分派的办法。编译期就能确定的东西既可以做类型检查，编译器也能进行优化，砍掉任何不必要的代码执行路径。例如在上例中，

``` C++
template <typename T> T addFloatOrMulInt(T a, T b);

// 迷之代码1：用于T是float的情况

// 迷之代码2：用于T是int时的情况
```

如果你运用了模板来实现，那么当传入两个不同类型的变量，或者不是 `int` 和 `float` 变量，编译器就会提示错误。但是如果使用了我们前述的 `Variant` 来实现，编译器可就管不了那么多了。但是，成也编译期，败也编译期。最严重的“缺点”，就是你没办法根据用户输入或者别的什么在运行期间可能发生变化的量来决定它产生、或执行什么代码。比如下面的代码段，它是不成立的。

``` C++

template <int i, int j>
int foo() { return i + j; }
int main()
{
	cin >> x >> y;
	return foo<x, y>();
}

```

这点限制也粉碎了妄图用模板来包办工厂（Factory）甚至是反射的梦想。尽管在《Modern C++ Design》中（别问我为什么老举这本书，因为《C++ Templates》和《Generic Programming》我只是囫囵吞枣读过，基本不记得了)大量运用模板来简化工厂方法；同时C++11和14中的一些机制如Vardric Template更是让这一问题的解决更加彻底。但无论如何，光靠模板你就是写不出依靠类名或者ID变量产生类型实例的代码。

所以说，从能力上来看，模板能做的事情都是编译期完成的。编译期完成的意思就是，当你编译一个程序的时候，所有的量就都已经确定了。比如下面的这个例子：

``` C++
int a = 3, b = 5;
Variant aVar, bVar;
aVar.setInt(a);			// 我们新加上的方法，怎么实现的无所谓，大家明白意思就行了。
bVar.setInt(b);
Variant result = addFloatOrMulInt(aVar, bVar);
```

除非世界末日，否则这个例子里不管你怎么蹦跶，单看代码我们就能知道， `aVar` 和 `bVar` 都一定会是整数。所以如果有合适的机制，编译器就能知道此处的 `addFloatOrMulInt` 中只需要执行 `Int` 路径上的代码，而且编译器在此处也能单独为 `Int` 路径生成代码，从而去掉那个不必要的 `if`。

在模板代码中，这个“合适的机制”就是指“特化”和“部分特化（Partial Specialization）”，后者也叫“偏特化”。

####2.2.2 特化

我的高中物理老师对我说过一句令我受用至今的话：把自己能做的事情做好。编写模板程序也是一样。当你试图用模板解决问题之前，先撇开那些复杂的语法要素，用最直观的方式表达你的需求：

``` C++
// 这里是伪代码，意思一下

int|float addFloatOrMulInt(a, b)
{
	if(type is Int)
	{
		return a * b;
	}
	else if (type is Float)
	{
		return a + b;
	}
}

void foo()
{
	float a, b, c;
	c = addFloatOrMulInt(a, b);		// c = a + b;
	
	int x, y, z;
	z = addFloatOrMulInt(x, y);		// z = x * y;
}
```

因为这一节是讲类模板有关的特化和偏特化机制，所以我们不用普通的函数，而是用类的静态成员函数来做这个事情（这就是典型的没事找抽型）：

``` C++
// 这里仍然是伪代码，意思一下，too。
class AddFloatOrMulInt
{
	static int|float Do(a, b)
	{
		if(type is Int)
		{
			return a * b;
		}
		else if (type is Float)
		{
			return a + b;
		}
	}
};

void foo()
{
	float a, b, c;
	c = AddFloatOrMulInt::Do(a, b);		// c = a + b;
	
	int x, y, z;
	z = AddFloatOrMulInt::Do(x, y);		// z = x * y;
}
```

好，意思表达清楚了。我们先从调用方的角度，把这个形式改写一下：

``` C++
void foo()
{
	float a, b, c;
	c = AddFloatOrMulInt<float>::Do(a, b);		// c = a + b;
	
	int x, y, z;
	z = AddFloatOrMulInt<int>::Do(x, y);		// z = x * y;
}
```
也许你不明白为什么要改写成现在这个样子。看不懂不怪你，怪我讲的不好。但是你别急，先看看这样改写以后能不能跟我们的目标接近一点。如果我们把 `AddFloatOrMulInt<float>::Do` 看作一个普通的函数，那么我们可以写两个实现出来：

``` C++
float AddFloatOrMulInt<float>::Do(float a, float b)
{
	return a + b;
}

int AddFloatOrMulInt<int>::Do(int a, int b)
{
	return a * b;
}

void foo()
{
	float a, b, c;
	c = AddFloatOrMulInt<float>::Do(a, b);		// c = a + b;
	
	int x, y, z;
	z = AddFloatOrMulInt<int>::Do(x, y);		// z = x * y;
}
```

这样是不是就很开心了？我们更进一步，把 `AddFloatOrMulInt<int>::Do` 换成合法的类模板：

``` C++
// 这个是给float用的。
template <typename T> class AddFloatOrMulInt
{
	T Do(T a, T b)
	{
		return a + b;
	}
};

// 这个是给int用的。
template <typename T> class AddFloatOrMulInt
{
	T Do(T a, T b)
	{
		return a * b;
	}
};

void foo()
{
	float a, b, c;

	// 嗯，我们需要 c = a + b;
	c = AddFloatOrMulInt<float>::Do(a, b);		
	// ... 觉得哪里不对劲 ...
	// ...
	// ...
	// ...
	// 啊！有两个AddFloatOrMulInt，class看起来一模一样，要怎么区分呢！
}
```
好吧，问题来了！如何要让两个内容不同，但是模板参数形式相同的类进行区分呢？特化！特化（specialization）是根据一个或多个特殊的整数或类型，给出模板实例化时的一个指定内容。我们先来看特化是怎么应用到这个问题上的。
``` C++
// 首先，要写出模板的一般形式（原型）
template <typename T> class AddFloatOrMulInt
{
	static T Do(T a, T b)
	{
		// 在这个例子里面一般形式里面是什么内容不重要，因为用不上
		// 这里就随便给个0吧。
		return T(0);
	}
};

// 其次，我们要指定T是int时候的代码，这就是特化：
template <> class AddFloatOrMulInt<int>
{
public:
	static int Do(int a, int b) // 
	{
		return a * b;
	}
};

// 再次，我们要指定T是float时候的代码：
template <> class AddFloatOrMulInt<float>
{
public:
	static float Do(float a, float b)
	{
		return a + b;
	}
};

void foo()
{
	// 这里面就不写了
}
```
我们再把特化的形式拿出来一瞧：这货有点怪啊： `template <> class AddFloatOrMulInt<int>`。别急，我给你解释一下。

``` C++
// 我们这个模板的基本形式是什么？
template <typename T> class AddFloatOrMulInt;

// 但是这个类，是给T是Int的时候用的，于是我们写作
class AddFloatOrMulInt<int>
// 当然，这里编译是通不过的。

// 但是它又不是个普通类，而是类模板的一个特化（特例）。
// 所以前面要加模板关键字template，
// 以及模板参数列表
template </* 这里要填什么？ */> class AddFloatOrMulInt<int>;

// 最后，模板参数列表里面填什么？因为原型的T已经被int取代了。所以这里就不能放任何额外的参数了。
// 所以这里要放空。
template <> class AddFloatOrMulInt<int>
{
	// ... 针对Int的实现 ... 
}

// Bingo!
```

哈，这样就好了。我们来做一个练习。我们有一些类型，然后你要用模板做一个对照表，让类型对应上一个数字。我先来做一个示范：

``` C++

template <typename T> class TypeToID
{
public:
	static int const ID = -1;
};

template <> class TypeToID<uint8_t>
{
public:
	static int const ID = 0;
};
```

然后呢，你的任务就是，要所有无符号的整数类型的特化（其实就是`uint8_t`到`uint64_t`啦），把所有的基本类型都赋予一个ID（当然是不一样的啦）。当你做完后呢，可以把类型所对应的ID打印出来，我仍然以 `uint8_t` 为例：

``` C++
void PrintID()
{
	cout << "ID of uint8_t: " << TypeToID<uint8_t>::ID << endl;
}
```
嗯，看起来挺简单的，是吧。但是这里透露出了一个非常重要的信号，我希望你已经能察觉出来了： `TypeToID` 如同是一个函数。这个函数只能在编译期间执行。它输入一个类型，输出一个ID。

如果你体味到了这一点，那么恭喜你，你的模板元编程已经开悟了。

####2.2.3 特化：一些其它问题

在上一节结束之后，你一定做了许多的练习。我们再来做三个练习。第一，给`float`一个ID；第二，给`void*`一个ID；第三，给任意类型的指针一个ID。先来做第一个:

``` C++
// ...
// TypeToID 的模板“原型”
// ...

template <typename T> class TypeToID<float>
{
	static int const ID = 0xF10A7;
};
```

嗯， 这个你已经了然于心了。那么`void*`呢？你想了想，这已经是一个复合类型了。不错你还是战战兢兢的写了下来：

``` C++
template <> class TypeToID<void*>
{
	static int const ID = 0x401d;
};

void PrintID()
{
	cout << "ID of uint8_t: " << TypeToID<void*>::ID << endl;
}
```

遍译运行一下，对了。模板不过如此嘛。然后你觉得自己已经完全掌握了，并试图将所有C++类型都放到模板里面，开始了自我折磨的过程：

``` C++
class ClassB {};

template <> class TypeToID<void ()>;			// 函数的TypeID
template <> class TypeToID<int[3]>;				// 数组的TypeID
template <> class TypeToID<int (int[3])>;		// 这是以数组为参数的函数的TypeID
template <> class TypeToID<
	int (ClassB::*[3])(void*, float[2])>;		// 我也不知道这是什么了，自己看着办吧。
```

甚至连 `const` 和 `volatile` 都能装进去

``` C++
template <> class TypeToID<int const * volatile * const volatile>;
```

此时就很明白了，只要 `<>` 内填进去的是一个C++能解析的合法类型，模板都能让你特化。不过这个时候如果你一点都没有写错的话， `PrintID` 中只打印了我们提供了特化的类型的ID。那如果我们没有为之提供特化的类型呢？比如说double？OK，实践出真知，我们来尝试着运行一下：

``` C++
void PrintID()
{
	cout << "ID of double: " << TypeToID<double>::ID << endl;
}
```

嗯，它输出的是-1。我们顺藤摸瓜会看到， `TypeToID`的类模板“原型”的ID是值就是-1。通过这个例子可以知道，当模板实例化时提供的模板参数不能匹配到任何的特化形式的时候，它就会去匹配类模板的“原型”形式。

不过这里有一个问题要厘清一下。和继承不同，类模板的“原型”和它的特化类在实现上是没有关系的，并不是在类模板中写了 `ID` 这个Member，那所有的特化就必须要加入 `ID` 这个Member，或者特化就自动有了这个成员。完全没这回事。我们把类模板改成以下形式，或许能看的更清楚一点：

``` C++
template <typename T> class TypeToID
{
public:
	static int const NotID = -2;
};

template <> class TypeToID<float>
{
public:
	static int const ID = 1;
};

void PrintID()
{
	cout << "ID of float: " << TypeToID<float>::ID << endl;	// Print "1"
	cout << "NotID of float: " << TypeToID<float>::NotID << endl;	// Error! TypeToID<float>使用的特化的类，这个类的实现没有NotID这个成员。
	cout << "ID of double: " << TypeToID<double>::ID << endl;	// Error! TypeToID<double>是由模板类实例化出来的，它只有NotID，没有ID这个成员。
}
```

这样就明白了。类模板和类模板的特化的作用，仅仅是指导编译器选择哪个编译，但是特化之间、特化和它原型的类模板之间，是分别独立实现的。所以如果多个特化、或者特化和对应的类模板有着类似的内容，很不好意思，你得写上若干遍了。

第三个问题，是写一个模板匹配任意类型的指针。对于C语言来说，因为没有泛型的概念，因此它提供了无类型的指针`void*`。它的优点是，所有指针都能转换成它。它的缺点是，一旦转换称它后，你就再也不知道这个指针到底是指向`float`或者是`int`或者是`struct`了。

比如说`copy`。

``` C
void copy(void* dst, void const* src, size_t elemSize, size_t elemCount, void (*copyElem)(void* dstElem, void const* srcElem))
{
	void const* reader = src;
	void const* writer = dst;
	for(size_t i = 0; i < elemCount; ++i)
	{
		copyElem(writer, reader);
		advancePointer(reader, elemSize);	// 把Reader指针往后移动一些字节
		advancePointer(writer, elemSize);
	}
}
```

为什么要提供copyElem，是因为可能有些struct需要深拷贝，所以得用特殊的copy函数。这个在C++98/03里面就体现为拷贝构造和赋值函数。
但是不管怎么搞，因为这个函数的参数只是`void*`而已，当你使用了错误的elemSize，或者传入了错误的copyElem，就必须要到运行的时候才有可能看出来。注意，这还只是有可能而已。


那么C++有了模板后，能否既能匹配任意类型的指针，同时又保留了类型信息呢？答案是显然的。至于怎么写，那就得充分发挥你的直觉了：

首先，我们需要一个`typename T`来指代“任意类型”这四个字：

``` C++
template <typename T>
```

接下来，我们要写函数原型:

``` C++
void copy(?? dest, ?? src, size_t elemCount);
```

这里的 `？？` 要怎么写呢？既然我们有了模板类型参数T，那我们不如就按照经验，写 `T*` 看看。

``` C++
template <typename T>
void copy(T* dst, T const* src, size_t elemCount);
```

编译一下，咦，居然通过了。看来这里的语法与我们以前学到的知识并没有什么不同。这也是语言设计最重要的一点原则：一致性。它可以让你辛辛苦苦体验到的规律不至于白费。
最后就是实现：

``` C++
template <typename T>
void copy(T* dst, T const* src, size_t elemCount)
{
	for(size_t i = 0; i < elemCount; ++i)
	{
		dst[i] = src[i];
	}
}
```

是不是简洁了许多？你不需要再传入size；只要你有正确的赋值函数，也不需要提供定制的copy；也不用担心dst和src的类型不匹配了。

最后，我们把函数模板学到的东西，也应用到类模板里面：

``` C++
template <typename T>					// 嗯，需要一个T
class TypeToID<T*>						// 我要对所有的指针类型特化，所以这里就写T*
{
public:
	static int const ID = 0x80000000;	// 用最高位表示它是一个指针
};
```

最后写个例子来测试一下，看看我们的 `T*` 能不能搞定 `float*`

``` C++
void PrintID()
{
	cout << "ID of float*: " << TypeToID<float*>::ID << endl;
}
```

哈哈，大功告成。嗯，别急着高兴。待我问一个问题：你知道 `TypeToID<float*>` 后，这里的T是什么吗？换句话说，你知道下面这段代码打印的是什么吗？

``` C++
// ...
// TypeToID 的其他代码，略过不表
// ...

template <typename T>					// 嗯，需要一个T
class TypeToID<T*>						// 我要对所有的指针类型特化，所以这里就写T*
{
public:
	typedef T		 SameAsT;
	static int const ID = 0x80000000;	// 用最高位表示它是一个指针
};

void PrintID()
{
	cout << "ID of float*: " << TypeToID< TypeToID<float*>::SameAsT >::ID << endl;
}
```

别急着运行，你先猜。

-------------------------  这里是给勤于思考的码猴的分割线  -------------------------------

OK，猜出来了吗，T是`float`。为什么呢？因为你用 `float *` 匹配了 `T *`，所以 `T` 就对应 `float` 了。没想清楚的自己再多体会一下。

嗯，所以实际上，我们可以利用这个特性做一件事情：把指针类型的那个指针给“干掉”：

``` C++
template <typename T>
class RemovePointer
{
	// 啥都不干，你要放一个不是指针的类型进来，我就让你死的难看。
};

template <typename T>
class RemovePointer<T*>	// 祖传牛皮藓，专治各类指针
{
public:
	typedef T Result;
};

void Foo()
{
	RemovePointer<float*>::Result x = 5.0f;		// 喏，用RemovePointer后，那个Result就是把float*的指针处理掉以后的结果：float啦。
	std::cout << x << std::endl;
}
```

OK，如果这个时候，我需要给 `int*` 提供一个更加特殊的特化，那么我还得都多提供一个：

``` C++
// ...
// TypeToID 的其他代码，略过不表
// ...

template <typename T>					// 嗯，需要一个T
class TypeToID<T*>						// 我要对所有的指针类型特化，所以这里就写T*
{
public:
	typedef T		 SameAsT;
	static int const ID = 0x80000000;	// 用最高位表示它是一个指针
};

template <>								// 嗯，int* 已经是个具体的不能再具体的类型了，所以模板不需要额外的类型参数了
class TypeToID<int*>					// 嗯，对int*的特化。在这里呢，要把int*整体看作一个类型。
{
public:
	static int const ID = 0x12345678;	// 给一个缺心眼的ID
};

void PrintID()
{
	cout << "ID of int*: " << TypeToID<int*>::ID << endl;
}
```

嗯，这个时候它会输出0x12345678的十进制（大概？）。
可能会有较真的人说，`int*` 去匹配 `T` 或者 `T*`，也是合法的。就和你说22岁以上能结婚，那24岁当然也能结婚一样。
那为什么 `int*` 就会找 `int*`，`float *`因为没有合适的特化就去找 `T*`，更一般的就去找 `T` 呢？废话，有专门为你准备的东西的不用，人干事？这就是直觉。
但是呢，直觉对付更加复杂的问题还是没用的（也不是没用，主要是你没这个直觉了）。我们要把这个直觉，转换成合理的规则——即模板的匹配规则。
当然，这个匹配规则是对复杂问题用的，所以我们会到实在一眼看不出来的时候才会动用它。一开始我们只要把握：模板是从最特殊到最一般形式进行匹配就可以了。


###2.3 函数模板的重载、参数匹配、特化与部分特化
###2.4 技巧单元：模板与继承

## 3   拿起特化的武器，去写程序吧！
###3.1 利用模板特化规则实现If-Then-Else与Switch-Case
###3.2 特化可以有多个选择：替换失败并不是一个错误，只是一种可能
###3.3 技巧单元：获得类型的属性——类型萃取（Type Traits） 

## 4   用模板写程序吧！骚年！
###4.1 模板上的递归
###4.2 将循环变成递归，将分支变成递归，将一切变成递归
###4.3 实战单元：元编程的Fibonacci数列
###4.4 技巧单元：typename与template的另一种用法
###4.5 实战单元：撰写你自己的元编程“函数”库
###4.6 实战单元：实现元编程上的数据结构——以Vector为例

## 5   关于模板，你还需要知道的其它常识
###5.1 类中类：灵活的模板定义
###5.2 Template-Template Class
###5.3 技巧单元：高阶函数——从函数到函数的组合
###5.4 实战单元：STL中的Allocator Rebinder
###5.5 像看堆栈一样的看出错信息
###5.6 模板的症结：易于实现，难于完美

alexandrescu 关于 min max 的讨论：《再谈Min和Max》

## 6   C++11的新特性
###6.1 变参模板
###6.2 Lambda与模板程序

## 7   模板的威力：从foreach, transform到Linq
###7.1 Foreach与Transform
###7.2 Reactor风格的编程
###7.3 Reactor与Linq
###7.4 Linq的C++实践
###7.5 更高更快更强：从Linq到FP

## 8   结语：讨论有益，争端无用
