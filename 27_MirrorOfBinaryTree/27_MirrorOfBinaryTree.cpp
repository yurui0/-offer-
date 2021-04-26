// 27_MirrorOfBinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������27���������ľ���
// ��Ŀ�������һ������������һ�����������ú���������ľ���

#include "stdafx.h"
#include <cstdio>
#include "BinaryTree.h"
#include <stack>

void MirrorRecursively(BinaryTreeNode *pNode)//���õݹ�ʵ��
{
	if ((pNode == nullptr) || (pNode->m_pLeft == nullptr && pNode->m_pRight))//�ж������Ƿ�Ϸ�
		return;

	//�������е�Ŀ���ǽ���pNode�ڵ㴦�������ӽڵ�
	BinaryTreeNode *pTemp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTemp;

	if (pNode->m_pLeft)//����������ڵ㲻Ϊ�գ�����еݹ飬��������ڵ�Ϊ���������
		MirrorRecursively(pNode->m_pLeft);

	if (pNode->m_pRight)//���������ҽڵ㲻Ϊ�գ�����еݹ飬��������ڵ�Ϊ���������
		MirrorRecursively(pNode->m_pRight);
}

void MirrorIteratively(BinaryTreeNode* pRoot)//����ѭ��ʵ�֣���ʱ��ѭ��������ջʵ�����Ƶݹ��Ч��
{
	if (pRoot == nullptr)//�ж������Ƿ�Ϸ�
		return;

	std::stack<BinaryTreeNode*> stackTreeNode;//����ջ��ջ��Ԫ�������Ƕ������ڵ�
	stackTreeNode.push(pRoot);//�ڵ��ջ

	while (stackTreeNode.size() > 0)//ѭ�����д�����ֻҪջ���нڵ�--���Ըýڵ���д���
	{
		BinaryTreeNode *pNode = stackTreeNode.top();//��ջ��ȡ��һ���ڵ�
		stackTreeNode.pop();//��ջ������Ӱ�����

		//�������е�Ŀ���ǽ���pNode�ڵ㴦�������ӽڵ�
		BinaryTreeNode *pTemp = pNode->m_pLeft;
		pNode->m_pLeft = pNode->m_pRight;
		pNode->m_pRight = pTemp;

		if (pNode->m_pLeft)//����������ڵ㲻Ϊ�գ��򽫽ڵ�ѹջ����������ڵ�Ϊ���������
			stackTreeNode.push(pNode->m_pLeft);

		if (pNode->m_pRight)//���������ҽڵ㲻Ϊ�գ��򽫽ڵ�ѹջ����������ڵ�Ϊ���������
			stackTreeNode.push(pNode->m_pRight);
	}
}

// ====================���Դ���====================
// ������ȫ������������Ҷ�ӽڵ㣬�����ڵ㶼�������ӽڵ�
//            8
//        6      10
//       5 7    9  11
void Test1()
{
	printf("=====Test1 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);

	PrintTree(pNode8);

	printf("=====Test1: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	printf("=====Test1: MirrorIteratively=====\n");
	MirrorIteratively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// ���Զ���������Ҷ�ӽ��֮�⣬���ҵĽ�㶼����ֻ��һ�����ӽ��
//            8
//          7   
//        6 
//      5
//    4
void Test2()
{
	printf("=====Test2 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(pNode8, pNode7, nullptr);
	ConnectTreeNodes(pNode7, pNode6, nullptr);
	ConnectTreeNodes(pNode6, pNode5, nullptr);
	ConnectTreeNodes(pNode5, pNode4, nullptr);

	PrintTree(pNode8);

	printf("=====Test2: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	printf("=====Test2: MirrorIteratively=====\n");
	MirrorIteratively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// ���Զ���������Ҷ�ӽ��֮�⣬���ҵĽ�㶼����ֻ��һ�����ӽ��
//            8
//             7   
//              6 
//               5
//                4
void Test3()
{
	printf("=====Test3 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(pNode8, nullptr, pNode7);
	ConnectTreeNodes(pNode7, nullptr, pNode6);
	ConnectTreeNodes(pNode6, nullptr, pNode5);
	ConnectTreeNodes(pNode5, nullptr, pNode4);

	PrintTree(pNode8);

	printf("=====Test3: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	printf("=====Test3: MirrorIteratively=====\n");
	MirrorIteratively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// ���Կն������������Ϊ��ָ��
void Test4()
{
	printf("=====Test4 starts:=====\n");
	BinaryTreeNode* pNode = nullptr;

	PrintTree(pNode);

	printf("=====Test4: MirrorRecursively=====\n");
	MirrorRecursively(pNode);
	PrintTree(pNode);

	printf("=====Test4: MirrorIteratively=====\n");
	MirrorIteratively(pNode);
	PrintTree(pNode);
}

// ����ֻ��һ�����Ķ�����
void Test5()
{
	printf("=====Test5 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);

	PrintTree(pNode8);

	printf("=====Test4: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	printf("=====Test4: MirrorIteratively=====\n");
	MirrorIteratively(pNode8);
	PrintTree(pNode8);
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
