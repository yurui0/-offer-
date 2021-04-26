// 12_StringPathInMatrix.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������12�������е�·��
// ��Ŀ�������һ�������������ж���һ���������Ƿ����һ������ĳ�ַ�������
// �ַ���·����·�����ԴӾ���������һ��ʼ��ÿһ�������ھ����������ҡ�
// �ϡ����ƶ�һ�����һ��·�������˾����ĳһ����ô��·�������ٴν���
// �ø��ӡ������������3��4�ľ����а���һ���ַ�����bfce����·����·���е���
// ĸ���»��߱�������������в������ַ�����abfb����·������Ϊ�ַ����ĵ�һ��
// �ַ�bռ���˾����еĵ�һ�еڶ�������֮��·�������ٴν���������ӡ�
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
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr) //ǰ���жϣ���֤����Ϸ�
		return false;

	bool *visited = new bool[rows * cols]; //��������������ʶ·���Ƿ��Ѿ�������ÿ������
	memset(visited, 0, rows * cols);//memset���ڴ���亯������visited�е�ǰλ�ú����rows * cols���ֽ� ��typedef unsigned int size_t ���� 0 �滻������ visited

	int pathLength = 0;//������¼�������ַ��������ǰƥ����Ӵ����±�
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (hasPathCore(matrix, rows, cols, row, col, str,pathLength, visited))//Ŀ���Ǵ�ÿһ�����������ƥ�䣬��Ϊ����������ģ�����Ҫ��ÿ���㿪ʼ���м��
			{
				return true;
			}
		}
	}

	delete[] visited;

	return false;
}

bool hasPathCore(const char* matrix, int rows, int cols, int row,int col, const char* str, int& pathLength, bool* visited)
{ //�����������������壺���󡢾�����С�������С��������ַ�����һ���ַ���ʼƥ��ʱ��ľ����е������ꡢ�����ꡢ������ַ�������ʾ·���Ĳ�������

	if (str[pathLength] == '\0') //pathlength�Ǽ�¼��ƥ����Ӵ��ĳ��ȣ������������˵�������д���һ��·�����ַ�����ƥ�䣬��ƥ��ɹ�
		return true;

	bool hasPath = false;//bool������������¼����ǰ������Χ�ĸ��㣨�������ң����Ƿ���ڷ���str�еĵ�ǰ���괦�ַ�����ֵ����Ӧ��
	//����֮�⣬�������

	if (row >= 0 && row < rows && col >= 0 && col < cols   //�������Ҫ��������
		&& matrix[row * cols + col] == str[pathLength]     //�����е�ǰ����ַ�����ֵ�Ƿ�ƥ��
		&& !visited[row * cols + col])                      //��ǰ��û�з��ʹ�
	{
		++pathLength;//��ǰ�����str�е�ǰ����ַ��������+1,���������μ������Χ�ĸ���
		visited[row * cols + col] = true;

		hasPath = hasPathCore(matrix, rows, cols, row, col - 1,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row - 1, col,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row, col + 1,
			str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row + 1, col,
			str, pathLength, visited);

		if (!hasPath) //��ǰ�ڵ���Χ�ĸ���û��ƥ��ģ���˻���һ��
		{
			--pathLength;
			visited[row * cols + col] = false;
		}
	}

	return hasPath;
}

// ====================���Դ���====================
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

