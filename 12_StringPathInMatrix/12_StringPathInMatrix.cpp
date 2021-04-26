// 12_StringPathInMatrix.cpp : 定义控制台应用程序的入口点。
//
// 面试题12：矩阵中的路径
// 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有
// 字符的路径。路径可以从矩阵中任意一格开始，每一步可以在矩阵中向左、右、
// 上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入
// 该格子。例如在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字
// 母用下划线标出）。但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个
// 字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。
// A B T G
// C F C S
// J D E H

#include "stdafx.h"
#include <cstdio>
#include <string>
#include <stack>
using namespace std;


bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* visited);

bool hasPath(const char* matrix, int rows, int cols, const char* str)
{
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr) //前期判断，保证矩阵合法
		return false;

	bool *visited = new bool[rows * cols]; //布尔矩阵，用来标识路径是否已经进入了每个格子
	memset(visited, 0, rows * cols);//memset是内存分配函数，将visited中当前位置后面的rows * cols个字节 （typedef unsigned int size_t ）用 0 替换并返回 visited

	int pathLength = 0;//用来记录待检测的字符串与矩阵当前匹配的子串的下标
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (hasPathCore(matrix, rows, cols, row, col, str,pathLength, visited))//目的是从每一个点出发进行匹配，因为矩阵是随机的，所以要从每个点开始进行检测
			{
				return true;
			}
		}
	}

	delete[] visited;

	return false;
}

bool hasPathCore(const char* matrix, int rows, int cols, int row,int col, const char* str, int& pathLength, bool* visited)
{ //函数各个参数的意义：矩阵、矩阵的行、矩阵的列、与待检测字符串第一个字符开始匹配时候的矩阵中的行坐标、列坐标、待检测字符串、标示路径的布尔矩阵

	if (str[pathLength] == '\0') //pathlength是记录的匹配的子串的长度，满足这个条件说明矩阵中存在一个路径和字符串相匹配，即匹配成功
		return true;

	bool hasPath = false;//bool变量，用来记录矩阵当前点其周围四个点（上下左右），是否存在符合str中的当前坐标处字符串的值所对应的
	//除此之外，如果存在

	if (row >= 0 && row < rows && col >= 0 && col < cols   //检索序号要符合条件
		&& matrix[row * cols + col] == str[pathLength]     //矩阵中当前点和字符串中值是否匹配
		&& !visited[row * cols + col])                      //当前点没有访问过
	{
		++pathLength;//当前点符合str中当前检测字符，则序号+1,接下来依次检测其周围四个点
		visited[row * cols + col] = true;

		hasPath = hasPathCore(matrix, rows, cols, row, col - 1,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row - 1, col,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row, col + 1,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row + 1, col,
			str, pathLength, visited);

		if (!hasPath) //当前节点周围四个都没有匹配的，因此回退一步
		{
			--pathLength;
			visited[row * cols + col] = false;
		}
	}

	return hasPath;
}

// ====================测试代码====================
void Test(const char* testName, const char* matrix, int rows, int cols, const char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (hasPath(matrix, rows, cols, str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

//ABTG
//CFCS
//JDEH

//BFCE
void Test1()
{
	const char* matrix = "ABTGCFCSJDEH";
	const char* str = "BFCE";

	Test("Test1", (const char*)matrix, 3, 4, str, true);
}

//ABCE
//SFCS
//ADEE

//SEE
void Test2()
{
	const char* matrix = "ABCESFCSADEE";
	const char* str = "SEE";

	Test("Test2", (const char*)matrix, 3, 4, str, true);
}

//ABTG
//CFCS
//JDEH

//ABFB
void Test3()
{
	const char* matrix = "ABTGCFCSJDEH";
	const char* str = "ABFB";

	Test("Test3", (const char*)matrix, 3, 4, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SLHECCEIDEJFGGFIE
void Test4()
{
	const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	const char* str = "SLHECCEIDEJFGGFIE";

	Test("Test4", (const char*)matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEM
void Test5()
{
	const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	const char* str = "SGGFIECVAASABCEHJIGQEM";

	Test("Test5", (const char*)matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEEJIGOEM
void Test6()
{
	const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	const char* str = "SGGFIECVAASABCEEJIGOEM";

	Test("Test6", (const char*)matrix, 5, 8, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEMS
void Test7()
{
	const char* matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
	const char* str = "SGGFIECVAASABCEHJIGQEMS";

	Test("Test7", (const char*)matrix, 5, 8, str, false);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAA
void Test8()
{
	const char* matrix = "AAAAAAAAAAAA";
	const char* str = "AAAAAAAAAAAA";

	Test("Test8", (const char*)matrix, 3, 4, str, true);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAAA
void Test9()
{
	const char* matrix = "AAAAAAAAAAAA";
	const char* str = "AAAAAAAAAAAAA";

	Test("Test9", (const char*)matrix, 3, 4, str, false);
}

//A

//A
void Test10()
{
	const char* matrix = "A";
	const char* str = "A";

	Test("Test10", (const char*)matrix, 1, 1, str, true);
}

//A

//B
void Test11()
{
	const char* matrix = "A";
	const char* str = "B";

	Test("Test11", (const char*)matrix, 1, 1, str, false);
}

void Test12()
{
	Test("Test12", nullptr, 0, 0, nullptr, false);
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
	Test10();
	Test11();
	Test12();

	return 0;
}

