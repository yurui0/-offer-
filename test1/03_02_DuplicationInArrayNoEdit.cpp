// test1.cpp : 定义控制台应用程序的入口点。
/*
剑指offer第三题的补充题目2，不修改数组找出重复的数组
题目：在一个长度为n+1的数组里的所有数字都在1-n的范围内，所以数组中至少有一个数字说重复的，请找出数组中任意一个重复的数字，但是
不能修改输入的数组。
*/

//思路：
// 二分法，假如没有重复的数字，那么1-n中只有n个数字，因此将1-n的数字二分为1-m、m+1-n，如果1-m的数字数目超过m，那么这个区间就包含重复数字，否则就是另一区间，然后再次二分


#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned int UNIT_32;

int countRange(vector<UNIT_32> numbers, UNIT_32 length, UNIT_32 start, UNIT_32 end);


int getDuplication(vector<UNIT_32> numbers, UNIT_32 length)
{
	if (numbers.empty() || length <= 0)
	{
		return -1;
	}
	UNIT_32 start = 1;
	UNIT_32 end = length - 1;
	while (end >= start)//保证vector中至少有两个数据，这样才有可能重复，否则仅有一个数据不存在重复
	{
		UNIT_32 middle = ((end - start) >> 1) + start; //右移>>,表示除2
		UNIT_32 count = countRange(numbers,length,start,middle);//该函数计算vector在start和middle范围中数的个数
		if (end == start)// 循环判断到最后
		{
			if (count > 1)
				return start;
			else
				break;
		}

		if (count > (middle - start + 1))// 计算的start-middle之间的数据的数量比两者之差还大，说明有重复的在他们之间
			end = middle;
		else  //反之就在middle+1-end之间
			start = middle + 1;
		
	}
	//仅有一个数据不存在重复
	return -1;

}

int countRange(vector<UNIT_32> numbers, UNIT_32 length, UNIT_32 start, UNIT_32 end)
{
	if (numbers.empty())
		return 0;

	int count = 0;
	for (int i = 0; i < length; ++i)
	{
		if (numbers[i] >= start && numbers[i] <= end) //计算在该范围内的数的个数
			++count;
	}
	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{

	cout << "请输入创建数组的大小" << endl;
	UNIT_32 n;
	UNIT_32 m;
	cin >> n;
	vector<UNIT_32> v1;
	cout << "请依次输入数组中的数据" << endl;
	for (auto i = 0; i < n; ++i)
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

	UNIT_32 result;
	result = getDuplication(v1, n-1);
	cout << "结果是" << result << endl;

	return 0;
}

