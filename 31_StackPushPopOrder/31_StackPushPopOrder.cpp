// 31_StackPushPopOrder.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������31��ջ��ѹ�롢��������
// ��Ŀ�����������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ���������
// ��Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ���������1��2��3��4��
// 5��ĳջ��ѹջ���У�����4��5��3��2��1�Ǹ�ѹջ���ж�Ӧ��һ���������У���
// 4��3��5��1��2�Ͳ������Ǹ�ѹջ���еĵ������С�

#include "stdafx.h"

#include <cstdio>
#include <stack>

//����pPush�ǵ�һ�����У���ջ��ѹ��˳��pPop�ǵڶ������У������жϵ�ջ�ĵ���˳�����һ�����������еĳ���
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool bPossible = false;//�жϵڶ��������Ƿ�Ϊջ��ѹ��˳��

	if (pPush != nullptr && pPop != nullptr && nLength > 0)//�����жϵ�ǰ������
	{
		const int* pNextPush = pPush;//
		const int* pNextPop = pPop;//

		std::stack<int> stackData;//����ջ�������������ѹ��ջ

		while (pNextPop - pPop < nLength)//������Ԫ��û��ȫ��ѹ��ջ�Ļ�
		{
			// ������ջ��ջ��Ԫ�ز���Ҫ������Ԫ��
			// ��ѹ��һЩ������ջ
			while (stackData.empty() || stackData.top() != *pNextPop)//ѹ�����ݵ�ջ��ֱ���ҵ��͵ڶ���������ջ����һ��������
			{
				// ����������ֶ�ѹ�븨��ջ�ˣ��˳�ѭ��
				if (pNextPush - pPush == nLength)
					break;

				stackData.push(*pNextPush);//

				pNextPush++;
			}

			if (stackData.top() != *pNextPop)//����������жϵ�����ǣ��������е����ݶ���ѹ��ջ����ʱ��û�����ݺ��������ƥ�䣬������ѭ��
				break;

			stackData.pop();//����˵���ҵ�������ջ��������һ��
			pNextPop++;
		}

		if (stackData.empty() && pNextPop - pPop == nLength)//����ջ��գ��ҵڶ�������Ҳ���
			bPossible = true;
	}

	return bPossible;
}

// ====================���Դ���====================
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

// push��pop����ֻ��һ������
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

