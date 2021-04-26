// 41_StreamMedian.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������41���������е���λ��
// ��Ŀ����εõ�һ���������е���λ����������������ж�����������ֵ����ô
// ��λ������������ֵ����֮��λ���м����ֵ��������������ж���ż������ֵ��
// ��ô��λ������������ֵ����֮���м���������ƽ��ֵ��

#include "stdafx.h"

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

//����������ͷ�ļ���<functional> ���ѵ�ʱ��Ĭ���Ǵ���ѣ�������������greater<T>����С���ѣ�
//�����ʱ��Ĭ���Ǵ�С���󣬵��ǵ�����������greater<T>���ɴӴ�С
//����˵һ�䣬make_heap��heap����������ͷ�ļ�<algorithm>��

template<typename T> 
class DynamicArray
{
public:
	void Insert(T num) //�����������е�������
	{
		//ע���������Ļ�������������Ƕ�Ӧ�����ѣ����ȡ���������ֵ���������ұ��Ƕ�Ӧ����С�ѣ�ȡ��С�ѵ���Сֵ

		if (((min.size() + max.size()) & 1) == 0)//�����ǰ�Ѿ����������������Ŀ��ż�����������ݲ�����С��
		{
			//��������ݱ�������ĳЩ����С���������ѵ����ֵС��������Ҫ���������

			if (max.size() > 0 && num < max[0])//��������ݱ������е����ֵ ҪС
			{
				max.push_back(num);//�Ȱ������ݲ�������
				push_heap(max.begin(), max.end(), less<T>());//less��Ĭ�ϣ���ʾ���󶥶ѣ�������һ��Ԫ�������ģ���������ʹ����ǰ��������

				num = max[0];//�������е���������ó�����������Ҫ������С�ѣ��Ա�֤��С�����������ֶ����������е����֣�

				pop_heap(max.begin(), max.end(), less<T>());//�ڶѵĻ����ϣ������Ѷ�Ԫ�أ����Ѷ�Ԫ�أ���Ϊ�����һ��λ�ã����������һ��λ�öԵ�
				max.pop_back();//��������pop_back��ɾ�����Ԫ��
			}

			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}
		else //�����ǰ�Ѿ����������������Ŀ������
		{
			//��������ݱ���С����ĳЩ���ݴ󣨼�����С�ѵ����ֵ�󣩣�����Ҫ���������

			if (min.size() > 0 && min[0] < num) //��������ݱ���С���е���Сֵ Ҫ��
			{
				min.push_back(num);//�Ȱ������ݲ�����С��
				push_heap(min.begin(), min.end(), greater<T>());//greater��ʾ��С���ѣ�������һ��Ԫ������С�ģ���������ʹ����ǰ������С��

				num = min[0];//����С���е���С�����ó�����������Ҫ�������ѣ��Ա�֤�������������ֶ�С����С���е����֣�

				pop_heap(min.begin(), min.end(), greater<T>());
				min.pop_back();
			}

			max.push_back(num);
			push_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()//�����������е���λ��
	{
		int size = min.size() + max.size();
		if (size == 0)
			throw exception("No numbers are available");

		T median = 0;//������¼�������λ��
		if ((size & 1) == 1)//������ݵ�����������
			median = min[0];
		else               //������ݵ�������ż��
			median = (min[0] + max[0]) / 2;

		return median;
	}

private:
	vector<T> min;//��С�ѣ���Ӧ�����ұ��ǲ��ֵ�����
	vector<T> max;//���ѣ���Ӧ��������ǲ��ֵ�����
};

// ====================���Դ���====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (abs(numbers.GetMedian() - expected) < 0.0000001)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	DynamicArray<double> numbers;

	printf("Test1 begins: ");
	try
	{
		numbers.GetMedian();
		printf("FAILED.\n");
	}
	catch (const exception&)
	{
		printf("Passed.\n");
	}

	numbers.Insert(5);
	Test("Test2", numbers, 5);

	numbers.Insert(2);
	Test("Test3", numbers, 3.5);

	numbers.Insert(3);
	Test("Test4", numbers, 3);

	numbers.Insert(4);
	Test("Test6", numbers, 3.5);

	numbers.Insert(1);
	Test("Test5", numbers, 3);

	numbers.Insert(6);
	Test("Test7", numbers, 3.5);

	numbers.Insert(7);
	Test("Test8", numbers, 4);

	numbers.Insert(0);
	Test("Test9", numbers, 3.5);

	numbers.Insert(8);
	Test("Test10", numbers, 4);
	return 0;
}

