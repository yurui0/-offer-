// 19_RegularExpressionsMatching.cpp : 定义控制台应用程序的入口点。
//

// 面试题19：正则表达式匹配
// 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
// 表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
// 中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
// 和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。

#include "stdafx.h"
#include <cstdio>

bool matchCore(const char* str, const char* pattern);

bool match(const char* str, const char* pattern) //用来匹配正则表达式的主类
{
	if (str == nullptr || pattern == nullptr) //字符串和正则表达式必须非空
		return false;

	return matchCore(str, pattern);//符合条件后，用来计算的表达式
}

bool matchCore(const char* str, const char* pattern)
{
	if (*str == '\0' && *pattern == '\0')//当字符串和正则表达式此时的值都为'\0'--即全部匹配完成，说明两者匹配成功
		return true;

	if (*str != '\0' && *pattern == '\0')//如果字符串没有到末尾，此时正则表达式到末尾，说明肯定没有匹配成功
		return false;

	if (*(pattern + 1) == '*') //如果当前正则表达式下标处的字母，其后面一个字符是*，说明要特别处理
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))// 当前正则表达式位置的字符和字符串当前位置相匹配，或 是.匹配
			// 进入有限状态机的下一个状态
			return matchCore(str + 1, pattern + 2) 
			// 继续留在有限状态机的当前状态 
			|| matchCore(str + 1, pattern)       
			// 略过一个'*' 
			|| matchCore(str, pattern + 2);    
		else
			// 略过一个'*'，即正则表达式往后移动两位
			return matchCore(str, pattern + 2);
	}

	if (*str == *pattern || (*pattern == '.' && *str != '\0'))//如果当前正则表达式下标处的字母和当前字符串下标处的字母相匹配
																// 或者当前正则表达式下标为.，字符串是非末尾的任意一个字符----对应正常匹配和.匹配的条件
		return matchCore(str + 1, pattern + 1);//此时正则表达式和字符串都往后移动一位

	return false;
}

// ====================测试代码====================
void Test(const char* testName, const char* string, const char* pattern, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (match(string, pattern) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test("Test01", "", "", true);
	Test("Test02", "", ".*", true);
	Test("Test03", "", ".", false);
	Test("Test04", "", "c*", true);
	Test("Test05", "a", ".*", true);
	Test("Test06", "a", "a.", false);
	Test("Test07", "a", "", false);
	Test("Test08", "a", ".", true);
	Test("Test09", "a", "ab*", true);
	Test("Test10", "a", "ab*a", false);
	Test("Test11", "aa", "aa", true);
	Test("Test12", "aa", "a*", true);
	Test("Test13", "aa", ".*", true);
	Test("Test14", "aa", ".", false);
	Test("Test15", "ab", ".*", true);
	Test("Test16", "ab", ".*", true);
	Test("Test17", "aaa", "aa*", true);
	Test("Test18", "aaa", "aa.a", false);
	Test("Test19", "aaa", "a.a", true);
	Test("Test20", "aaa", ".a", false);
	Test("Test21", "aaa", "a*a", true);
	Test("Test22", "aaa", "ab*a", false);
	Test("Test23", "aaa", "ab*ac*a", true);
	Test("Test24", "aaa", "ab*a*c*a", true);
	Test("Test25", "aaa", ".*", true);
	Test("Test26", "aab", "c*a*b", true);
	Test("Test27", "aaca", "ab*a*c*a", true);
	Test("Test28", "aaba", "ab*a*c*a", false);
	Test("Test29", "bbbba", ".*a*a", true);
	Test("Test30", "bcbbabab", ".*a*a", false);

	return 0;
}

