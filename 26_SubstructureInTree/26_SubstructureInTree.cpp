// 26_SubstructureInTree.cpp : 定义控制台应用程序的入口点。
//
// 面试题26：树的子结构
// 题目：输入两棵二叉树A和B，判断B是不是A的子结构。

#include "stdafx.h"
#include <cstdio>

struct BinaryTreeNode
{
	double                 m_dbValue;
	BinaryTreeNode*        m_pLeft;
	BinaryTreeNode*        m_pRight;
};

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool Equal(double num1, double num2);

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)//这个函数用来
{
	bool result = false;//记录A是否有B的子结构

	if (pRoot1 != nullptr && pRoot2 != nullptr)//判断两棵树是否都是非空的，只要有一个空就肯定不存在子结构含有的情况
	{
		if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))//找到树1中和树2根结点相同的节点，随后判断树1中是否有树2
			result = DoesTree1HaveTree2(pRoot1, pRoot2);
		if (!result)//如果根结点相等的情况下判断得到的结果是false，则说明需要继续遍历子节点，判断树1后续节点构成的子树是否和树2一样，先从左边开始
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);
		if (!result)//再从右边开始
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
	}

	return result;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)//判断树1中是否有树2
{
	if (pRoot2 == nullptr)//当树2全部节点比较完成时，说明树1中含有树2
		return true;

	if (pRoot1 == nullptr)//如果树2当前节点不为空，而树1中已经为空了，则说明不匹配
		return false;

	if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))//如果两颗树跟节点的值不相等，则肯定不匹配
		return false;

	//否则说明根结点的值匹配，此时在比较左子树和右子树是否相等
	return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
		DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool Equal(double num1, double num2)//用来判断double类型的两个数是否相等
{
	if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
		return true;
	else
		return false;
}

// ====================辅助测试代码====================
BinaryTreeNode* CreateBinaryTreeNode(double dbValue)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_dbValue = dbValue;
	pNode->m_pLeft = nullptr;
	pNode->m_pRight = nullptr;

	return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
	if (pParent != nullptr)
	{
		pParent->m_pLeft = pLeft;
		pParent->m_pRight = pRight;
	}
}

void DestroyTree(BinaryTreeNode* pRoot)
{
	if (pRoot != nullptr)
	{
		BinaryTreeNode* pLeft = pRoot->m_pLeft;
		BinaryTreeNode* pRight = pRoot->m_pRight;

		delete pRoot;
		pRoot = nullptr;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}

// ====================测试代码====================
void Test(char* testName, BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2, bool expected)
{
	if (HasSubtree(pRoot1, pRoot2) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s failed.\n", testName);
}

// 树中结点含有分叉，树B是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
void Test1()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test1", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点含有分叉，树B不是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
void Test2()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test2", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树B是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    2
//         /      
//        2        
//       /
//      5
void Test3()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test3", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树B不是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    3
//         /      
//        2        
//       /
//      5
void Test4()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test4", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有右子结点，树B是树A的子结构
//       8                   8
//        \                   \ 
//         8                   9   
//          \                   \
//           9                   2
//            \      
//             2        
//              \
//               5
void Test5()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, nullptr, pNodeB3);

	Test("Test5", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树A中结点只有右子结点，树B不是树A的子结构
//       8                   8
//        \                   \ 
//         8                   9   
//          \                 / \
//           9               3   2
//            \      
//             2        
//              \
//               5
void Test6()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test6", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树A为空树
void Test7()
{
	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test7", nullptr, pNodeB1, false);

	DestroyTree(pNodeB1);
}

// 树B为空树
void Test8()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, pNodeA3, pNodeA4);

	Test("Test8", pNodeA1, nullptr, false);

	DestroyTree(pNodeA1);
}

// 树A和树B都为空
void Test9()
{
	Test("Test9", nullptr, nullptr, false);
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
	Test8();
	Test9();

	return 0;
}

