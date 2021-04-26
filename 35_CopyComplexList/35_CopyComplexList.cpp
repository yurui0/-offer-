// 35_CopyComplexList.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������35����������ĸ���
// ��Ŀ����ʵ�ֺ���ComplexListNode* Clone(ComplexListNode* pHead)����
// ��һ�����������ڸ��������У�ÿ����������һ��m_pNextָ��ָ����һ��
// ����⣬����һ��m_pSibling ָ�������е����������nullptr��
#include "stdafx.h"
#include <cstdio>
#include "ComplexList.h"

void CloneNodes(ComplexListNode* pHead);
void ConnectSiblingNodes(ComplexListNode* pHead);
ComplexListNode* ReconnectNodes(ComplexListNode* pHead);

//����ǲ����ø����ռ��ʵ��o(n)��ʱ��Ч��
ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}

void CloneNodes(ComplexListNode* pHead)//��һ������ԭʼ�����ÿ���ڵ�N����һ���½ڵ�N',���������N�ڵ�֮��
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* pCloned = new ComplexListNode();//���pHead��ÿ���ڵ㶼����һ���½ڵ�
		pCloned->m_nValue = pNode->m_nValue;//�½ڵ��ֵ��Դ�ڵ�һ��
		pCloned->m_pNext = pNode->m_pNext;//�½ڵ�ָ���һ���ڵ�
		pCloned->m_pSibling = nullptr;//

		pNode->m_pNext = pCloned;//ԭ�ڵ�ָ���½ڵ㣬������������ԭ�ڵ�֮�������һ���½ڵ�

		pNode = pCloned->m_pNext;//������������һ��ԭ�ڵ㣨����������һ���½ڵ㣩
	}
}

void ConnectSiblingNodes(ComplexListNode* pHead)//��һ�������ø��Ƴ����Ľڵ�m_pSibling
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* pCloned = pNode->m_pNext;//�õ���һ�������½ڵ�ĸ��������е��½ڵ�
		if (pNode->m_pSibling != nullptr)
		{
			pCloned->m_pSibling = pNode->m_pSibling->m_pNext;//�����ƽڵ��m_pSibling����Ϊԭ�ڵ��m_pSiblingλ�ô��ĺ�һλ�������γ�ƽ�еĸо�
		}

		pNode = pCloned->m_pNext;//������ʹ��pNodeָ���Ѿ������˸��ƵĽڵ��m_pSibling �� ��һ��ԭ�ڵ�
	}
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)//������������в�֣�����λ�õĽڵ����ԭ���ڵ㣬ż��λ���ϵĽڵ���ɸ��Ƴ���������
{
	ComplexListNode* pNode = pHead;//�����������ѡ��ԭ����
	ComplexListNode* pClonedHead = nullptr;//��������ĸ��Ƶĸ�������ֻ��Ҫָ��pClonedNode���ɣ����ֻ��pClonedNode�ı伴��
	ComplexListNode* pClonedNode = nullptr;//�����������ѡ��������

	if (pNode != nullptr)
	{
		pClonedHead = pClonedNode = pNode->m_pNext;//���������ø����������ʼ�㣬ͬʱ��pClonedHeadָ��������ԭ����pClonedNode��䣬��Ҫһ�����������ָ��仯�������
		pNode->m_pNext = pClonedNode->m_pNext;//������������ʼԭ�ڵ����һ�ݽڵ�
		pNode = pNode->m_pNext;//pnode��Ϊ����һ��ԭ�����е���һ������
	}

	while (pNode != nullptr)//ԭ����û�д����꣬��Ϊ���������ԭ����һ����
	{
		//���ƽڵ���������������һ�����ƽڵ�
		pClonedNode->m_pNext = pNode->m_pNext;
		pClonedNode = pClonedNode->m_pNext;

		//ԭ�ڵ���������������һ���ڵ�
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}

	return pClonedHead;//���ظ��Ƶĸ�������
}

// ====================���Դ���====================
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

// m_pSiblingָ��������
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

// m_pSibling�γɻ�
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

// ֻ��һ�����
void Test4()
{
	ComplexListNode* pNode1 = CreateNode(1);
	BuildNodes(pNode1, nullptr, pNode1);

	Test("Test4", pNode1);
}

// ³���Բ���
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

