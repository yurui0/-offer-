// 30_MinInStack.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������30������min������ջ
// ��Ŀ������ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ����СԪ�ص�min
// �������ڸ�ջ�У�����min��push��pop��ʱ�临�Ӷȶ���O(1)��

#include "stdafx.h"

#include <cstdio>
#include "StackWithMin.h"

//��һ���˼·���ǣ�����push��pop��ʱ�临�Ӷȶ���O(1),����϶�û�����⣬�������Ҫ�ľ���ʹ�û��ջ����Сֵ��min������ʱ�临�Ӷ�ΪO(1)
//�����׾��뵽�¼�һ��ջ�������ջ��ֻѹ�뵱ǰѹ���һ��ջ�е���С��ֵ�������ڶ���ջ��ջ����ʼ������С��Ԫ��
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

