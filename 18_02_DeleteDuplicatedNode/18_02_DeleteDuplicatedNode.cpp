// 18_02_DeleteDuplicatedNode.cpp : 定义控制台应用程序的入口点。
//

// 面试题18（二）：删除链表中重复的结点
// 题目：在一个排序的链表中，如何删除重复的结点？例如，在图3.4（a）中重复
// 结点被删除之后，链表如图3.4（b）所示。
#include "stdafx.h"
#include <cstdio>
#include "List.h"

void DeleteDuplication(ListNode** pHead)
{
	if (pHead == nullptr || *pHead == nullptr) //该指针为空（不合法），或者链表为空链表
		return;

	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pHead;
	while (pNode != nullptr) //此处循环针对pNode,只要pNode没到链表最末尾，则需要进行判断
	{
		ListNode *pNext = pNode->m_pNext;
		bool needDelete = false;//判断是否需要删除的标识
		if (pNext != nullptr && pNext->m_nValue == pNode->m_nValue)//链表中不止一个节点（仅一个肯定不用删，因为没有重复）,且前后两点值相同
			needDelete = true;

		if (!needDelete)//说明前后两个不一样，因此不用删，只需要把pPreNode指向原来的pNode（为了后续考虑，如果下一次重复，需要获取上次的节点），并将pNode右移
		{
			pPreNode = pNode;
			pNode = pNode->m_pNext;
		}
		else //此时前后两个是一样的，需要删除
		{
			int value = pNode->m_nValue; //记录重复的节点处的值，为后面while循环中删除两次做判断条件
			ListNode* pToBeDel = pNode;  //声明一个新节点是避免直接在pNode节点上操作，可能导致错误
			while (pToBeDel != nullptr && pToBeDel->m_nValue == value) //在此处进行删除两次的操作，先删除pNode，在删除和他重复的另一个节点
			{
				pNext = pToBeDel->m_pNext; //此时pNext指向pToBeDel下一个节点，当再次循环一次后就会跳出while循环

				delete pToBeDel;
				pToBeDel = nullptr;

				pToBeDel = pNext;
			}

			if (pPreNode == nullptr) //如果pPreNode为空（空的原因是），就让其指向pNext
				*pHead = pNext;
			else
				pPreNode->m_pNext = pNext;//否则就让pPreNode节点指向删除两个元素后的pNext
			pNode = pNext; //让pNode指向pNext，后面循环时，pNext在后移
		}
	}
}

// ====================测试代码====================
void Test(char* testName, ListNode** pHead, int* expectedValues, int expectedLength)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	DeleteDuplication(pHead);

	int index = 0;
	ListNode* pNode = *pHead;
	while (pNode != nullptr && index < expectedLength)
	{
		if (pNode->m_nValue != expectedValues[index])
			break;

		pNode = pNode->m_pNext;
		index++;
	}

	if (pNode == nullptr && index == expectedLength)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// 某些结点是重复的
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(4);
	ListNode* pNode6 = CreateListNode(4);
	ListNode* pNode7 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2, 5 };
	Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 没有重复的结点
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
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2, 3, 4, 5, 6, 7 };
	Test("Test2", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 除了一个结点之外其他所有结点的值都相同
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(1);
	ListNode* pNode5 = CreateListNode(1);
	ListNode* pNode6 = CreateListNode(1);
	ListNode* pNode7 = CreateListNode(2);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 2 };
	Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 所有结点的值都相同
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(1);
	ListNode* pNode5 = CreateListNode(1);
	ListNode* pNode6 = CreateListNode(1);
	ListNode* pNode7 = CreateListNode(1);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	Test("Test4", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 所有结点都成对出现
void Test5()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(2);
	ListNode* pNode5 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(3);
	ListNode* pNode7 = CreateListNode(4);
	ListNode* pNode8 = CreateListNode(4);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);
	ConnectListNodes(pNode7, pNode8);

	ListNode* pHead = pNode1;

	Test("Test5", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 除了两个结点之外其他结点都成对出现
void Test6()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(4);
	ListNode* pNode7 = CreateListNode(5);
	ListNode* pNode8 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);
	ConnectListNodes(pNode7, pNode8);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 2, 4 };
	Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 链表中只有两个不重复的结点
void Test7()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);

	ConnectListNodes(pNode1, pNode2);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2 };
	Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 结点中只有一个结点
void Test8()
{
	ListNode* pNode1 = CreateListNode(1);

	ConnectListNodes(pNode1, nullptr);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1 };
	Test("Test8", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 结点中只有两个重复的结点
void Test9()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);

	ConnectListNodes(pNode1, pNode2);

	ListNode* pHead = pNode1;

	Test("Test9", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 空链表
void Test10()
{
	ListNode* pHead = nullptr;

	Test("Test10", &pHead, nullptr, 0);
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
	Test8();
	Test9();
	Test10();
	return 0;
}

