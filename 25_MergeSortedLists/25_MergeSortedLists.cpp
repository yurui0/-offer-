// 25_MergeSortedLists.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������25���ϲ��������������
// ��Ŀ������������������������ϲ�����������ʹ�������еĽ����Ȼ�ǰ�
// �յ�������ġ���������ͼ3.11�е�����1������2����ϲ�֮���������������
// ��3��ʾ��
#include "stdafx.h"

#include <cstdio>
#include "List.h"

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)//˼·���Ƕ����������������������ָ�룬���αȽϣ�
{
	if (pHead1 == nullptr)//һ������Ϊ�գ��ϲ������Ϊ��һ������
		return pHead2;
	else if (pHead2 == nullptr)//һ������Ϊ�գ��ϲ������Ϊ��һ������
		return pHead1;

	ListNode* pMergedHead = nullptr;//�ϲ��������

	if (pHead1->m_nValue < pHead2->m_nValue)//��һ������ǰ��ֵС����һ������ǰ��ֵ
	{
		pMergedHead = pHead1;
		pMergedHead->m_pNext = Merge(pHead1->m_pNext, pHead2);//���õݹ飬��һ��������ƣ���ʼ�ݹ�
	}
	else
	{
		pMergedHead = pHead2;
		pMergedHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
	}

	return pMergedHead;
}

// ====================���Դ���====================
ListNode* Test(char* testName, ListNode* pHead1, ListNode* pHead2)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The first list is:\n");
	PrintList(pHead1);

	printf("The second list is:\n");
	PrintList(pHead2);

	printf("The merged list is:\n");
	ListNode* pMergedHead = Merge(pHead1, pHead2);
	PrintList(pMergedHead);

	printf("\n\n");

	return pMergedHead;
}

// list1: 1->3->5
// list2: 2->4->6
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode6 = CreateListNode(6);

	ConnectListNodes(pNode2, pNode4);
	ConnectListNodes(pNode4, pNode6);

	ListNode* pMergedHead = Test("Test1", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// �������������ظ�������
// list1: 1->3->5
// list2: 1->3->5
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(5);

	ConnectListNodes(pNode2, pNode4);
	ConnectListNodes(pNode4, pNode6);

	ListNode* pMergedHead = Test("Test2", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// ��������ֻ��һ������
// list1: 1
// list2: 2
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);

	ListNode* pMergedHead = Test("Test3", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// һ������Ϊ������
// list1: 1->3->5
// list2: ������
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pMergedHead = Test("Test4", pNode1, nullptr);

	DestroyList(pMergedHead);
}

// ��������Ϊ������
// list1: ������
// list2: ������
void Test5()
{
	ListNode* pMergedHead = Test("Test5", nullptr, nullptr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	return 0;
}

