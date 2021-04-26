// 59_01_MaxInSlidingWindow.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������59��һ�����������ڵ����ֵ
// ��Ŀ������һ������ͻ������ڵĴ�С�����ҳ����л�������������ֵ�����磬
// �����������{2, 3, 4, 2, 6, 2, 5, 1}���������ڵĴ�С3����ôһ������6��
// �������ڣ����ǵ����ֵ�ֱ�Ϊ{4, 4, 6, 6, 6, 5}��

#include "stdafx.h"

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
	vector<int> maxInWindows; //������������в�ͬ���������µ����ֵ

	if (num.size() >= size && size >= 1)//�����Ƿ�Ϸ���size��ʾ�������ڵĴ�С
	{
		deque<int> index;//˫�˿��ڵĶ��У����ڱ����п����ǻ����������ֵ�����ֵ��±꣬�������Զ�ǻ������ڵ����ֵ

		for (unsigned int i = 0; i < size; ++i)//����ǹ�����ʼ�Ļ������ڣ���������0-size-1�Ļ������ڣ����Լ���Ӧ�Ķ����±����
		{
			while (!index.empty() && num[i] >= num[index.back()])//����±���в�Ϊ�գ����±�����д�������С�ڴ���������֣����������δӶ�βɾ��(���䲻�����ǻ����������ֵ)
				index.pop_back();//�������ж��׵��±��Ƴ�һ��

			index.push_back(i);//���±�������ĩ��
		}

		for (unsigned int i = size; i < num.size(); ++i)//��ʼ�ƶ���������ֱ������ĩ��
		{
			maxInWindows.push_back(num[index.front()]);//��maxInWindows�д��뵱ǰ�����������ֵ

			while (!index.empty() && num[i] >= num[index.back()])//����±���в�Ϊ�գ����±�����д�������С�ڴ���������֣����������δӶ�βɾ��(���䲻�����ǻ����������ֵ)
				index.pop_back();
			if (!index.empty() && index.front() <= (int)(i - size))//����±���в�Ϊ�գ��Ҷ���Ԫ�ض�Ӧ���±곬���������ڵķ�Χ����Ӧ�ý����Ƴ�
				index.pop_front();

			index.push_back(i);
		}
		maxInWindows.push_back(num[index.front()]);//���һ��ѭ��ִ�������������ʱ���һ�����ڻ���Ҫ����front�ǻ�ȡdeque�ж���Ԫ��
	}

	return maxInWindows;
}

// ====================���Դ���====================
void Test(const char* testName, const vector<int>& num, unsigned int size, const vector<int>& expected) //���������ǣ�ԭ���顢�������ڴ�С�������������ֵ����
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	vector<int> result = maxInWindows(num, size);

	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while (iterResult < result.end() && iterExpected < expected.end())
	{
		if (*iterResult != *iterExpected)
			break;

		++iterResult;
		++iterExpected;
	}

	if (iterResult == result.end() && iterExpected == expected.end())
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

void Test1()
{
	int num[] = { 2, 3, 4, 2, 6, 2, 5, 1 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int)); //ͨ�������ַ��ʼ��,��������int a[5] = {1,2,3,4,5};
																	//ͨ������a�ĵ�ַ��ʼ����ע���ַ�Ǵ�0��5������ҿ����䣩vector<int> b(a, a + 5);

	int expected[] = { 4, 4, 6, 6, 6, 5 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test1", vecNumbers, size, vecExpected);
}

void Test2()
{
	int num[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 3, 3, 5, 5, 6, 7 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test2", vecNumbers, size, vecExpected);
}

// �������鵥������
void Test3()
{
	int num[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 7, 9, 11, 13, 15 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test3", vecNumbers, size, vecExpected);
}

// �������鵥���ݼ�
void Test4()
{
	int num[] = { 16, 14, 12, 10, 8, 6, 4 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 16, 14, 12 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 5;

	Test("Test4", vecNumbers, size, vecExpected);
}

// �������ڵĴ�СΪ1
void Test5()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 10, 14, 12, 11 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 1;

	Test("Test5", vecNumbers, size, vecExpected);
}

// �������ڵĴ�С��������ĳ���
void Test6()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 14 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test6", vecNumbers, size, vecExpected);
}

// �������ڵĴ�СΪ0
void Test7()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 0;

	Test("Test7", vecNumbers, size, vecExpected);
}

// �������ڵĴ�С������������ĳ���
void Test8()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test8", vecNumbers, size, vecExpected);
}

// ��������Ϊ��
void Test9()
{
	vector<int> vecNumbers;
	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test9", vecNumbers, size, vecExpected);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();

	return 0;
}

