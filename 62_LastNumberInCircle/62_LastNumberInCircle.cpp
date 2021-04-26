// 62_LastNumberInCircle.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������62��ԲȦ�����ʣ�µ�����
// ��Ŀ��0, 1, ��, n-1��n�������ų�һ��ԲȦ��������0��ʼÿ�δ����ԲȦ��
// ɾ����m�����֡�������ԲȦ��ʣ�µ����һ�����֡�

#include "stdafx.h"

#include <cstdio>
#include <list>

using namespace std;
//Std::list��֧�ֳ���ʱ��������κ�λ�ò�����Ƴ�Ԫ�ص���������֧�ֿ���������ʡ���ͨ��ʵ��Ϊ˫������


// ====================����1====================
int LastRemaining_Solution1(unsigned int n, unsigned int m)//����ⷨ���û�������ģ��ԲȦ��n��m�ֱ��ʾԲȦ��n�����֣�ÿ��ɾ�����m������
{
	if (n < 1 || m < 1)//�����Ƿ�Ϸ�
		return -1;

	unsigned int i = 0;

	list<int> numbers;//����Ԫ������ΪInt��˫������list
	for (i = 0; i < n; ++i)//�����ǽ�Ԫ�ز�������ĩ�ˣ����ݷ�ΧΪ[0,n-1]
		numbers.push_back(i);

	list<int>::iterator current = numbers.begin();//ָ��˫�������һ��Ԫ�أ�˫��������ѭ��������������һ��ѭ������ģ��ѭ�����������
	while (numbers.size() > 1)//�������Ƿ��ж���һ����Ԫ�أ���Ϊ�����size=1��˵����������ʣ�µ�����
	{
		//ע��end˵���õ�����ָ�����ĩβԪ�ص���һ��Ԫ��λ�ã�������������ķ�Χ��һ����Ϊ��ֹ����
		for (int i = 1; i < m; ++i)//ģ��ѭ������������m��ֵ�����ƶ�
		{
			current++;
			if (current == numbers.end())//����ƶ���end(������ĩβԪ�ص���һ��λ�ã���λ�ó���������ķ�Χ)�ͽ����ƶ����ײ�
				current = numbers.begin();
		}

		list<int>::iterator next = ++current;//����������һ��������������¼��m�����ֺ����һ������
		if (next == numbers.end())//����õ�����ָ���������ĩβԪ�ص���һ��λ��,�ͽ����ƶ����ײ�
			next = numbers.begin();

		--current;//��current�ص���m��Ԫ�أ���Ϊ֮ǰΪ�˼�¼��m��Ԫ�غ���һ��Ԫ�أ���������ǰ�ƶ���һλ����˽��仹ԭ
		numbers.erase(current);// ɾ��currentָ���Ľڵ�
		current = next;//���õ�������ֵΪ��һ��Ԫ�صĵ���������Ϊ��������˵�ǰλ�õ�����ɾ����Ӱ������������������˳�������Ͳ�����ô��
	}

	return *(current);
}

// ====================����2====================
// ���ַ����Ƚ����룬��Ϊ��һ����������˼·������Ϊ����
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)//�ж�˼·�Ƿ�Ϸ�
		return -1;

	//�����ǵݹ鹫ʽ��ʵ�֣����忴��ָoffer303ҳ
	int last = 0;
	for (int i = 2; i <= n; i++)
		last = (last + m) % i;

	return last;
}

// ====================���Դ���====================
void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	if (LastRemaining_Solution1(n, m) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (LastRemaining_Solution2(n, m) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	printf("\n");
}

void Test1()
{
	Test("Test1", 5, 3, 3);
}

void Test2()
{
	Test("Test2", 5, 2, 2);
}

void Test3()
{
	Test("Test3", 6, 7, 4);
}

void Test4()
{
	Test("Test4", 6, 6, 3);
}

void Test5()
{
	Test("Test5", 0, 0, -1);
}

void Test6()
{
	Test("Test6", 4000, 997, 1027);
}



int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}

