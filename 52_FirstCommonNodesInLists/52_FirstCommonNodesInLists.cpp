// 52_FirstCommonNodesInLists.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������52����������ĵ�һ���������
// ��Ŀ���������������ҳ����ǵĵ�һ��������㡣ע������Ĺ����ڵ�˵���Ӹýڵ�֮��Ͷ����غϵĽڵ�,����������������Y���Σ������Ҿ��������ǹ����ڵ�Ķ���Ҫ�����
// ��������ڵ�˵���ǵ�һ���ڵ���ͬ���������ǰ�����ǶԵġ����������Y�֣��Ҿ���������������⣨�п���x-x�����ļ��м�һ����һ���������ֲ�һ���ˣ���
// ��ʱӦ����������������ջ���Ӻ���ǰ��ջ��ֱ�����һ����ջ ����

#include "stdafx.h"

#include <cstdio>
#include "List.h"

unsigned int GetListLength(ListNode* pHead);

ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
	// �õ���������ĳ���
	unsigned int nLength1 = GetListLength(pHead1);
	unsigned int nLength2 = GetListLength(pHead2);
	int nLengthDif = nLength1 - nLength2;//������Ĭ������1������2������Ȼ�ⲻһ������Ϊ�������Ǹ�if�жϾ��Ǹ�����ʵ��������ĸ��������

	ListNode* pListHeadLong = pHead1;
	ListNode* pListHeadShort = pHead2;
	if (nLength2 > nLength1)//����ʵ�������Ƚ����޸ģ�ʹ��pListHeadLongָ�����������
	{
		pListHeadLong = pHead2;
		pListHeadShort = pHead1;
		nLengthDif = nLength2 - nLength1;//��ʾ������ȶ���������
	}

	// ���ڳ��������߼�������ͬʱ�����������ϱ���
	for (int i = 0; i < nLengthDif; ++i) //���ڳ�����˵�߳��Ĳ���
		pListHeadLong = pListHeadLong->m_pNext;

	while ((pListHeadLong != nullptr) &&
		(pListHeadShort != nullptr) &&
		(pListHeadLong != pListHeadShort))//��û�б���������ĩβ�������������ֵû����ȣ�������ж�
	{
		pListHeadLong = pListHeadLong->m_pNext;
		pListHeadShort = pListHeadShort->m_pNext;
	}

	// �õ���һ���������
	ListNode* pFisrtCommonNode = pListHeadLong;

	return pFisrtCommonNode;
}

unsigned int GetListLength(ListNode* pHead) //�ú����������Ǹ���һ�������ȱ���һ�飬����䳤��
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

// ====================���Դ���====================
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

// ��һ����������������м�
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

// û�й������
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

// ������������һ�����
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

// ��������ǵ�һ�����
// 1 - 2 - 3 - 4 - 5
// ����������ȫ�غ�   
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

// ���������������һ��������
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

// ���������������һ��������
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

