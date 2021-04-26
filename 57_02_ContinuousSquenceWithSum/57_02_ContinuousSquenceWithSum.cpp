// 57_02_ContinuousSquenceWithSum.cpp : 定义控制台应用程序的入口点。
//

// 面试题57（二）：为s的连续正数序列
// 题目：输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、
// 4～6和7～8。

#include "stdafx.h"
#include <cstdio>

void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
	if (sum < 3) //题目要求最少两个数，因此不符合直接跳出
		return; //没有返回值的函数里面,如果想让函数退出

	int small = 1;//指向前面指针
	int big = 2; //指向后面的指针
	int middle = (1 + sum) / 2; //这里是确定终止条件，即small到达sum的一半的时候，此时就无需后续的处理了
	int curSum = small + big;

	while (small < middle)
	{
		if (curSum == sum)//如果前后指针对于的和等于sum，则打印出两者之间的数据
			PrintContinuousSequence(small, big);

		while (curSum > sum && small < middle)//如果当前值要比sum大，并且此时small还没有到终止条件，则减小small逐步逼近
		{
			curSum -= small;
			small++;

			if (curSum == sum)
				PrintContinuousSequence(small, big);
		}
		// 不满足上面的while条件--即当前值要比sum小，则big扩大
		big++; //这里也是保证big要比small大，这样当small不小于middle时才可以说所有可能都找过
		curSum += big;
	}
}

void PrintContinuousSequence(int small, int big)//打印出两个指针之间的数据
{
	for (int i = small; i <= big; ++i)
		printf("%d ", i);

	printf("\n");
}

// ====================测试代码====================
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

