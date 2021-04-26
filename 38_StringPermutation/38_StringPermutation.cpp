// 38_StringPermutation.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������38���ַ���������
// ��Ŀ������һ���ַ�������ӡ�����ַ������ַ����������С����������ַ���abc��
// ���ӡ�����ַ�a��b��c�������г����������ַ���abc��acb��bac��bca��cab��cba��

#include "stdafx.h"

#include <cstdio>

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
	if (pStr == nullptr)//�ж��Ƿ�Ϸ�
		return;

	Permutation(pStr, pStr);
}

// �����ַ��� abcd����
void Permutation(char* pStr, char* pBegin)//��һ���ַ���pStrָ�������ַ����ĵ�һ���ַ����ڶ����ַ���pBefin��ʾ��ǰ����ִ�����в������ַ����ĵ�һ���ַ�
{											//ע�����ﴫ�ݵ���ָ�룬���pStr����ΪpBegin�ı任���任����Ϊ���Ƕ�ָ��ͬһ���ַ���
	if (*pBegin == '\0')
	{
		printf("%s\n", pStr);
	}
	else
	{
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			//��һ����ĸ�ͺ�һ��pch��ָ��ĸ�����н���
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);

			//��һ����ĸ�����һ����ĸ������������������֮����Ҫ��λ�û�ԭ��Ϊ�������ý�����һ����ĸ�����¸���ĸ������׼��
			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}

// ====================���Դ���====================
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

