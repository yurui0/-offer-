// test2.cpp : 定义控制台应用程序的入口点。
/*
面试题4：二维数组中的查找，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数

*/
//

#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned int UNIT_32;

bool Find(vector<vector<UNIT_32> > obj, UNIT_32 rows, UNIT_32 columns, UNIT_32 number)
{
	bool found = false;

	if (!obj.empty() && rows > 0 && columns > 0) //前置条件
	{
		UNIT_32 row = 0;
		UNIT_32 column = columns - 1;
		while (row < rows && column >= 0)//数组要满足一定的条件，要合法
		{
			if (obj[row][column] == number)
			{
				found = true;
				break;
			}
			else if (obj[row][column] > number)//因为obj[row][column]都比Number大了，那么在往下查找，即row增加就没有意义，因为从上往下是递增的
				--column;
			else // 同理，obj[row][column]都比Number小了，其右边不可能再去遍历（上个条件过滤了），因此要找到只可能是往下找
				++row;

		}

	}

	return found;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "请输入创建二维数组的行列号" << endl;
	UNIT_32 m;//行
	UNIT_32 n;//列
	cin >> m;
	cin >> n;
	vector<vector<UNIT_32> > obj(m, vector<UNIT_32>(n)); //定义二维动态数组5行6列 

	cout << "请按照从上到下/从左到右的顺序依次输入数组" << endl;
	for (auto i = 0; i < obj.size(); i++)//输入二维动态数组 //行
	{
		for (auto j = 0; j < obj[i].size(); j++)  //列
		{
			cin >> obj[i][j] ;
		}
	}

	/* 输出二维动态数组，检测是否正确。
	for (int i = 0; i < obj.size(); i++)//输出二维动态数组 
	{
		for (int j = 0; j < obj[i].size(); j++)
		{
			cout << obj[i][j] << " ";
		}
		cout << "\n";
	}
	*/
	cout << "请输入想要查询的数字（unsigned int类型）" << endl;
	UNIT_32 l;
	cin >> l;
	bool result;
	result=Find(obj, m, n, l);
	if (result)
		cout << "找到" << endl;
	else
		cout << "没找到" << endl;

	return 0;
}

