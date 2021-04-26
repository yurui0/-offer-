// 50_01_FirstNotRepeatingChar.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������50��һ�����ַ����е�һ��ֻ����һ�ε��ַ�
// ��Ŀ�����ַ������ҳ���һ��ֻ����һ�ε��ַ���������"abaccdeff"�������
// 'b'��

#include "stdafx.h"
#include <cstdio>
#include <string>

char FirstNotRepeatingChar(const char* pString)//����һ���ַ���������תΪconst char *
{
	if (pString == nullptr)
		return '\0';

	const int tableSize = 256;//��Ϊ�ַ�ֻ��8bit��ֻ��256���ַ�
	unsigned int hashTable[tableSize]; //һ��һά����
	for (unsigned int i = 0; i < tableSize; ++i)
		hashTable[i] = 0;

	const char* pHashKey = pString;
	while (*(pHashKey) != '\0')//����char������ÿ����ĸ��ASCALL��ֵ��Ϊ�±�
		hashTable[*(pHashKey++)] ++;

	pHashKey = pString;
	while (*pHashKey != '\0')//�ڶ���ɨ�裬�ҳ�hash���е�һ�γ���ֵΪ1�Ľ��
	{
		if (hashTable[*pHashKey] == 1)
			return *pHashKey;

		pHashKey++;
	}

	return '\0';
}

// ====================���Դ���====================
void Test(const char* pString, char expected)
{
	if (FirstNotRepeatingChar(pString) == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ����������ԣ�����ֻ����һ�ε��ַ�
	Test("google", 'l');

	// ����������ԣ�������ֻ����һ�ε��ַ�
	Test("aabccdbd", '\0');

	// ����������ԣ������ַ���ֻ����һ��
	Test("abcdefg", 'a');

	// ³���Բ��ԣ�����nullptr
	Test(nullptr, '\0');


	return 0;
}

