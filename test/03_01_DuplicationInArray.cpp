// test.cpp : �������̨Ӧ�ó������ڵ㡣
/*
��ָoffer ��Ŀ3 ����vector��д��Ĵ���
��Ŀ���ҳ��������ظ�������
	��һ������Ϊ n ����������������ֶ��� 0 �� n-1 �ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�����֪���м����������ظ��ģ�Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ������֡�

*/

//

#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;

typedef unsigned int UNIT_32;

bool duplicate(vector<UNIT_32> numbers, UNIT_32 length, vector<UNIT_32> *duplication)
{
	if (numbers.empty() || length <= 0)     //ǰ������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	{
		return false;
	}

	for (auto it = numbers.begin(); it != numbers.end(); ++it) //�ж������Ƿ�Ϸ�
	{
		if (*it < 0 || *it >length - 1)
		{
			return false;
		}
	}

	
	for (auto i = 0; i < length; ++i)
	{
		while (numbers[i] != i) //һֱ����ֱ�������е�i��λ�õ�����ֵΪi
		{
			if (numbers[i]==numbers[numbers[i]]) //��iλ�ô���ֵ��num[��ֵ]�Ƚϣ�Ϊ�ľ����ҳ��ظ�������
			{
				duplication->emplace_back(numbers[i]);//push_back() ������β�����Ԫ��ʱ�����Ȼᴴ�����Ԫ�أ�Ȼ���ٽ����Ԫ�ؿ��������ƶ��������У�����ǿ����Ļ����º������������ǰ���������Ԫ�أ����� emplace_back() ��ʵ��ʱ������ֱ��������β���������Ԫ�أ�ʡȥ�˿������ƶ�Ԫ�صĹ��̡�
				return true;
			}
			// ���������ͽ����˴ˣ��ٴ��ж�
			UNIT_32 temp = numbers[i];
			numbers[i] = numbers[temp];
			numbers[temp] = temp;

		}
	}




}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "�����봴������Ĵ�С" << endl;
	UNIT_32 n;
	UNIT_32 m;
	cin >> n;
	vector<UNIT_32> v1;
	cout << "���������������е�����" << endl;
	for (auto i = 0; i < n;++i)
	{
		cin >> m;
		v1.emplace_back(m);
	}
	vector<UNIT_32>::iterator it;
	cout << "||||" << endl;
	for (it = v1.begin(); it != v1.end(); ++it)
	{
		cout << *it << endl;
	}
	vector<UNIT_32> result;
	bool test = false;
	test=duplicate(v1, n, &result);

	if (test)
	{
		cout << "�ظ�Ԫ��Ϊ��" << endl;
		for (it = result.begin(); it != result.end(); ++it)
		{
			cout << *it << endl;
		}
	}
	else
		cout << "û���ظ�Ԫ��" << endl;
	

	return 0;
}

