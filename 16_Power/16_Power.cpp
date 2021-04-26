// 16_Power.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������16����ֵ�������η�
// ��Ŀ��ʵ�ֺ���double Power(double base, int exponent)����base��exponent
// �η�������ʹ�ÿ⺯����ͬʱ����Ҫ���Ǵ������⡣


#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

bool g_InvalidInput = false; //ȫ�ֲ���������������ʶ�Ƿ������������򷵻�true�����򷵻�false
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent)
{
	g_InvalidInput = false;

	if (equal(base, 0.0) && exponent < 0) //��ʱ˵��������0����ָ��С��0����ʱ�ǲ��Ϸ��ģ��������ñ�ʶ������0
	{
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);//��ָ��ȡ����ֵ
	if (exponent < 0)
		absExponent = (unsigned int)(-exponent);

	double result = PowerWithUnsignedExponent(base, absExponent);//�������ĺ�������֤�����ָ��������
	if (exponent < 0) //���ָ��ԭ���Ǹ�������ȥ����ĵ���
		result = 1.0 / result;

	return result;
}

/*
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
double result = 1.0;

for (int i = 1; i <= exponent; ++i) //����ָ������õ��Ľ��
result *= base;
return result;
}
*/

// �˺�����˼·��  { a^(n/2) * a^(n/2)
//             an={
//                 { a^(n-1)/2 * a^(n-1)/2 * a
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double result = PowerWithUnsignedExponent(base, exponent >> 1);//�������滻����
	result *= result; //�ѽ������ƽ��
	if ((exponent & 0x1) == 1) //��λ�������滻��������%��������˵���ָ�����������������Ҫ����ԭ������һ��
		result *= base;

	return result;
}

bool equal(double num1, double num2) //�ж��Ƿ����
{
	if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
		return true;
	else
		return false;
}

// ====================���Դ���====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
	double result = Power(base, exponent);
	if (equal(result, expectedResult) && g_InvalidInput == expectedFlag)
		cout << testName << " passed" << endl;
	else
		cout << testName << " FAILED" << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// ������ָ����Ϊ����
	Test("Test1", 2, 3, 8, false);

	// ����Ϊ������ָ��Ϊ����
	Test("Test2", -2, 3, -8, false);

	// ָ��Ϊ����
	Test("Test3", 2, -3, 0.125, false);

	// ָ��Ϊ0
	Test("Test4", 2, 0, 1, false);

	// ������ָ����Ϊ0
	Test("Test5", 0, 0, 1, false);

	// ����Ϊ0��ָ��Ϊ����
	Test("Test6", 0, 4, 0, false);

	// ����Ϊ0��ָ��Ϊ����
	Test("Test7", 0, -4, 0, true);

	return 0;
}

