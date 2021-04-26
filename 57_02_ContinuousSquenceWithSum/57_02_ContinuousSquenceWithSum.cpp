// 57_02_ContinuousSquenceWithSum.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������57��������Ϊs��������������
// ��Ŀ������һ������s����ӡ�����к�Ϊs�������������У����ٺ�������������
// ��������15������1+2+3+4+5=4+5+6=7+8=15�����Խ����ӡ��3����������1��5��
// 4��6��7��8��

#include "stdafx.h"
#include <cstdio>

void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
	if (sum < 3) //��ĿҪ����������������˲�����ֱ������
		return; //û�з���ֵ�ĺ�������,������ú����˳�

	int small = 1;//ָ��ǰ��ָ��
	int big = 2; //ָ������ָ��
	int middle = (1 + sum) / 2; //������ȷ����ֹ��������small����sum��һ���ʱ�򣬴�ʱ����������Ĵ�����
	int curSum = small + big;

	while (small < middle)
	{
		if (curSum == sum)//���ǰ��ָ����ڵĺ͵���sum�����ӡ������֮�������
			PrintContinuousSequence(small, big);

		while (curSum > sum && small < middle)//�����ǰֵҪ��sum�󣬲��Ҵ�ʱsmall��û�е���ֹ���������Сsmall�𲽱ƽ�
		{
			curSum -= small;
			small++;

			if (curSum == sum)
				PrintContinuousSequence(small, big);
		}
		// �����������while����--����ǰֵҪ��sumС����big����
		big++; //����Ҳ�Ǳ�֤bigҪ��small��������small��С��middleʱ�ſ���˵���п��ܶ��ҹ�
		curSum += big;
	}
}

void PrintContinuousSequence(int small, int big)//��ӡ������ָ��֮�������
{
	for (int i = small; i <= big; ++i)
		printf("%d ", i);

	printf("\n");
}

// ====================���Դ���====================
void Test(const char* testName, int sum)
{
	if (testName != nullptr)
		printf("%s for %d begins: \n", testName, sum);

	FindContinuousSequence(sum);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test("test1", 1);
	Test("test2", 3);
	Test("test3", 4);
	Test("test4", 9);
	Test("test5", 15);
	Test("test6", 100);

	return 0;
}

