// 38_StringPermutation.cpp : 定义控制台应用程序的入口点。
//
// 面试题38：字符串的排列
// 题目：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc，
// 则打印出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。

#include "stdafx.h"

#include <cstdio>

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
	if (pStr == nullptr)//判断是否合法
		return;

	Permutation(pStr, pStr);
}

// 例如字符串 abcd，则
void Permutation(char* pStr, char* pBegin)//第一个字符串pStr指向整个字符串的第一个字符，第二个字符串pBefin表示当前我们执行排列操作的字符串的第一个字符
{											//注：这里传递的是指针，因此pStr会因为pBegin的变换而变换，因为他们都指向同一个字符串
	if (*pBegin == '\0')
	{
		printf("%s\n", pStr);
	}
	else
	{
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			//第一个字母和后一个pch所指字母，进行交换
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);

			//第一个字母和其后一个字母的所有情况都考虑完成之后，需要将位置还原，为的是做好交换第一个字母与下下个字母交换的准备
			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}

// ====================测试代码====================
void Test(char* pStr)
{
	if (pStr == nullptr)
		printf("Test for nullptr begins:\n");
	else
		printf("Test for %s begins:\n", pStr);

	Permutation(pStr);

	printf("\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test(nullptr);

	char string1[] = "";
	Test(string1);

	char string2[] = "a";
	Test(string2);

	char string3[] = "ab";
	Test(string3);

	char string4[] = "abc";
	Test(string4);
	return 0;
}

