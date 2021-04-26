// 33_SquenceOfBST.cpp : 定义控制台应用程序的入口点。
//

// 面试题33：二叉搜索树的后序遍历序列
// 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
// 如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。

#include "stdafx.h"

#include <cstdio>

// BST：Binary Search Tree，二叉搜索树
// 二叉搜索树的特点：它或者是一棵空树，或者是具有下列性质的二叉树： 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 
// 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值

bool VerifySquenceOfBST(int sequence[], int length)
{
	if (sequence == nullptr || length <= 0)//序列为空不存在结果
		return false;

	int root = sequence[length - 1];//获得根节点的值，后续遍历的特点

	// 在二叉搜索树中左子树的结点小于根结点，而根节点的左右子树都是二叉搜索树，所以找到最后一个符合小于根节点的值，就为左子树的根结点
	int i = 0;
	for (; i < length - 1; ++i)//这里是找到当前树中根节点的左子树的根结点
	{
		if (sequence[i] > root)
			break;
	}

	// 在二叉搜索树中右子树的结点大于根结点
	int j = i;
	for (; j < length - 1; ++j)//这里是找到当前树中根结点的右子树的根结点
	{
		if (sequence[j] < root)//如果在右子树中存在小于根结点的节点值，则肯定是错误的，不存在这课二叉搜索树
			return false;
	}

	// 判断左子树是不是二叉搜索树
	bool left = true;
	if (i > 0)
		left = VerifySquenceOfBST(sequence, i);

	// 判断右子树是不是二叉搜索树
	bool right = true;
	if (i < length - 1)
		right = VerifySquenceOfBST(sequence + i, length - i - 1);

	return (left && right);
}

// ====================测试代码====================
void Test(const char* testName, int sequence[], int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (VerifySquenceOfBST(sequence, length) == expected)
		printf("passed.\n");
	else
		printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
	int data[] = { 4, 8, 6, 12, 16, 14, 10 };
	Test("Test1", data, sizeof(data) / sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
	int data[] = { 4, 6, 7, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), true);
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
void Test3()
{
	int data[] = { 1, 2, 3, 4, 5 };
	Test("Test3", data, sizeof(data) / sizeof(int), true);
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
void Test4()
{
	int data[] = { 5, 4, 3, 2, 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), true);
}

// 树中只有1个结点
void Test5()
{
	int data[] = { 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), true);
}

void Test6()
{
	int data[] = { 7, 4, 6, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), false);
}

void Test7()
{
	int data[] = { 4, 6, 12, 8, 16, 14, 10 };
	Test("Test7", data, sizeof(data) / sizeof(int), false);
}

void Test8()
{
	Test("Test8", nullptr, 0, false);
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

	return 0;
}

