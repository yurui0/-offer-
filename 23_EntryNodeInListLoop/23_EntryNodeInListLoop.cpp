// 23_EntryNodeInListLoop.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������23�������л�����ڽ��
// ��Ŀ��һ�������а�����������ҳ�������ڽ�㣿���磬��ͼ3.8�������У�
// ������ڽ���ǽ��3��
#include "stdafx.h"

#include <cstdio>
#include "List.h"

ListNode* MeetingNode(ListNode* pHead) //�ú�����������������Ƿ���ڻ������ڻ����ڵ�ǰ�����ҵ���������ָ�������ĵ㣨�õ��ڻ��У�����һ��������Ҫ�õ��ģ�
{
	if (pHead == nullptr)//����Ϊ��
		return nullptr;

	ListNode* pSlow = pHead->m_pNext;//���ڵ�
	if (pSlow == nullptr)//ֻ��һ���ڵ�϶��������л������ؿ�
		return nullptr;

	ListNode* pFast = pSlow->m_pNext;//��ڵ�
	while (pFast != nullptr && pSlow != nullptr) //�������ڵ�Ҳ�������л�
	{
		if (pFast == pSlow) //��ڵ���������ڵ㣬��ʱ�ýڵ�λ�ڻ��У�Ϊ�����ó����ڽڵ���Ŀ���ҵ�����������̵�
			return pFast;

		pSlow = pSlow->m_pNext;//��ָ����һ��

		pFast = pFast->m_pNext; //��ָ������һ��
		if (pFast != nullptr) //��ָ���һ����Ϊ�յĻ�������һ����ʵ�ֿ�ָ�������� �����ֻ��һ����Ϊ�գ��˴��ٴ�ѭ����ʱ��ͻ�ֱ�ӷ��ؿ�ָ�룬�������û�д���
			pFast = pFast->m_pNext;
	}

	return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)//�����õ����еĽڵ���Ŀ���Լ��ҵ�������ڽڵ�
{
	ListNode* meetingNode = MeetingNode(pHead); // �õ���������һ��
	if (meetingNode == nullptr)
		return nullptr;

	// �õ����н�����Ŀ
	int nodesInLoop = 1;
	ListNode* pNode1 = meetingNode;
	while (pNode1->m_pNext != meetingNode)//�ӻ�������ڵ�������ٴλص�����꣬���ɵõ����ĳ���
	{
		pNode1 = pNode1->m_pNext;
		++nodesInLoop;
	}
	//�õ����ĳ���֮����������ָ�룬ǰ�����Ϊ���ĳ��ȣ������������Ļ�����ʱ���ǻ������

	// ���ƶ�pNode1������Ϊ���н�����Ŀ��ʹ�ú�����ڶ����ڵ����Ϊ���ĳ���
	pNode1 = pHead;
	for (int i = 0; i < nodesInLoop; ++i)
		pNode1 = pNode1->m_pNext;

	// ���ƶ�pNode1��pNode2
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

