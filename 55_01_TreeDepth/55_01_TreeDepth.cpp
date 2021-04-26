// 55_01_TreeDepth.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������55��һ���������������
// ��Ŀ������һ�ö������ĸ���㣬���������ȡ��Ӹ���㵽Ҷ������ξ�����
// ��㣨������Ҷ��㣩�γ�����һ��·�����·���ĳ���Ϊ������ȡ�

#include "stdafx.h"

#include <cstdio>
#include "BinaryTree.h"

//˼·�ǣ����ֻ��һ���ڵ㣬�������Ϊ1����������ֻ��������û������������ô�������Ӧ���������������+1����������ֻ��������û������������ô�������Ӧ���������������+1
// ����ýڵ������������������������ô�������Ӧ������������������нϴ��+1
int TreeDepth(const BinaryTreeNode* pRoot) 
{
	if (pRoot == nullptr)
		return 0;

	int nLeft = TreeDepth(pRoot->m_pLeft);
	int nRight = TreeDepth(pRoot->m_pRight);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);//�����ʵ�����������������ʵ�֣�ֻ������������ ��Ԫ�����  ����
}

// ====================���Դ���====================
void Test(const char* testName, const BinaryTreeNode* pRoot, int expected)
{
	int result = TreeDepth(pRoot);
	if (expected == result)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

//            1
//         /      \
//        2        3
//       /\         \
//      4  5         6
//        /
//       7
void Test1()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode3, nullptr, pNode6);
	ConnectTreeNodes(pNode5, pNode7, nullptr);

	Test("Test1", pNode1, 4);

	DestroyTree(pNode1);
}

//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test2()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode5, nullptr);

	Test("Test2", pNode1, 5);

	DestroyTree(pNode1);
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

	Test("Test3", pNode1, 5);

	DestroyTree(pNode1);
}

// ����ֻ��1�����
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1, 1);

	DestroyTree(pNode1);
}

// ����û�н��
void Test5()
{
	Test("Test5", nullptr, 0);
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

