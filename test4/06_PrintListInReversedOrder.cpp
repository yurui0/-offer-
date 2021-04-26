// test4.cpp : 定义控制台应用程序的入口点。
//

//面试题6：从头到尾打印链表：输入一个链表的头结点，从尾到头反过来打印出每个节点的值

#include "stdafx.h"
#include "List.h"
#include <stack>
using namespace std;

void PrintListReversingly_Iteratively(ListNode * pHead) //运用栈进行后进先出
{
	stack<ListNode *>nodes;

	ListNode * pNode = pHead;
	while (pNode != nullptr){
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}

	while (!nodes.empty())
	{
		pNode = nodes.top();
		printf("%d\t", pNode->m_nValue);
		nodes.pop();
	}

}

void PrintListReversingly_Recursively(ListNode * pHead) //递归法
{
	if (pHead != nullptr)
	{
		if (pHead->m_pNext != nullptr)
		{
			PrintListReversingly_Recursively(pHead->m_pNext);
		}
		printf("%d\t", pHead->m_nValue);
	}

}


void Test(ListNode* pHead)
{

	PrintList(pHead);
	PrintListReversingly_Iteratively(pHead);
	printf("\n");
	PrintListReversingly_Recursively(pHead);

}

int _tmain(int argc, _TCHAR* argv[])
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

	Test(pNode1);

	DestroyList(pNode1);

	return 0;
}

