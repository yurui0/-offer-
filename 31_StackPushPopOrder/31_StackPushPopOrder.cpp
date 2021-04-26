// 31_StackPushPopOrder.cpp : 定义控制台应用程序的入口点。
//
// 面试题31：栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
// 否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
// 5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，但
// 4、3、5、1、2就不可能是该压栈序列的弹出序列。

#include "stdafx.h"

#include <cstdio>
#include <stack>

//其中pPush是第一个序列，即栈的压入顺序；pPop是第二个序列，即待判断的栈的弹出顺序；最后一个参数是序列的长度
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool bPossible = false;//判断第二个序列是否为栈的压入顺序

	if (pPush != nullptr && pPop != nullptr && nLength > 0)//进行判断的前提条件
	{
		const int* pNextPush = pPush;//
		const int* pNextPop = pPop;//

		std::stack<int> stackData;//辅助栈，把输入的序列压入栈

		while (pNextPop - pPop < nLength)//序列中元素没有全部压入栈的话
		{
			// 当辅助栈的栈顶元素不是要弹出的元素
			// 先压入一些数字入栈
			while (stackData.empty() || stackData.top() != *pNextPop)//压入数据到栈，直到找到和第二个序列中栈弹出一样的数据
			{
				// 如果所有数字都压入辅助栈了，退出循环
				if (pNextPush - pPush == nLength)
					break;

				stackData.push(*pNextPush);//

				pNextPush++;
			}

			if (stackData.top() != *pNextPop)//到这个条件判断的情况是：输入序列的数据都被压入栈，此时还没有数据和输出序列匹配，则跳出循环
				break;

			stackData.pop();//否则说明找到，即出栈，查找下一个
			pNextPop++;
		}

		if (stackData.empty() && pNextPop - pPop == nLength)//辅助栈清空，且第二个序列也清空
			bPossible = true;
	}

	return bPossible;
}

// ====================测试代码====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (IsPopOrder(pPush, pPop, nLength) == expected)
		printf("Passed.\n");
	else
		printf("failed.\n");
}

void Test1()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 4, 5, 3, 2, 1 };

	Test("Test1", push, pop, nLength, true);
}

void Test2()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 3, 5, 4, 2, 1 };

	Test("Test2", push, pop, nLength, true);
}

void Test3()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 4, 3, 5, 1, 2 };

	Test("Test3", push, pop, nLength, false);
}

void Test4()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 3, 5, 4, 1, 2 };

	Test("Test4", push, pop, nLength, false);
}

// push和pop序列只有一个数字
void Test5()
{
	const int nLength = 1;
	int push[nLength] = { 1 };
	int pop[nLength] = { 2 };

	Test("Test5", push, pop, nLength, false);
}

void Test6()
{
	const int nLength = 1;
	int push[nLength] = { 1 };
	int pop[nLength] = { 1 };

	Test("Test6", push, pop, nLength, true);
}

void Test7()
{
	Test("Test7", nullptr, nullptr, 0, false);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	return 0;
}

