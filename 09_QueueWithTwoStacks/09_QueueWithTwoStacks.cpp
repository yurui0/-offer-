// 09_QueueWithTwoStacks.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������9��������ջʵ�ֶ���
// ��Ŀ��������ջʵ��һ�����С����е��������£���ʵ��������������appendTail
// ��deleteHead���ֱ�����ڶ���β����������ڶ���ͷ��ɾ�����Ĺ��ܡ�

#include "stdafx.h"
#include "Queue.h"

// ====================���Դ���====================
void Test(char actual, char expected)
{
	if (actual == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}



int _tmain(int argc, _TCHAR* argv[])
{
	CQueue<char> queue;

	queue.appendTail('a');
	queue.appendTail('b');
	queue.appendTail('c');

	char head = queue.deleteHead();
	Test(head, 'a');

	head = queue.deleteHead();
	Test(head, 'b');

	queue.appendTail('d');
	head = queue.deleteHead();
	Test(head, 'c');

	queue.appendTail('e');
	head = queue.deleteHead();
	Test(head, 'd');

	head = queue.deleteHead();
	Test(head, 'e');

	return 0;
}

