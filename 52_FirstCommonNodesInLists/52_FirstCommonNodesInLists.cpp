// 52_FirstCommonNodesInLists.cpp : 定义控制台应用程序的入口点。
//

// 面试题52：两个链表的第一个公共结点
// 题目：输入两个链表，找出它们的第一个公共结点。注：这里的公共节点说明从该节点之后就都是重合的节点,比如两个链表链是Y字形，但是我觉得这里是公共节点的定义要问清楚
// 如果公共节点说的是第一个节点相同，那下面从前往后是对的。但是如果是Y字，我觉得下面代码有问题（有可能x-x这样的即中间一部分一样，后面又不一样了），
// 此时应该是运用两个辅助栈，从后往前出栈，直到最后一个出栈 才行

#include "stdafx.h"

#include <cstdio>
#include "List.h"

unsigned int GetListLength(ListNode* pHead);

ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
	// 得到两个链表的长度
	unsigned int nLength1 = GetListLength(pHead1);
	unsigned int nLength2 = GetListLength(pHead2);
	int nLengthDif = nLength1 - nLength2;//这里是默认链表1比链表2长，当然这不一定合理，为此下面那个if判断就是根据真实情况计算哪个链表更长

	ListNode* pListHeadLong = pHead1;
	ListNode* pListHeadShort = pHead2;
	if (nLength2 > nLength1)//根据实际链表长度进行修改，使得pListHeadLong指向更长的链表
	{
		pListHeadLong = pHead2;
		pListHeadShort = pHead1;
		nLengthDif = nLength2 - nLength1;//表示长链表比短链表长多少
	}

	// 先在长链表上走几步，再同时在两个链表上遍历
	for (int i = 0; i < nLengthDif; ++i) //先在长链表说走长的步数
		pListHeadLong = pListHeadLong->m_pNext;

	while ((pListHeadLong != nullptr) &&
		(pListHeadShort != nullptr) &&
		(pListHeadLong != pListHeadShort))//还没有遍历到链表末尾，且两个链表的值没有相等，则继续判断
	{
		pListHeadLong = pListHeadLong->m_pNext;
		pListHeadShort = pListHeadShort->m_pNext;
	}

	// 得到第一个公共结点
	ListNode* pFisrtCommonNode = pListHeadLong;

	return pFisrtCommonNode;
}

unsigned int GetListLength(ListNode* pHead) //该函数的作用是给定一个链表，先遍历一遍，获得其长度
{
	unsigned int nLength = 0;
	ListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		++nLength;
		pNode = pNode->m_pNext;
	}

	return nLength;
}

// ====================测试代码====================
void DestroyNode(ListNode* pNode);

void Test(char* testName, ListNode* pHead1, ListNode* pHead2, ListNode* pExpected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	ListNode* pResult = FindFirstCommonNode(pHead1, pHead2);
	if (pResult == pExpected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 第一个公共结点在链表中间
// 1 - 2 - 3 \
//            6 - 7
//     4 - 5 /
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode6);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test1", pNode1, pNode4, pNode6);

	DestroyNode(pNode1);
	DestroyNode(pNode2);
	DestroyNode(pNode3);
	DestroyNode(pNode4);
	DestroyNode(pNode5);
	DestroyNode(pNode6);
	DestroyNode(pNode7);
}

// 没有公共结点
// 1 - 2 - 3 - 4
//            
// 5 - 6 - 7
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test2", pNode1, pNode5, nullptr);

	DestroyList(pNode1);
	DestroyList(pNode5);
}

// 公共结点是最后一个结点
// 1 - 2 - 3 - 4 \
//                7
//         5 - 6 /
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode7);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test3", pNode1, pNode5, pNode7);

	DestroyNode(pNode1);
	DestroyNode(pNode2);
	DestroyNode(pNode3);
	DestroyNode(pNode4);
	DestroyNode(pNode5);
	DestroyNode(pNode6);
	DestroyNode(pNode7);
}

// 公共结点是第一个结点
// 1 - 2 - 3 - 4 - 5
// 两个链表完全重合   
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

	Test("Test4", pNode1, pNode1, pNode1);

	DestroyList(pNode1);
}

// 输入的两个链表有一个空链表
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

	Test("Test5", nullptr, pNode1, nullptr);

	DestroyList(pNode1);
}

// 输入的两个链表有一个空链表
void Test6()
{
	Test("Test6", nullptr, nullptr, nullptr);
}

void DestroyNode(ListNode* pNode)
{
	delete pNode;
	pNode = nullptr;
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

