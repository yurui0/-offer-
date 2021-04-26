// 55_02_BalancedBinaryTree.cpp : 定义控制台应用程序的入口点。
//

// 面试题55（二）：平衡二叉树
// 题目：输入一棵二叉树的根结点，判断该树是不是平衡二叉树。
// 平衡二叉树的定义：如果某二叉树中任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。


#include "stdafx.h"

#include <cstdio>
#include "BinaryTree.h"

// ====================方法1====================
int TreeDepth(const BinaryTreeNode* pRoot) // 55-01的代码，作用是对给定根结点的二叉树搜索其深度
{
	if (pRoot == nullptr)
		return 0;

	int nLeft = TreeDepth(pRoot->m_pLeft);
	int nRight = TreeDepth(pRoot->m_pRight);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

bool IsBalanced_Solution1(const BinaryTreeNode* pRoot)//考虑到55_01的思路，对每一个节点分别计算其左子树和右子树的深度，只要两者
{
	if (pRoot == nullptr)
		return true;

	int left = TreeDepth(pRoot->m_pLeft);
	int right = TreeDepth(pRoot->m_pRight);
	int diff = left - right;
	if (diff > 1 || diff < -1)
		return false;
	 
	return IsBalanced_Solution1(pRoot->m_pLeft) //这里是通过递归的方式，开始遍历以当前节点的左子节点和右子节点为根结点的左右子树
		&& IsBalanced_Solution1(pRoot->m_pRight);// 当前这种递归有一个通用的不足，就是会重复遍历多次同一个节点
}

// ====================方法2====================
bool IsBalanced(const BinaryTreeNode* pRoot, int* pDepth);

bool IsBalanced_Solution2(const BinaryTreeNode* pRoot)//初始函数
{
	int depth = 0;
	return IsBalanced(pRoot, &depth);//一开始深度为0
}

bool IsBalanced(const BinaryTreeNode* pRoot, int* pDepth)//depth是计算某一节点的深度（等于该节点到叶节点的路径的长度）
{
	if (pRoot == nullptr)//空子树的深度为0
	{
		*pDepth = 0;
		return true;
	}

	int left, right;
	if (IsBalanced(pRoot->m_pLeft, &left)
		&& IsBalanced(pRoot->m_pRight, &right)) //遍历某节点的左右子节点后，我们根据其左右子树的深度判断其是否是平衡的，并得到当前节点的深度游
	{                                           // 当最后遍历到树的根结点的时候，也就判断了整棵二叉树是不是平衡二叉树
		int diff = left - right;
		if (diff <= 1 && diff >= -1)
		{
			*pDepth = 1 + (left > right ? left : right);
			return true;
		}
	} 

	return false;
}

// ====================测试代码====================
void Test(const char* testName, const BinaryTreeNode* pRoot, bool expected)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("Solution1 begins: ");
	if (IsBalanced_Solution1(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	printf("Solution2 begins: ");
	if (IsBalanced_Solution2(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 完全二叉树
//             1
//         /      \
//        2        3
//       /\       / \
//      4  5     6   7
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
	ConnectTreeNodes(pNode3, pNode6, pNode7);

	Test("Test1", pNode1, true);

	DestroyTree(pNode1);
}

// 不是完全二叉树，但是平衡二叉树
//             1
//         /      \
//        2        3
//       /\         \
//      4  5         6
//        /
//       7
void Test2()
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

	Test("Test2", pNode1, true);

	DestroyTree(pNode1);
}

// 不是平衡二叉树
//             1
//         /      \
//        2        3
//       /\         
//      4  5        
//        /
//       6
void Test3()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode5, pNode6, nullptr);

	Test("Test3", pNode1, false);

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
void Test4()
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

	Test("Test4", pNode1, false);

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
void Test5()
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

	Test("Test5", pNode1, false);

	DestroyTree(pNode1);
}

// 树中只有1个结点
void Test6()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test6", pNode1, true);

	DestroyTree(pNode1);
}

// 树中没有结点
void Test7()
{
	Test("Test7", nullptr, true);
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

