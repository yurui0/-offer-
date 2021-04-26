// 58_01_ReverseWordsInSentence.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������58��һ������ת����˳��
// ��Ŀ������һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣
// Ϊ������������ź���ͨ��ĸһ���������������ַ���"I am a student. "��
// �����"student. a am I"��

#include "stdafx.h"

#include <cstdio>
#include "StringUtil.h"
#include <string>

char* ReverseSentence(char *pData)
{
	if (pData == nullptr)//�����Ƿ�Ϸ�
		return nullptr;

	char *pBegin = pData;//�����ָ���ַ����׽ڵ�
	//���²����ǵõ�ָ���ַ���β�ڵ��ָ��
	char *pEnd = pData;
	while (*pEnd != '\0')
		pEnd++;
	pEnd--;//��Ϊ����ѭ��������ֹ��ָ��'\0'��������Ҫ�ڼ�ȥһ��


	// ��ת��������
	Reverse(pBegin, pEnd); //�����������ʵ�֣���ת�ַ����е�һ�Σ���begin��end֮��ģ�

	// ��ת�����е�ÿ������
	pBegin = pEnd = pData;
	while (*pBegin != '\0')
	{
		if (*pBegin == ' ')//˵����ʱpbedin��ָ��ļ������˽�����ָ�붼��ǰ�ƶ�һλ��������
		{
			pBegin++;
			pEnd++;
		}
		else if (*pEnd == ' ' || *pEnd == '\0')//*pEnd == ' '˵��һ�����ʶ��꣬*pEnd == '\0'˵�������ַ���ĩβ
		{
			Reverse(pBegin, --pEnd);//��ת����ַ�����--pend����Ϊ��ָ�򵥴ʺ�һλ
			pBegin = ++pEnd;
		}
		else //��ʱ˵��һ�����ʻ�û���꣬��˼����ƶ�end
			pEnd++;
	}

	return pData;
}

// ====================���Դ���====================
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

// ���ܲ��ԣ��������ж������
void Test1()
{
	char input[] = "I am a student.";
	char expected[] = "student. a am I";

	Test("Test1", input, expected);
}

// ���ܲ��ԣ�������ֻ��һ������
void Test2()
{
	char input[] = "Wonderful";
	char expected[] = "Wonderful";

	Test("Test2", input, expected);
}

// ³���Բ���
void Test3()
{
	Test("Test3", nullptr, nullptr);
}

// �߽�ֵ���ԣ����Կ��ַ���
void Test4()
{
	Test("Test4", "", "");
}

// �߽�ֵ���ԣ��ַ�����ֻ�пո�
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

