// 58_01_ReverseWordsInSentence.cpp : 定义控制台应用程序的入口点。
//

// 面试题58（一）：翻转单词顺序
// 题目：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
// 为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，
// 则输出"student. a am I"。

#include "stdafx.h"

#include <cstdio>
#include "StringUtil.h"
#include <string>

char* ReverseSentence(char *pData)
{
	if (pData == nullptr)//输入是否合法
		return nullptr;

	char *pBegin = pData;//这个是指向字符串首节点
	//以下步骤是得到指向字符串尾节点的指针
	char *pEnd = pData;
	while (*pEnd != '\0')
		pEnd++;
	pEnd--;//因为上面循环条件截止是指向'\0'，所以需要在减去一个


	// 翻转整个句子
	Reverse(pBegin, pEnd); //这个函数用于实现（翻转字符串中的一段，即begin与end之间的）

	// 翻转句子中的每个单词
	pBegin = pEnd = pData;
	while (*pBegin != '\0')
	{
		if (*pBegin == ' ')//说明此时pbedin是指向的间隔，因此将两个指针都向前移动一位，跳过他
		{
			pBegin++;
			pEnd++;
		}
		else if (*pEnd == ' ' || *pEnd == '\0')//*pEnd == ' '说明一个单词读完，*pEnd == '\0'说明读到字符串末尾
		{
			Reverse(pBegin, --pEnd);//翻转这个字符串，--pend是因为其指向单词后一位
			pBegin = ++pEnd;
		}
		else //此时说明一个单词还没读完，因此继续移动end
			pEnd++;
	}

	return pData;
}

// ====================测试代码====================
void Test(const char* testName, char* input, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	ReverseSentence(input);

	if ((input == nullptr && expectedResult == nullptr)
		|| (input != nullptr && strcmp(input, expectedResult) == 0))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// 功能测试，句子中有多个单词
void Test1()
{
	char input[] = "I am a student.";
	char expected[] = "student. a am I";

	Test("Test1", input, expected);
}

// 功能测试，句子中只有一个单词
void Test2()
{
	char input[] = "Wonderful";
	char expected[] = "Wonderful";

	Test("Test2", input, expected);
}

// 鲁棒性测试
void Test3()
{
	Test("Test3", nullptr, nullptr);
}

// 边界值测试，测试空字符串
void Test4()
{
	Test("Test4", "", "");
}

// 边界值测试，字符串中只有空格
void Test5()
{
	char input[] = "   ";
	char expected[] = "   ";
	Test("Test5", input, expected);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}

