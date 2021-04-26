// 32_01_PrintTreeFromTopToBottom.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������32��һ���������д������´�ӡ������
// ��Ŀ���������´�ӡ����������ÿ����㣬ͬһ��Ľ�㰴�մ����ҵ�˳���ӡ��

#include "stdafx.h"

#include <cstdio>
#include "BinaryTree.h"
#include <deque>

void PrintFromTopToBottom(BinaryTreeNode* pRoot)//���ö���ʵ�ָ�����ӡ������ǰ�ڵ��ӡʱ�����������ӽڵ�ѹ����У�����Ƚ��ȳ����ص㣬ʵ�ֲ����д������´�ӡ
{
	if (pRoot == nullptr)//���������ڴ�ӡ
		return;

	std::deque<BinaryTreeNode *> dequeTreeNode;//���У����ж��д��ڵ�Ԫ���Ƕ������Ľڵ�

	dequeTreeNode.push_back(pRoot);//���Ƚ�����������

	while (dequeTreeNode.size())//����Ϊǰ��������жϣ�����������һ������㣬��˶�����һ��ʼ����Ϊnull��
	{
		BinaryTreeNode *pNode = dequeTreeNode.front();//��ȡ�����е���Ԫ��
		dequeTreeNode.pop_front();//�������Ƴ���Ԫ��

		printf("%d ", pNode->m_nValue);//����Ԫ��

		if (pNode->m_pLeft)//��ǰ�ڵ����ӽڵ㲻Ϊ�գ������ӽڵ������
			dequeTreeNode.push_back(pNode->m_pLeft);

		if (pNode->m_pRight)//��ǰ�ڵ����ӽڵ㲻Ϊ�գ������ӽڵ������
			dequeTreeNode.push_back(pNode->m_pRight);
	}
}

// ====================���Դ���====================
void Test(char* testName, BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	PrintTree(pRoot);

	printf("The nodes from top to bottom, from left to right are: \n");
	PrintFromTopToBottom(pRoot);

	printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16      ��ʱ����˳��Ϊ  10-6-14-4-8-12-16
void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	Test("Test1", pNode10);

	DestroyTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode1, nullptr);

	Test("Test2", pNode5);

	DestroyTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test3()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode5);

	Test("Test3", pNode1);

	DestroyTree(pNode1);
}

// ����ֻ��1�����
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyTree(pNode1);
}

// ����û�н��
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

