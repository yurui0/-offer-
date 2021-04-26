// 64_Accumulate.cpp : 定义控制台应用程序的入口点。
//

// 面试题64：求1+2+…+n
// 题目：求1+2+…+n，要求不能使用乘除法、for、while、if、else、switch、case
// 等关键字及条件判断语句（A?B:C）。

#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;

// ====================方法一==================== //运用构造函数求解，将累加的代码放到构造函数中
class Temp
{
public:
	Temp() { ++N; Sum += N; }//构造函数，每次调用就加一，然后加到总和sum中
	//下面定义为静态变量就是方便调用，因为是算法，这样通过类名直接调用更加方便
	static void Reset() { N = 0; Sum = 0; }//每次调用就更新为初始状态，以免之前操作的影响
	static unsigned int GetSum() { return Sum; }//返回sum

private:
	static unsigned int N;
	static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution1(unsigned int n)//方法1的输入口
{
	Temp::Reset();

	Temp *a = new Temp[n];//根据n的个数创建多个对象，这里是创建对象数组，个数为n，即相当于调用了n次构造函数
	delete[]a;
	a = NULL;

	return Temp::GetSum();
}

// ====================方法二====================//利用虚函数求解
class A;
A* Array[2];

class A
{
public:
	virtual unsigned int Sum(unsigned int n)
	{
		return 0;

	}
};

class B : public A
{
public:
	virtual unsigned int Sum(unsigned int n)
	{
		return Array[!!n]->Sum(n - 1) + n;//这里！n=0,!!n=1，无论n为哪个整数，正负数都一样（0除外）,如果n为0，仅此一例，此时！n=1,!!n=0
										// 因此当n不为0的时候，就是调用Array[1]的sum进行加法，当n为0，则调用的是虚基类中的sum，返回0说明终止递归
	}
};

int Sum_Solution2(int n)//方法二的输入口
{
	A a;
	B b;
	Array[0] = &a;
	Array[1] = &b;

	int value = Array[1]->Sum(n);

	return value;
}

// ====================方法三====================//在纯C语言环境下不能使用虚函数，因此我们可以使用函数指针来模拟
typedef unsigned int(*fun)(unsigned int);

unsigned int Solution3_Teminator(unsigned int n)
{
	return 0;
}

unsigned int Sum_Solution3(unsigned int n)//方法三的输入口
{
	static fun f[2] = { Solution3_Teminator, Sum_Solution3 };
	return n + f[!!n](n - 1);//f[!!n]中!!n与上面叙述的一致，这里不再详细描述
}

// ====================方法四====================
template <unsigned int n> struct Sum_Solution4 //这里是使用模板类型进行求解，让编译器帮我们完成
{
	enum Value { N = Sum_Solution4<n - 1>::N + n };
};

template <> struct Sum_Solution4<1>
{
	enum Value { N = 1 };
};

template <> struct Sum_Solution4<0>
{
	enum Value { N = 0 };
};

// ====================测试代码====================
void Test(int n, int expected)
{
	printf("Test for %d begins:\n", n);

	if (Sum_Solution1(n) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (Sum_Solution2(n) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	if (Sum_Solution3(n) == expected)
		printf("Solution3 passed.\n");
	else
		printf("Solution3 failed.\n");
}

void Test1()
{
	const unsigned int number = 1;
	int expected = 1;
	Test(number, expected);
	if (Sum_Solution4<number>::N == expected)
		printf("Solution4 passed.\n");
	else
		printf("Solution4 failed.\n");
}

void Test2()
{
	const unsigned int number = 5;
	int expected = 15;
	Test(number, expected);
	if (Sum_Solution4<number>::N == expected)
		printf("Solution4 passed.\n");
	else
		printf("Solution4 failed.\n");
}

void Test3()
{
	const unsigned int number = 10;
	int expected = 55;
	Test(number, expected);
	if (Sum_Solution4<number>::N == expected)
		printf("Solution4 passed.\n");
	else
		printf("Solution4 failed.\n");
}

void Test4()
{
	const unsigned int number = 0;
	int expected = 0;
	Test(number, expected);
	if (Sum_Solution4<number>::N == expected)
		printf("Solution4 passed.\n");
	else
		printf("Solution4 failed.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	//cout << endl;
	//cout << !!0<< endl; //其中！n=0,!!n=1无论n取正负（0除外）,如果n为0，仅此一例，此时！n=1,!!n=0

	return 0;
}

