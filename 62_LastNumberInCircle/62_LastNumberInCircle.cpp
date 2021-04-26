// 62_LastNumberInCircle.cpp : 定义控制台应用程序的入口点。
//

// 面试题62：圆圈中最后剩下的数字
// 题目：0, 1, …, n-1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里
// 删除第m个数字。求出这个圆圈里剩下的最后一个数字。

#include "stdafx.h"

#include <cstdio>
#include <list>

using namespace std;
//Std::list是支持常数时间从容器任何位置插入和移除元素的容器。不支持快速随机访问。它通常实现为双向链表。


// ====================方法1====================
int LastRemaining_Solution1(unsigned int n, unsigned int m)//经典解法，用环形链表模拟圆圈，n和m分别表示圆圈中n个数字，每次删除其第m个数字
{
	if (n < 1 || m < 1)//输入是否合法
		return -1;

	unsigned int i = 0;

	list<int> numbers;//声明元素类型为Int的双向链表list
	for (i = 0; i < n; ++i)//这里是将元素插入链表末端，数据范围为[0,n-1]
		numbers.push_back(i);

	list<int>::iterator current = numbers.begin();//指向双向链表第一个元素：双向链表不是循环链表，因此下面第一个循环就是模拟循环链表的作用
	while (numbers.size() > 1)//链表中是否还有多于一个的元素，因为如果其size=1，说明其就是最后剩下的数字
	{
		//注：end说明该迭代器指向的是末尾元素的下一个元素位置，即超过了链表的范围，一般作为终止条件
		for (int i = 1; i < m; ++i)//模拟循环链表，即根据m的值不断移动
		{
			current++;
			if (current == numbers.end())//如果移动到end(即链表末尾元素的下一个位置，此位置超过了链表的范围)就将其移动到首部
				current = numbers.begin();
		}

		list<int>::iterator next = ++current;//这里是运用一个辅助链表来记录第m个数字后面的一个数字
		if (next == numbers.end())//如果该迭代器指向的是链表末尾元素的下一个位置,就将其移动到首部
			next = numbers.begin();

		--current;//让current回到第m个元素，因为之前为了记录第m个元素后面一个元素，将其又向前移动了一位，因此将其还原
		numbers.erase(current);// 删除current指定的节点
		current = next;//将该迭代器赋值为想一个元素的迭代器，因为是链表，因此当前位置迭代器删除不影响后续迭代器，如果是顺序容器就不能这么做
	}

	return *(current);
}

// ====================方法2====================
// 这种方法比较难想，因为有一定创新性且思路分析较为复杂
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)//判断思路是否合法
		return -1;

	//下面是递归公式的实现，具体看剑指offer303页
	int last = 0;
	for (int i = 2; i <= n; i++)
		last = (last + m) % i;

	return last;
}

// ====================测试代码====================
void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	if (LastRemaining_Solution1(n, m) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (LastRemaining_Solution2(n, m) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	printf("\n");
}

void Test1()
{
	Test("Test1", 5, 3, 3);
}

void Test2()
{
	Test("Test2", 5, 2, 2);
}

void Test3()
{
	Test("Test3", 6, 7, 4);
}

void Test4()
{
	Test("Test4", 6, 6, 3);
}

void Test5()
{
	Test("Test5", 0, 0, -1);
}

void Test6()
{
	Test("Test6", 4000, 997, 1027);
}



int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}

