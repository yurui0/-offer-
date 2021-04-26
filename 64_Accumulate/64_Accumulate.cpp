// 64_Accumulate.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������64����1+2+��+n
// ��Ŀ����1+2+��+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case
// �ȹؼ��ּ������ж���䣨A?B:C����

#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;

// ====================����һ==================== //���ù��캯����⣬���ۼӵĴ���ŵ����캯����
class Temp
{
public:
	Temp() { ++N; Sum += N; }//���캯����ÿ�ε��þͼ�һ��Ȼ��ӵ��ܺ�sum��
	//���涨��Ϊ��̬�������Ƿ�����ã���Ϊ���㷨������ͨ������ֱ�ӵ��ø��ӷ���
	static void Reset() { N = 0; Sum = 0; }//ÿ�ε��þ͸���Ϊ��ʼ״̬������֮ǰ������Ӱ��
	static unsigned int GetSum() { return Sum; }//����sum

private:
	static unsigned int N;
	static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution1(unsigned int n)//����1�������
{
	Temp::Reset();

	Temp *a = new Temp[n];//����n�ĸ�������������������Ǵ����������飬����Ϊn�����൱�ڵ�����n�ι��캯��
	delete[]a;
	a = NULL;

	return Temp::GetSum();
}

// ====================������====================//�����麯�����
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
		return Array[!!n]->Sum(n - 1) + n;//���n=0,!!n=1������nΪ�ĸ���������������һ����0���⣩,���nΪ0������һ������ʱ��n=1,!!n=0
										// ��˵�n��Ϊ0��ʱ�򣬾��ǵ���Array[1]��sum���мӷ�����nΪ0������õ���������е�sum������0˵����ֹ�ݹ�
	}
};

int Sum_Solution2(int n)//�������������
{
	A a;
	B b;
	Array[0] = &a;
	Array[1] = &b;

	int value = Array[1]->Sum(n);

	return value;
}

// ====================������====================//�ڴ�C���Ի����²���ʹ���麯����������ǿ���ʹ�ú���ָ����ģ��
typedef unsigned int(*fun)(unsigned int);

unsigned int Solution3_Teminator(unsigned int n)
{
	return 0;
}

unsigned int Sum_Solution3(unsigned int n)//�������������
{
	static fun f[2] = { Solution3_Teminator, Sum_Solution3 };
	return n + f[!!n](n - 1);//f[!!n]��!!n������������һ�£����ﲻ����ϸ����
}

// ====================������====================
template <unsigned int n> struct Sum_Solution4 //������ʹ��ģ�����ͽ�����⣬�ñ��������������
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

// ====================���Դ���====================
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
	//cout << !!0<< endl; //���У�n=0,!!n=1����nȡ������0���⣩,���nΪ0������һ������ʱ��n=1,!!n=0

	return 0;
}

