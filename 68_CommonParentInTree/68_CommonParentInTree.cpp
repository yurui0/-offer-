// 68_CommonParentInTree.cpp : 定义控制台应用程序的入口点。
//

// 面试题68：树中两个结点的最低公共祖先
// 题目：输入两个树结点，求它们的最低公共祖先。

#include "stdafx.h"
#include <cstdio>
#include "Tree.h"
#include <list>
#include <iostream>
using namespace std;



//这种方法是针对：1、不是二叉搜索树甚至不是二叉树的情况；2、树中的结点没有指向父节点的指针
// GetNodePath用来得到从根结点pRoot开始到达结点pNode的路径，这条路径保存在path中
bool GetNodePath(const TreeNode* pRoot, const TreeNode* pNode, list<const TreeNode*>& path)
{
	if (pRoot == pNode)
		return true;

	path.push_back(pRoot);

	bool found = false;

	vector<TreeNode*>::const_iterator i = pRoot->m_vChildren.begin();
	while (!found && i < pRoot->m_vChildren.end())
	{
		found = GetNodePath(*i, pNode, path);
		++i;
	}

	if (!found)
		path.pop_back();

	return found;
}

//函数GetLastCommonNode用来得到两条路径path1和path2的最后一个公共节点
const TreeNode* GetLastCommonNode(const list<const TreeNode*>& path1,const list<const TreeNode*>& path2)
{
	list<const TreeNode*>::const_iterator iterator1 = path1.begin();
	list<const TreeNode*>::const_iterator iterator2 = path2.begin();

	const TreeNode* pLast = nullptr;

	while (iterator1 != path1.end() && iterator2 != path2.end())
	{
		if (*iterator1 == *iterator2)
			pLast = *iterator1;

		iterator1++;
		iterator2++;
	}

	return pLast;
}

//GetLastCommonParent函数先调用GetNodePath得到pRoot到达pNode1的路径path1,再得到pRoot到达pNode2的路径path2，最后调用GetLastCommonNode得到path1和path2
// 的最后一个公共节点，即我们要找的最低公共祖先
const TreeNode* GetLastCommonParent(const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2)
{
	if (pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr)
		return nullptr;

	list<const TreeNode*> path1;
	GetNodePath(pRoot, pNode1, path1);

	list<const TreeNode*> path2;
	GetNodePath(pRoot, pNode2, path2);

	return GetLastCommonNode(path1, path2);
}

// ====================测试代码====================
void Test(const char* testName, const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2, TreeNode* pExpected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	const TreeNode* pResult = GetLastCommonParent(pRoot, pNode1, pNode2);

	if ((pExpected == nullptr && pResult == nullptr) ||
		(pExpected != nullptr && pResult != nullptr && pResult->m_nValue == pExpected->m_nValue))
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 形状普通的树
//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
void Test1()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);
	TreeNode* pNode6 = CreateTreeNode(6);
	TreeNode* pNode7 = CreateTreeNode(7);
	TreeNode* pNode8 = CreateTreeNode(8);
	TreeNode* pNode9 = CreateTreeNode(9);
	TreeNode* pNode10 = CreateTreeNode(10);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode1, pNode3);

	ConnectTreeNodes(pNode2, pNode4);
	ConnectTreeNodes(pNode2, pNode5);

	ConnectTreeNodes(pNode4, pNode6);
	ConnectTreeNodes(pNode4, pNode7);

	ConnectTreeNodes(pNode5, pNode8);
	ConnectTreeNodes(pNode5, pNode9);
	ConnectTreeNodes(pNode5, pNode10);

	Test("Test1", pNode1, pNode6, pNode8, pNode2);
}

// 树退化成一个链表
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
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	Test("Test2", pNode1, pNode5, pNode4, pNode3);
}

// 树退化成一个链表，一个结点不在树中
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test3()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	TreeNode* pNode6 = CreateTreeNode(6);

	Test("Test3", pNode1, pNode5, pNode6, nullptr);
}

// 输入nullptr
void Test4()
{
	Test("Test4", nullptr, nullptr, nullptr, nullptr);
}


int _tmain(int argc, _TCHAR* argv[])
{

	Test1();
	Test2();
	Test3();
	Test4();

	

	return 0;
}

