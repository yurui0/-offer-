// 50_01_FirstNotRepeatingChar.cpp : 定义控制台应用程序的入口点。
//

// 面试题50（一）：字符串中第一个只出现一次的字符
// 题目：在字符串中找出第一个只出现一次的字符。如输入"abaccdeff"，则输出
// 'b'。

#include "stdafx.h"
#include <cstdio>
#include <string>

char FirstNotRepeatingChar(const char* pString)//输入一个字符串，将其转为const char *
{
	if (pString == nullptr)
		return '\0';

	const int tableSize = 256;//因为字符只有8bit，只有256个字符
	unsigned int hashTable[tableSize]; //一个一维数组
	for (unsigned int i = 0; i < tableSize; ++i)
		hashTable[i] = 0;

	const char* pHashKey = pString;
	while (*(pHashKey) != '\0')//根据char数组中每个字母的ASCALL码值作为下标
		hashTable[*(pHashKey++)] ++;

	pHashKey = pString;
	while (*pHashKey != '\0')//第二次扫描，找出hash表中第一次出现值为1的结果
	{
		if (hashTable[*pHashKey] == 1)
			return *pHashKey;

		pHashKey++;
	}

	return '\0';
}

// ====================测试代码====================
void Test(const char* pString, char expected)
{
	if (FirstNotRepeatingChar(pString) == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 常规输入测试，存在只出现一次的字符
	Test("google", 'l');

	// 常规输入测试，不存在只出现一次的字符
	Test("aabccdbd", '\0');

	// 常规输入测试，所有字符都只出现一次
	Test("abcdefg", 'a');

	// 鲁棒性测试，输入nullptr
	Test(nullptr, '\0');


	return 0;
}

