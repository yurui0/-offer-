// test3.cpp : �������̨Ӧ�ó������ڵ㡣
/*
����5���滻�ո���ʵ��һ�����������ַ����е�ÿ���ո��滻�ɡ�%20�������硰hello world��->��hello%20world��
Ҫ������ԭ�����������㹻�󣬾�����������н����滻����������o(n)��ʱ��Ľⷨ�����ַ����еĿո��滻��%20
*/

//˼·����Ϊʱ��Ч��o(n^2)̫��ԭ����Ǵ�ǰ�����ƶ��ַ��Ļ�������ÿ���ո񶼻��ƶ�o(n)���ַ���������o(n)���ַ�����ʱ��Ч�ʾ���o(n^2)
//��˿�����һ��˼·,Ϊ�β�ʹ������ָ��



#include "stdafx.h"
#include<iostream>
//#include<istream>
#include <cstdio>
#include <cstring>
#include<fstream>
#include <string>
using namespace std;

typedef unsigned int UNIT_32;

void ReplaceBlank(char str[], UNIT_32 len)
{
	if (str == nullptr || len <= 0)
	{
		return ;
	}

	/*originallenΪ�ַ���str��ʵ�ʳ��ȣ�len��ʾchar������ܳ��ȣ������ո�*/
	UNIT_32 originallen = 0;
	UNIT_32 numberofBlank = 0;
	UNIT_32 i = 0;
	while (str[i] != '\0')
	{
		++originallen;//������ֵ���ַ��ĸ���

		if (str[i] == ' ')
			++numberofBlank;//����ո�ĸ���
		++i;
	}

	/* newlen Ϊ����%20֮����ַ����ĳ���*/
	UNIT_32 newlen = originallen + 2 * numberofBlank;

	if (newlen > len)//�ж���ûԽ�磬��Ϊ��Ŀ˵��ԭ�������㹻��                                                                                     
	{
		return ;
	} 

	
	UNIT_32 indexOfOriginal = originallen;
	UNIT_32 indexOfNew = newlen;

	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)//ָ�뻹ûָ����ǰ�棬�ҿո񻹻�������
	{
		if (str[indexOfOriginal] == ' ')//���
		{
			str[indexOfNew--] = '0';
			str[indexOfNew--] = '2';
			str[indexOfNew--] = '%';
		}

		else
		{
			str[indexOfNew--] = str[indexOfOriginal];//��������ʹ��ԭ����indexofnew��Ȼ����ֵ��1����û�������ո�Ļ��ͽ��������κ���
		}
		//���ﵥ���ó�������Ϊ����������Ŀո���--������else����Ļ�����ô��һ��ѭ��ʱ��ǰһ��ָ��û���ƶ����Ӷ��д���
		--indexOfOriginal;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	
	//cout << "we are happy." << endl;
	//char s[100]="we are happy.";
	char s[100];
	gets_s(s);
	cout << "���ո��滻" << endl;

	ReplaceBlank(s, 100);
	cout << s << endl;

	return 0;
}

