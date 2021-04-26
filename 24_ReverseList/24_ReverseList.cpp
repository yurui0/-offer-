// 24_ReverseList.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������24����ת����
// ��Ŀ������һ������������һ�������ͷ��㣬��ת�����������ת�������
// ͷ��㡣

#include "stdafx.h"

#include <cstdio>
#include "List.h"

ListNode* ReverseList(ListNode* pHead)
{
	ListNode* pReversedHead = nullptr; //ָ��ת����������ͷ���
	ListNode* pNode = pHead; //ָ���һ���ڵ�
	ListNode* pPrev = nullptr; // 
	while (pNode != nullptr)//��һ���ڵ�Ϊ�վ����跴ת
	{
		ListNode* pNext = pNode->m_pNext;//��ǰ�ڵ����һ���ڵ�

		if (pNext == nullptr)//�����һ���ڵ�Ϊ�գ���͵���������ĩβ����˷�ת����������ͷ�����ǵ�ǰ�ڵ�
			pReversedHead = pNode;

		pNode->m_pNext = pPrev;//��ǰ�ڵ��ǰһ���ڵ�ΪpPrev(��һ���ڵ���ǰ�ڵ�Ϊ��)

		//�������֮�󣬵�ǰ�ڵ���ƣ�����¼ǰһ���ڵ㣬��������������˳���ܷ�����Ϊ�������pPrev���޷�ָ�����ǰһ���ڵ���
		pPrev = pNode;//
		pNode = pNext;
	}

	return pReversedHead;
}

// ====================���Դ���====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);

	ListNode* pReversedHead = ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

// ����������ж�����
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������ֻ��һ�����
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������
void Test3()
{
	Test(nullptr);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	return 0;
}

