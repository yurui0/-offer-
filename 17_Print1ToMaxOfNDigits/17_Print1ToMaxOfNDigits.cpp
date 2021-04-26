// 17_Print1ToMaxOfNDigits.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������17����ӡ1������nλ��
// ��Ŀ����������n����˳���ӡ����1����nλʮ����������������3����
// ��ӡ��1��2��3һֱ������3λ����999��
//ע���д������⣬��˿������ַ���

//�����࿴����

#include "stdafx.h"
#include <cstdio>
#include <memory>

void PrintNumber(char* number);
bool Increment(char* number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index);

// ====================����һ====================
void Print1ToMaxOfNDigits_1(int n) //�ܵķ����������е���Incrementʵ���ַ���+1,PrintNumberʵ�ִ�ӡ����
{
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	while (!Increment(number))
	{
		PrintNumber(number);
	}

	delete[]number;
}

// �ַ���number��ʾһ�����֣��� number������1
// ������ӷ�������򷵻�true������Ϊfalse
bool Increment(char* number)
{
	bool isOverflow = false; //��ʶ��������ӳ�ӷ��Ƿ� ���
	int nTakeOver = 0;
	int nLength = strlen(number);//��¼�ַ����ĳ��ȣ������Ǳ�ʾ��Ӧ������λ��

	for (int i = nLength - 1; i >= 0; i--)
	{
		int nSum = number[i] - '0' + nTakeOver;
		if (i == nLength - 1)
			nSum++;

		if (nSum >= 10)
		{
			if (i == 0)
				isOverflow = true;
			else
			{
				nSum -= 10;
				nTakeOver = 1; //����ǽ�λ�����ԭ��ÿ�ε��µ�һλ������ʼֵΪ1��֮ǰ��ʼ��Ϊ0������Ϊ�ַ��������λ����������Сλ����Ϊ0����
								// ��������λ���ǽ�λ�õ��ģ�����Ϊ0,�����1��ʼ
				number[i] = '0' + nSum;
			}
		}
		else
		{
			number[i] = '0' + nSum;
			break; //��ʾ�˳���ǰѭ�����������������£�forѭ��ִֻ��һ��
		}
	}

	return isOverflow;
}

// ====================������====================
void Print1ToMaxOfNDigits_2(int n)  //��������������ǣ���������λ��ʼ����Ӧ�ַ�������С����������ʼֵΪ0-9
{
	if (n <= 0)
		return;

	char* number = new char[n + 1]; //�ַ������һλ��\0���������������һλ
	number[n] = '\0';

	for (int i = 0; i < 10; ++i)
	{
		number[0] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, n, 0); //���λ���ִ�0-9��һ��ѭ��ʮ�Σ��ú������Ǽ��㵱ǰ���λֵ�����п�������
	}

	delete[] number;
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index) //�������λȷ��������µ���������
{
	if (index == length - 1)//��ǰ���λ������λ�����ֶ��������ˣ���˴�ӡ
	{
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; ++i)
	{
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);//�ݹ���һλ�������������Ѿ����������ֵ����һλ
	}
}

// ====================��������====================
// �ַ���number��ʾһ�����֣����������ɸ�0��ͷ
// ��ӡ��������֣������Կ�ͷ��0
void PrintNumber(char* number)
{
	bool isBeginning0 = true;
	int nLength = strlen(number);

	for (int i = 0; i < nLength; ++i)
	{
		if (isBeginning0 && number[i] != '0')
			isBeginning0 = false;

		if (!isBeginning0)
		{
			printf("%c", number[i]);
		}
	}

	printf("\t");
}

// ====================���Դ���====================
void Test(int n)
{
	printf("Test for %d begins:\n", n);

	Print1ToMaxOfNDigits_1(n);
	Print1ToMaxOfNDigits_2(n);

	printf("\nTest for %d ends.\n", n);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(0);
	Test(-1);
	return 0;
}

