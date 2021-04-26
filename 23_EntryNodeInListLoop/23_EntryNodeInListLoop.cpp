// 23_EntryNodeInListLoop.cpp : 定义控制台应用程序的入口点。
//
// 面试题23：链表中环的入口结点
// 题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
// 环的入口结点是结点3。
#include "stdafx.h"

#include <cstdio>
#include "List.h"

ListNode* MeetingNode(ListNode* pHead) //该函数用来检测链表中是否存在环，并在环存在的前提下找到快慢两个指针相遇的点（该点在环中，是下一个函数需要用到的）
{
	if (pHead == nullptr)//链表为空
		return nullptr;

	ListNode* pSlow = pHead->m_pNext;//慢节点
	if (pSlow == nullptr)//只有一个节点肯定不可能有环，返回空
		return nullptr;

	ListNode* pFast = pSlow->m_pNext;//快节点
	while (pFast != nullptr && pSlow != nullptr) //仅两个节点也不可能有环
	{
		if (pFast == pSlow) //快节点赶上了慢节点，此时该节点位于环中，为后续得出环在节点数目，找到环的入口做铺垫
			return pFast;

		pSlow = pSlow->m_pNext;//慢指针走一步

		pFast = pFast->m_pNext; //快指针先走一步
		if (pFast != nullptr) //快指针后一个不为空的话，再走一步，实现快指针走两步 ，如果只走一步就为空，此处再次循环的时候就会直接返回空指针，因此这里没有处理
			pFast = pFast->m_pNext;
	}

	return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)//用来得到环中的节点数目，以及找到环的入口节点
{
	ListNode* meetingNode = MeetingNode(pHead); // 得到环中任意一点
	if (meetingNode == nullptr)
		return nullptr;

	// 得到环中结点的数目
	int nodesInLoop = 1;
	ListNode* pNode1 = meetingNode;
	while (pNode1->m_pNext != meetingNode)//从环在任意节点出发，再次回到这个店，即可得到环的长度
	{
		pNode1 = pNode1->m_pNext;
		++nodesInLoop;
	}
	//得到环的长度之后，运用两个指针，前后距离为环的长度，当两者相遇的话，此时就是环的入口

	// 先移动pNode1，次数为环中结点的数目，使得后续与第二个节点距离为环的长度
	pNode1 = pHead;
	for (int i = 0; i < nodesInLoop; ++i)
		pNode1 = pNode1->m_pNext;

	// 再移动pNode1和pNode2
	ListNode* pNode2 = pHead;
	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->m_pNext;
		pNode2 = pNode2->m_pNext;
	}

	return pNode1;
}

// ==================== Test Code ====================
void Test(char* testName, ListNode* pHead, ListNode* entryNode)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (EntryNodeOfLoop(pHead) == entryNode)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);

	Test("Test1", pNode1, nullptr);

	DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ConnectListNodes(pNode1, pNode1);

	Test("Test2", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test3()
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
	ConnectListNodes(pNode5, pNode3);

	Test("Test3", pNode1, pNode3);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test4()
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
	ConnectListNodes(pNode5, pNode1);

	Test("Test4", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test5()
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
	ConnectListNodes(pNode5, pNode5);

	Test("Test5", pNode1, pNode5);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, without a loop 
void Test6()
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

	Test("Test6", pNode1, nullptr);

	DestroyList(pNode1);
}

// Empty list
void Test7()
{
	Test("Test7", nullptr, nullptr);
}



int _tmain(int argc, _TCHAR* argv[])
{

	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}

