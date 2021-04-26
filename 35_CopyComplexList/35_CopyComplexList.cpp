// 35_CopyComplexList.cpp : 定义控制台应用程序的入口点。
//
// 面试题35：复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。
#include "stdafx.h"
#include <cstdio>
#include "ComplexList.h"

void CloneNodes(ComplexListNode* pHead);
void ConnectSiblingNodes(ComplexListNode* pHead);
ComplexListNode* ReconnectNodes(ComplexListNode* pHead);

//这个是不运用辅助空间的实现o(n)的时间效率
ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}

void CloneNodes(ComplexListNode* pHead)//第一步根据原始链表的每个节点N创建一个新节点N',并将其插入N节点之后
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* pCloned = new ComplexListNode();//针对pHead中每个节点都创建一个新节点
		pCloned->m_nValue = pNode->m_nValue;//新节点的值与源节点一样
		pCloned->m_pNext = pNode->m_pNext;//新节点指向后一个节点
		pCloned->m_pSibling = nullptr;//

		pNode->m_pNext = pCloned;//原节点指向新节点，这样就在两个原节点之间插入了一个新节点

		pNode = pCloned->m_pNext;//接下来处理下一个原节点（即在其后面加一个新节点）
	}
}

void ConnectSiblingNodes(ComplexListNode* pHead)//这一步是设置复制出来的节点m_pSibling
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* pCloned = pNode->m_pNext;//得到第一步包含新节点的复杂链表中的新节点
		if (pNode->m_pSibling != nullptr)
		{
			pCloned->m_pSibling = pNode->m_pSibling->m_pNext;//将复制节点的m_pSibling设置为原节点的m_pSibling位置处的后一位，类似形成平行的感觉
		}

		pNode = pCloned->m_pNext;//这里是使得pNode指向已经设置了复制的节点的m_pSibling 的 后一个原节点
	}
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)//把两个链表进行拆分，奇数位置的节点组成原来节点，偶数位置上的节点组成复制出来的链表
{
	ComplexListNode* pNode = pHead;//从组合链表中选择原链表
	ComplexListNode* pClonedHead = nullptr;//最终输出的复制的复杂链表，只需要指向pClonedNode即可，随后只让pClonedNode改变即可
	ComplexListNode* pClonedNode = nullptr;//从组会链表中选择新链表

	if (pNode != nullptr)
	{
		pClonedHead = pClonedNode = pNode->m_pNext;//这里是设置复制链表的起始点，同时让pClonedHead指向复制链表，原因是pClonedNode会变，需要一个不变的链表指向变化后的链表
		pNode->m_pNext = pClonedNode->m_pNext;//这里是设置起始原节点的下一份节点
		pNode = pNode->m_pNext;//pnode变为了下一个原链表中的下一个链表
	}

	while (pNode != nullptr)//原链表没有处理完，因为复制链表和原链表一样长
	{
		//复制节点获得他所期望的下一个复制节点
		pClonedNode->m_pNext = pNode->m_pNext;
		pClonedNode = pClonedNode->m_pNext;

		//原节点获得它所期望的下一个节点
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}

	return pClonedHead;//返回复制的复杂链表
}

// ====================测试代码====================
void Test(const char* testName, ComplexListNode* pHead)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The original list is:\n");
	PrintList(pHead);

	ComplexListNode* pClonedHead = Clone(pHead);

	printf("The cloned list is:\n");
	PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, pNode3);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, pNode3);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode4);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
	ComplexListNode* pNode1 = CreateNode(1);
	BuildNodes(pNode1, nullptr, pNode1);

	Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
	Test("Test5", nullptr);
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

