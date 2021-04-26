// test.cpp : 定义控制台应用程序的入口点。
/*
剑指offer 题目3 运用vector重写后的代码
题目：找出数组中重复的数字
	在一个长度为 n 的数组里的所有数字都在 0 到 n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字是重复的，也不知道每个数字重复几次。请找出数组中任意一个重复的数字。

*/

//

#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;

typedef unsigned int UNIT_32;

bool duplicate(vector<UNIT_32> numbers, UNIT_32 length, vector<UNIT_32> *duplication)
{
	if (numbers.empty() || length <= 0)     //前置条件                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	{
		return false;
	}

	for (auto it = numbers.begin(); it != numbers.end(); ++it) //判断数组是否合法
	{
		if (*it < 0 || *it >length - 1)
		{
			return false;
		}
	}

	
	for (auto i = 0; i < length; ++i)
	{
		while (numbers[i] != i) //一直处理直到数组中第i个位置的数据值为i
		{
			if (numbers[i]==numbers[numbers[i]]) //将i位置处的值和num[该值]比较，为的就是找出重复的数据
			{
				duplication->emplace_back(numbers[i]);//push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；而 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
				return true;
			}
			// 如果不满足就交换彼此，再次判断
			UNIT_32 temp = numbers[i];
			numbers[i] = numbers[temp];
			numbers[temp] = temp;

		}
	}




}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "请输入创建数组的大小" << endl;
	UNIT_32 n;
	UNIT_32 m;
	cin >> n;
	vector<UNIT_32> v1;
	cout << "请依次输入数组中的数据" << endl;
	for (auto i = 0; i < n;++i)
	{
		cin >> m;
		v1.emplace_back(m);
	}
	vector<UNIT_32>::iterator it;
	cout << "||||" << endl;
	for (it = v1.begin(); it != v1.end(); ++it)
	{
		cout << *it << endl;
	}
	vector<UNIT_32> result;
	bool test = false;
	test=duplicate(v1, n, &result);

	if (test)
	{
		cout << "重复元素为：" << endl;
		for (it = result.begin(); it != result.end(); ++it)
		{
			cout << *it << endl;
		}
	}
	else
		cout << "没有重复元素" << endl;
	

	return 0;
}

