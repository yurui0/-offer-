// test5.cpp : 定义控制台应用程序的入口点。
//
// 输入二叉树的前序遍历和中序遍历的结果，请重建该二叉树
// 利用先序和后序重构二叉树，一般情况下无法重构出唯一的二叉树，结果往往有多个,如果没有给定中序遍历则无法重构二叉树
//
//

#include "stdafx.h"
#include <exception>
#include "BinaryTree.h"
#include <cstdio>
#include <exception>
using namespace std;

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);
 
BinaryTreeNode * Construct(int * preorder, int * inorder, int length)   //检测
{
	if (preorder == nullptr || inorder == nullptr || length <= 0)
		return nullptr;

	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);//一个数组名+常数表示访问常数位置的数据,例如，int str [10] ,str+2 = str[2]

}

BinaryTreeNode * ConstructCore(int * startPreorder, int* endPreorder, int * startInorder, int * endInorder)
{
	//前序遍历序列的第一个数字是根结点的值
	int rootValue = startPreorder[0];
	BinaryTreeNode * root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	//即当前只有一个根结点，一个根结点构成一棵树
	if (startPreorder == endPreorder)
	{
		if (startInorder == endInorder && *startPreorder == *startInorder)
			return root;
		else
			throw exception("Invalid input");
	}

	//在中序遍历序列中找到根结点的值
	int* rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue) 
		++rootInorder;//这里是指针运算，指针所指的就是rootvalue的值

	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw exception("Invalid input");

	int leftLength = rootInorder - startInorder;//因为是指向同一个数组的，所以指针之间可以相加减，得到左子树的节点个数
	int * leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0)//接下来是递归构建
	{
		//构建左子树
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if (leftLength < endPreorder - startPreorder)
	{
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;
}



// ====================测试代码====================

void Test(char* testName, int* preorder, int* inorder, int length)
{
	if (testName != nullptr)

		printf("%s begins:\n", testName);

	printf("The preorder sequence is: ");

	for (int i = 0; i < length; ++i)
		printf("%d ", preorder[i]);

	printf("\n");

	printf("The inorder sequence is: ");

	for (int i = 0; i < length; ++i)
		printf("%d ", inorder[i]);

	printf("\n");

	try
	{
		BinaryTreeNode* root = Construct(preorder, inorder, length);
		PrintTree(root);
		DestroyTree(root);
	}
	catch (std::exception& exception)
	{
		printf("Invalid Input.\n");
	}
}

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8

void Test1()
{
	const int length = 8;
	int preorder[length] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inorder[length] = { 4, 7, 2, 1, 5, 3, 8, 6 };
	Test("Test1", preorder, inorder, length);
}


// 所有结点都没有右子结点

//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5

void Test2()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 5, 4, 3, 2, 1 };
	Test("Test2", preorder, inorder, length);

}


// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5

void Test3()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 1, 2, 3, 4, 5 };
	Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点

void Test4()
{
	const int length = 1;
	int preorder[length] = { 1 };
	int inorder[length] = { 1 };
	Test("Test4", preorder, inorder, length);
}


// 完全二叉树

//              1

//           /     \

//          2       3  

//         / \     / \

//        4   5   6   7

void Test5()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 5, 1, 6, 3, 7 };
	Test("Test5", preorder, inorder, length);
}


// 输入空指针
void Test6()
{

	Test("Test6", nullptr, nullptr, 0);
}


// 输入的两个序列不匹配

void Test7()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 8, 1, 6, 3, 7 };
	Test("Test7: for unmatched input", preorder, inorder, length);
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

