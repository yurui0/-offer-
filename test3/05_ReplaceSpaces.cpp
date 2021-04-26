// test3.cpp : 定义控制台应用程序的入口点。
/*
面试5：替换空格：请实现一个函数，把字符串中的每个空格都替换成“%20”，例如“hello world”->“hello%20world”
要求：其中原数组声明的足够大，就在这个数组中进行替换操作，运用o(n)的时间的解法，把字符串中的空格替换成%20
*/

//思路：因为时间效率o(n^2)太大，原因就是从前往后移动字符的话，对于每个空格都会移动o(n)个字符，而若有o(n)个字符，则时间效率就是o(n^2)
//因此考虑另一个思路,为何不使用两个指针



#include "stdafx.h"
#include<iostream>
//#include<istream>
#include <cstdio>
#include <cstring>
#include<fstream>
#include <string>
using namespace std;

typedef unsigned int UNIT_32;

void ReplaceBlank(char str[], UNIT_32 len)
{
	if (str == nullptr || len <= 0)
	{
		return ;
	}

	/*originallen为字符串str的实际长度，len表示char数组的总长度（包括空格）*/
	UNIT_32 originallen = 0;
	UNIT_32 numberofBlank = 0;
	UNIT_32 i = 0;
	while (str[i] != '\0')
	{
		++originallen;//计算有值的字符的个数

		if (str[i] == ' ')
			++numberofBlank;//计算空格的个数
		++i;
	}

	/* newlen 为加入%20之后的字符串的长度*/
	UNIT_32 newlen = originallen + 2 * numberofBlank;

	if (newlen > len)//判断有没越界，因为题目说明原来数组足够大！                                                                                     
	{
		return ;
	} 

	
	UNIT_32 indexOfOriginal = originallen;
	UNIT_32 indexOfNew = newlen;

	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)//指针还没指到最前面，且空格还还处理完
	{
		if (str[indexOfOriginal] == ' ')//如果
		{
			str[indexOfNew--] = '0';
			str[indexOfNew--] = '2';
			str[indexOfNew--] = '%';
		}

		else
		{
			str[indexOfNew--] = str[indexOfOriginal];//这里是先使用原来的indexofnew，然后其值减1，即没有遇到空格的话就将数据依次后移
		}
		//这里单独拿出来是因为如果有连续的空格，且--操作在else里面的话，那么下一次循环时，前一个指针没有移动，从而有错误
		--indexOfOriginal;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	
	//cout << "we are happy." << endl;
	//char s[100]="we are happy.";
	char s[100];
	gets_s(s);
	cout << "将空格替换" << endl;

	ReplaceBlank(s, 100);
	cout << s << endl;

	return 0;
}

