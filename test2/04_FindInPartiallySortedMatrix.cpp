// test2.cpp : �������̨Ӧ�ó������ڵ㡣
/*
������4����ά�����еĲ��ң�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳������
�����һ������������������һ����ά�����һ���������ж��������Ƿ��и�����

*/
//

#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;
typedef unsigned int UNIT_32;

bool Find(vector<vector<UNIT_32> > obj, UNIT_32 rows, UNIT_32 columns, UNIT_32 number)
{
	bool found = false;

	if (!obj.empty() && rows > 0 && columns > 0) //ǰ������
	{
		UNIT_32 row = 0;
		UNIT_32 column = columns - 1;
		while (row < rows && column >= 0)//����Ҫ����һ����������Ҫ�Ϸ�
		{
			if (obj[row][column] == number)
			{
				found = true;
				break;
			}
			else if (obj[row][column] > number)//��Ϊobj[row][column]����Number���ˣ���ô�����²��ң���row���Ӿ�û�����壬��Ϊ���������ǵ�����
				--column;
			else // ͬ��obj[row][column]����NumberС�ˣ����ұ߲�������ȥ�������ϸ����������ˣ������Ҫ�ҵ�ֻ������������
				++row;

		}

	}

	return found;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "�����봴����ά��������к�" << endl;
	UNIT_32 m;//��
	UNIT_32 n;//��
	cin >> m;
	cin >> n;
	vector<vector<UNIT_32> > obj(m, vector<UNIT_32>(n)); //�����ά��̬����5��6�� 

	cout << "�밴�մ��ϵ���/�����ҵ�˳��������������" << endl;
	for (auto i = 0; i < obj.size(); i++)//�����ά��̬���� //��
	{
		for (auto j = 0; j < obj[i].size(); j++)  //��
		{
			cin >> obj[i][j] ;
		}
	}

	/* �����ά��̬���飬����Ƿ���ȷ��
	for (int i = 0; i < obj.size(); i++)//�����ά��̬���� 
	{
		for (int j = 0; j < obj[i].size(); j++)
		{
			cout << obj[i][j] << " ";
		}
		cout << "\n";
	}
	*/
	cout << "��������Ҫ��ѯ�����֣�unsigned int���ͣ�" << endl;
	UNIT_32 l;
	cin >> l;
	bool result;
	result=Find(obj, m, n, l);
	if (result)
		cout << "�ҵ�" << endl;
	else
		cout << "û�ҵ�" << endl;

	return 0;
}

