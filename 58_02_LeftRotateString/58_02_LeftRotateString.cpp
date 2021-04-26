// 58_02_LeftRotateString.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������58������������ת�ַ���
// ��Ŀ���ַ���������ת�����ǰ��ַ���ǰ������ɸ��ַ�ת�Ƶ��ַ�����β����
// �붨��һ������ʵ���ַ�������ת�����Ĺ��ܡ����������ַ���"abcdefg"����
// ��2���ú�������������ת2λ�õ��Ľ��"cdefgab"��

#include "stdafx.h"

#include <cstdio>
#include "StringUtil.h"
#include <string.h>

char* LeftRotateString(char* pStr, int n)
{
	if (pStr != nullptr)
	{
		int nLength = static_cast<int>(strlen(pStr));
		if (nLength > 0 && n > 0 && n < nLength)//�ų�n<0ʹ��ָ��pstr+n���ʵ��ڴ治�����ַ�����������������벻�Ϸ�������ת��ǰ��λ�����ܳ����ַ�������
		{
			//���������n���ַ�������Ϊǰ�泤��Ϊn�ĵ�һ����
			char* pFirstStart = pStr; 
			char* pFirstEnd = pStr + n - 1;
			//���������n���ַ�������Ϊ���泤��Ϊlength-n�ĵڶ�����
			char* pSecondStart = pStr + n; 
			char* pSecondEnd = pStr + nLength - 1;

			// ��ת�ַ�����ǰ��n���ַ�
			Reverse(pFirstStart, pFirstEnd);
			// ��ת�ַ����ĺ��沿��
			Reverse(pSecondStart, pSecondEnd);
			// ��ת�����ַ���
			Reverse(pFirstStart, pSecondEnd);
		}
	}

	return pStr;
}

// ====================���Դ���====================
void Test(const char* testName, char* input, int num, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	char* result = LeftRotateString(input, num);

	if ((input == nullptr && expectedResult == nullptr)
		|| (input != nullptr && strcmp(result, expectedResult) == 0))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// ���ܲ���
void Test1()
{
	char input[] = "abcdefg";
	char expected[] = "cdefgab";

	Test("Test1", input, 2, expected);
}

// �߽�ֵ����
void Test2()
{
	char input[] = "abcdefg";
	char expected[] = "bcdefga";

	Test("Test2", input, 1, expected);
}

// �߽�ֵ����
void Test3()
{
	char input[] = "abcdefg";
	char expected[] = "gabcdef";

	Test("Test3", input, 6, expected);
}

// ³���Բ���
void Test4()
{
	Test("Test4", nullptr, 6, nullptr);
}

// ³���Բ���
void Test5()
{
	char input[] = "abcdefg";
	char expected[] = "abcdefg";

	Test("Test5", input, 0, expected);
}

// ³���Բ���
void Test6()
{
	char input[] = "abcdefg";
	char expected[] = "abcdefg";

	Test("Test6", input, 7, expected);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}

