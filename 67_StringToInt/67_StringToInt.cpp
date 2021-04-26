// 67_StringToInt.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������67�����ַ���ת��������
// ��Ŀ������дһ������StrToInt��ʵ�ְ��ַ���ת��������������ܡ���Ȼ����
// ��ʹ��atoi�����������ƵĿ⺯����

#include "stdafx.h"
#include <cstdio>

//ģ��c++��atio����
long long StrToIntCore(const char* str, bool minus);

enum Status { kValid = 0, kInvalid };//�����ǣ������ж������Ƿ�Ϊ�Ƿ����룬���丳ֵΪkInvalid��ʾ���벻�Ϸ�����ֵΪkValid��ʾ����Ϸ�
int g_nStatus = kValid;

int StrToInt(const char* str)
{
	g_nStatus = kInvalid;//һ��ʼĬ�ϱ��Ϊ���Ϸ�
	long long num = 0;

	if (str != nullptr && *str != '\0')//�ж������ַ����Ƿ�Ϊ��Ϊ���Ҳ�Ϊ���ַ���������к�������
	{
		bool minus = false;//���ַ����е�һ���ַ�Ϊ����λ��ʱ���ж����������Ǹ�����->false,��->true
		if (*str == '+')
			str++;
		else if (*str == '-')
		{
			str++;
			minus = true;
		}

		if (*str != '\0')
			num = StrToIntCore(str, minus);//��ʼ���ַ���תΪ����
	}
	//����ֱ�����0���ұ�Ǽ�Ϊ���Ϸ�kInvalid
	return (int)num;
}

long long StrToIntCore(const char* digit, bool minus)//���ַ���תΪ���֣���һ���������ַ������ڶ��������Ǳ�ʶ����������
{
	long long num = 0;

	while (*digit != '\0')//�ַ���û�е�ĩβ
	{
		if (*digit >= '0' && *digit <= '9')//
		{
			int flag = minus ? -1 : 1;//minusΪtrue��ʾ������flagΪ��-1��������Ϊfalse��flagΪ��+1��
			num = num * 10 + flag * (*digit - '0');//��������

			if ((!minus && num > 0x7FFFFFFF) //���num�������������ķ�Χ��˵������������󣬴�ʱҲ�������ת��
				|| (minus && num < (signed int)0x80000000))
			{
				num = 0;
				break;
			}

			digit++;
		}
		else//����ַ��������ϡ�0��-��9���ķ�Χ��˵������תΪ���֣���˷���0����������ǰѭ��
		{
			num = 0;
			break;
		}
	}

	if (*digit == '\0')//����������while�����꣬�ҵ�ǰ��digit��ֵΪ�ַ���ĩβ������˵���Ѿ�ת��Ϊ���֣���Ϊ����ǲ���������while��������*digit ��= '\0'���������kInvalid
		g_nStatus = kValid;

	return num;
}

// ====================���Դ���====================
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

	//��Ч�����������, 0x7FFFFFFF
	Test("+2147483647");

	Test("-2147483647");

	Test("+2147483648");

	//��Ч����С������, 0x80000000
	Test("-2147483648");

	Test("+2147483649");

	Test("-2147483649");

	Test("+");

	Test("-");

	return 0;
}

