// 24_ReverseList.cpp : 定义控制台应用程序的入口点。
//
// 面试题24：反转链表
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的
// 头结点。

#include "stdafx.h"

#include <cstdio>
#include "List.h"

ListNode* ReverseList(ListNode* pHead)
{
	ListNode* pReversedHead = nullptr; //指向反转链表后链表的头结点
	ListNode* pNode = pHead; //指向第一个节点
	ListNode* pPrev = nullptr; // 
	while (pNode != nullptr)//第一个节点为空就无需反转
	{
		ListNode* pNext = pNode->m_pNext;//当前节点的下一个节点

		if (pNext == nullptr)//如果下一个节点为空，则就到了正链表末尾，因此反转链表后的链表头结点就是当前节点
			pReversedHead = pNode;

		pNode->m_pNext = pPrev;//当前节点的前一个节点为pPrev(第一个节点其前节点为空)

		//处理完成之后，当前节点后移，并记录前一个节点，，这里下面两个顺序不能反，因为如果反了pPrev就无法指向的是前一个节点了
		pPrev = pNode;//
		pNode = pNext;
	}

	return pReversedHead;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);

	ListNode* pReversedHead = ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

// 输入的链表有多个结点
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

// 输入的链表只有一个结点
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入空链表
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

