// test1.cpp : �������̨Ӧ�ó������ڵ㡣
/*
��ָoffer������Ĳ�����Ŀ2�����޸������ҳ��ظ�������
��Ŀ����һ������Ϊn+1����������������ֶ���1-n�ķ�Χ�ڣ�����������������һ������˵�ظ��ģ����ҳ�����������һ���ظ������֣�����
�����޸���������顣
*/

//˼·��
// ���ַ�������û���ظ������֣���ô1-n��ֻ��n�����֣���˽�1-n�����ֶ���Ϊ1-m��m+1-n�����1-m��������Ŀ����m����ô�������Ͱ����ظ����֣����������һ���䣬Ȼ���ٴζ���


#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned int UNIT_32;

int countRange(vector<UNIT_32> numbers, UNIT_32 length, UNIT_32 start, UNIT_32 end);


int getDuplication(vector<UNIT_32> numbers, UNIT_32 length)
{
	if (numbers.empty() || length <= 0)
	{
		return -1;
	}
	UNIT_32 start = 1;
	UNIT_32 end = length - 1;
	while (end >= start)//��֤vector���������������ݣ��������п����ظ����������һ�����ݲ������ظ�
	{
		UNIT_32 middle = ((end - start) >> 1) + start; //����>>,��ʾ��2
		UNIT_32 count = countRange(numbers,length,start,middle);//�ú�������vector��start��middle��Χ�����ĸ���
		if (end == start)// ѭ���жϵ����
		{
			if (count > 1)
				return start;
			else
				break;
		}

		if (count > (middle - start + 1))// �����start-middle֮������ݵ�����������֮���˵�����ظ���������֮��
			end = middle;
		else  //��֮����middle+1-end֮��
			start = middle + 1;
		
	}
	//����һ�����ݲ������ظ�
	return -1;

}

int countRange(vector<UNIT_32> numbers, UNIT_32 length, UNIT_32 start, UNIT_32 end)
{
	if (numbers.empty())
		return 0;

	int count = 0;
	for (int i = 0; i < length; ++i)
	{
		if (numbers[i] >= start && numbers[i] <= end) //�����ڸ÷�Χ�ڵ����ĸ���
			++count;
	}
	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{

	cout << "�����봴������Ĵ�С" << endl;
	UNIT_32 n;
	UNIT_32 m;
	cin >> n;
	vector<UNIT_32> v1;
	cout << "���������������е�����" << endl;
	for (auto i = 0; i < n; ++i)
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

	UNIT_32 result;
	result = getDuplication(v1, n-1);
	cout << "�����" << result << endl;

	return 0;
}

