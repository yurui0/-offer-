// 30_MinInStack.cpp : 定义控制台应用程序的入口点。
//
// 面试题30：包含min函数的栈
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min
// 函数。在该栈中，调用min、push及pop的时间复杂度都是O(1)。

#include "stdafx.h"

#include <cstdio>
#include "StackWithMin.h"

//这一题的思路就是，调用push和pop其时间复杂度都是O(1),这个肯定没有问题，因此最主要的就是使得获得栈中最小值的min函数的时间复杂度为O(1)
//很容易就想到新加一个栈，随后在栈中只压入当前压入第一个栈中的最小的值，这样第二个栈的栈顶就始终是最小的元素
//


void Test(const char* testName, const StackWithMin<int>& stack, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (stack.min() == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	StackWithMin<int> stack;

	stack.push(3);
	Test("Test1", stack, 3);

	stack.push(4);
	Test("Test2", stack, 3);

	stack.push(2);
	Test("Test3", stack, 2);

	stack.push(3);
	Test("Test4", stack, 2);

	stack.pop();
	Test("Test5", stack, 2);

	stack.pop();
	Test("Test6", stack, 3);

	stack.pop();
	Test("Test7", stack, 3);

	stack.push(0);
	Test("Test8", stack, 0);
	return 0;
}

