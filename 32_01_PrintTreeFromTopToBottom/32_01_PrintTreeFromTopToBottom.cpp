// 32_01_PrintTreeFromTopToBottom.cpp : 定义控制台应用程序的入口点。
//
// 面试题32（一）：不分行从上往下打印二叉树
// 题目：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。

#include "stdafx.h"

#include <cstdio>
#include "BinaryTree.h"
#include <deque>

void PrintFromTopToBottom(BinaryTreeNode* pRoot)//运用队列实现辅助打印，当当前节点打印时，将其左右子节点压入队列，结合先进先出的特点，实现不分行从上往下打印
{
	if (pRoot == nullptr)//空树不存在打印
		return;

	std::deque<BinaryTreeNode *> dequeTreeNode;//队列，其中队列存在的元素是二叉树的节点

	dequeTreeNode.push_back(pRoot);//首先将根结点进队列

	while (dequeTreeNode.size())//（因为前面进行了判断，最起码是有一个根结点，因此队列中一开始不会为null）
	{
		BinaryTreeNode *pNode = dequeTreeNode.front();//获取队列中的首元素
		dequeTreeNode.pop_front();//队列中移除首元素

		printf("%d ", pNode->m_nValue);//输入元素

		if (pNode->m_pLeft)//当前节点左子节点不为空，则左子节点进队列
			dequeTreeNode.push_back(pNode->m_pLeft);

		if (pNode->m_pRight)//当前节点左子节点不为空，则右子节点进队列
			dequeTreeNode.push_back(pNode->m_pRight);
	}
}

// ====================测试代码====================
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
//      4  8     12  16      此时输入顺序为  10-6-14-4-8-12-16
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

// 树中只有1个结点
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyTree(pNode1);
}

// 树中没有结点
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

