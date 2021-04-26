// 60_DicesProbability.cpp : �������̨Ӧ�ó������ڵ㡣
 //

// ������60��n�����ӵĵ���
// ��Ŀ����n���������ڵ��ϣ��������ӳ���һ��ĵ���֮��Ϊs������n����ӡ��s
// �����п��ܵ�ֵ���ֵĸ��ʡ�

#include "stdafx.h"

#include <cstdio>
#include <math.h>

int g_maxValue = 6;

// ====================����һ==================== //���õݹ��˼·���
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

void PrintProbability_Solution1(int number)//������������number��ʾn������
{
	if (number < 1)//�����Ƿ�Ϸ�
		return;

	int maxSum = number * g_maxValue;//��Ϊһ�����ӵ�ֵ��ΧΪ[1,6]�����n�����ӵĺ����λ6n
	int* pProbabilities = new int[maxSum - number + 1];//�����洢���ϵ�n�����ӵĺ�sum�����飬����ķ�Χ��6n-n+1����Ϊsum��СΪn�����λ6n��
														// ���ڡ�+1������Ϊ������������ʾ������֮������ĸ���Ҫ���������ֵ��һ
	for (int i = number; i <= maxSum; ++i)
		pProbabilities[i - number] = 0;//��ʼ������sum��ΧΪ[n,6n]֮��ĸ�ֵ����Ӧ�������о���[0,6n-n]

	Probability(number, pProbabilities);//����n�����ӿ��ܳ��ֵ�sum�Ĵ�����Ϊ�������������̵�

	int total = pow((double)g_maxValue, number); //pow���ݺ�������pow(x,y)��ʾx^y��x��y���ݣ������Ǽ���6^n�Σ���Ϊn�����ӵ����е�������Ϊ6x6x6...x6��Ҳ����6^n
	for (int i = number; i <= maxSum; ++i)
	{
		double ratio = (double)pProbabilities[i - number] / total;//����ÿһ�ֿ��ܵĽ�����ֵĸ���
		printf("%d: %e\n", i, ratio);
	}

	delete[] pProbabilities;
}

void Probability(int number, int* pProbabilities)
{
	//�����ǽ�n�����ӷ�Ϊ���ѣ�һ��һ�����ӣ���һ��n-1���������ǵ�һ�����ӵ�ֵ��[1,6]��ʼ�ֱ����ʣ��n-1�ѵĿ��ܵ�sum��
	for (int i = 1; i <= g_maxValue; ++i) 
		Probability(number, number, i, pProbabilities);
}

void Probability(int original, int current, int sum,int* pProbabilities)// original��ʾ������n��current��ʾ����Ϊ���Ѻ�ڶ��ѵ�������
															// sum��ʾ��Ӧcurrent���ֵĶѵ�����£�ǰ��һ���ѵ����Ӻ�sum��pProbabilities�洢��ͬ���Ӷ�Ӧ����������
{
	if (current == 1)
	{
		pProbabilities[sum - original]++;
	}
	else
	{
		for (int i = 1; i <= g_maxValue; ++i)
		{
			Probability(original, current - 1, i + sum, pProbabilities);
		}
	}
}

// ====================������====================
void PrintProbability_Solution2(int number) //��һ��˼·�ǣ�����ѭ�������ӵ���
{
	if (number < 1)//�����Ƿ�Ϸ�
		return;

	int* pProbabilities[2];//�����������飬��һ������ĵ�n��������Ӻ�Ϊn���ֵĴ�������һ������ĵ�n�����ֱ�ʾǰһ�������Ӧ�ĵ�[n-1,n-6]������֮��
	pProbabilities[0] = new int[g_maxValue * number + 1];
	pProbabilities[1] = new int[g_maxValue * number + 1];
	for (int i = 0; i < g_maxValue * number + 1; ++i)
	{
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}

	int flag = 0;
	for (int i = 1; i <= g_maxValue; ++i)
		pProbabilities[flag][i] = 1;

	for (int k = 2; k <= number; ++k)
	{
		for (int i = 0; i < k; ++i)
			pProbabilities[1 - flag][i] = 0;

		for (int i = k; i <= g_maxValue * k; ++i)
		{
			pProbabilities[1 - flag][i] = 0;
			for (int j = 1; j <= i && j <= g_maxValue; ++j)
				pProbabilities[1 - flag][i] += pProbabilities[flag][i - j]; //��һ������ĵ�n�����ֱ�ʾǰһ�������Ӧ�ĵ�[n - 1, n - 6]������֮��
		}

		flag = 1 - flag;//����һ��ѭ���н���������������������
	}

	double total = pow((double)g_maxValue, number);//pow���ݺ�������pow(x,y)��ʾx^y��x��y���ݣ������Ǽ���6^n�Σ���Ϊn�����ӵ����е�������Ϊ6x6x6...x6��Ҳ����6^n
	for (int i = number; i <= g_maxValue * number; ++i)
	{
		double ratio = (double)pProbabilities[flag][i] / total;//����ÿһ�ֿ��ܵĽ�����ֵĸ���
		printf("%d: %e\n", i, ratio);
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}

// ====================���Դ���====================
void Test(int n)
{
	printf("Test for %d begins:\n", n);

	printf("Test for solution1\n");
	PrintProbability_Solution1(n);

	printf("Test for solution2\n");
	PrintProbability_Solution2(n);

	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(4);

	Test(11);

	Test(0);

	return 0;
}

