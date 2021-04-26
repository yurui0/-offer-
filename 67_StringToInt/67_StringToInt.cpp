// 67_StringToInt.cpp : 定义控制台应用程序的入口点。
//

// 面试题67：把字符串转换成整数
// 题目：请你写一个函数StrToInt，实现把字符串转换成整数这个功能。当然，不
// 能使用atoi或者其他类似的库函数。

#include "stdafx.h"
#include <cstdio>

//模仿c++的atio函数
long long StrToIntCore(const char* str, bool minus);

enum Status { kValid = 0, kInvalid };//特殊标记，用来判断输入是否为非法输入，将其赋值为kInvalid表示输入不合法，赋值为kValid表示输入合法
int g_nStatus = kValid;

int StrToInt(const char* str)
{
	g_nStatus = kInvalid;//一开始默认标记为不合法
	long long num = 0;

	if (str != nullptr && *str != '\0')//判断输入字符串是否为不为空且不为空字符串，则进行后续操作
	{
		bool minus = false;//当字符串中第一个字符为符号位的时候，判断其是正还是负，正->false,负->true
		if (*str == '+')
			str++;
		else if (*str == '-')
		{
			str++;
			minus = true;
		}

		if (*str != '\0')
			num = StrToIntCore(str, minus);//开始将字符串转为数字
	}
	//否则直接输出0，且标记记为不合法kInvalid
	return (int)num;
}

long long StrToIntCore(const char* digit, bool minus)//将字符串转为数字，第一个参数是字符串，第二个参数是标识数据正负的
{
	long long num = 0;

	while (*digit != '\0')//字符串没有到末尾
	{
		if (*digit >= '0' && *digit <= '9')//
		{
			int flag = minus ? -1 : 1;//minus为true表示负数，flag为‘-1’，否则为false，flag为‘+1’
			num = num * 10 + flag * (*digit - '0');//计算数字

			if ((!minus && num > 0x7FFFFFFF) //如果num超过了正负数的范围，说明存在溢出现象，此时也不能完成转换
				|| (minus && num < (signed int)0x80000000))
			{
				num = 0;
				break;
			}

			digit++;
		}
		else//如果字符串不符合‘0’-‘9’的范围，说明不能转为数字，因此返回0，并跳出当前循环
		{
			num = 0;
			break;
		}
	}

	if (*digit == '\0')//如果从上面的while运行完，且当前的digit的值为字符串末尾符，则说明已经转换为数字，因为如果是不符合上面while跳出，则*digit ！= '\0'，标记仍是kInvalid
		g_nStatus = kValid;

	return num;
}

// ====================测试代码====================
void Test(const char* string)
{
	int result = StrToInt(string);
	if (result == 0 && g_nStatus == kInvalid)
		printf("the input %s is invalid.\n", string);
	else
		printf("number for %s is: %d.\n", string, result);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test(nullptr);

	Test("");

	Test("123");

	Test("+123");

	Test("-123");

	Test("1a33");

	Test("+0");

	Test("-0");

	//有效的最大正整数, 0x7FFFFFFF
	Test("+2147483647");

	Test("-2147483647");

	Test("+2147483648");

	//有效的最小负整数, 0x80000000
	Test("-2147483648");

	Test("+2147483649");

	Test("-2147483649");

	Test("+");

	Test("-");

	return 0;
}

