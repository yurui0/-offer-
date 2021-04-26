//==================================================================
// ����ָOffer�����������Թپ������ͱ���⡷����
// ���ߣ��κ���
//==================================================================

// ������9��������ջʵ�ֶ���
// ��Ŀ��������ջʵ��һ�����С����е��������£���ʵ��������������appendTail
// ��deleteHead���ֱ�����ڶ���β����������ڶ���ͷ��ɾ�����Ĺ��ܡ�

#pragma once
#include <stack>
#include <exception>

using namespace std;

template <typename T> class CQueue   // template��c++ģ�壬���ͱ�̵Ļ���
{
public:
	CQueue(void);
	~CQueue(void);

	// �ڶ���ĩβ���һ�����
	void appendTail(const T& node);

	// ɾ�����е�ͷ���
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T> CQueue<T>::CQueue(void)
{
}

template <typename T> CQueue<T>::~CQueue(void)
{
}

template<typename T> void CQueue<T>::appendTail(const T& element) //���һ��stack��������ݣ��Ƚ������������Ҳ���������queue�������ݶ�Ӧ�ĺ��������������ǲ����һ��stack
{
	stack1.push(element);// 
}

template<typename T> T CQueue<T>::deleteHead()//�ӵ�һ��stack���ó����ݣ��Ƚ��������Ȼ�����ڶ���stack�У�����ȳ�����Ȼ�󸺸����������մӵڶ���stack�����ľ��ǣ��Ƚ��ȳ���
{                                                   // �����Ӧ���ǴӶ���queue��ɾ�����ݣ�һ��ɾ�����ݾ�Ҫ�ѵ�ǰ��һ��stack�е�����ȫ���Ƶ��ڶ���stack���������ڶ���stack
	if (stack2.size() <= 0) // �ڶ���stackΪ��
	{
		while (stack1.size()>0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if (stack2.size() == 0)//��һ��ջ�о��ǿյģ�˵�������ǿյ�
		throw new exception("queue is empty");

	T head = stack2.top();//ȡ�õڶ���stack��ǰ�ĵ�һ������
	stack2.pop();// ȡ��֮�����ݳ�ջ  stack.pop()��stack.peek()������ ��ͬ��:��Ҷ�����ջ����ֵ�� ��ͬ��:peek ���ı�ջ��ֵ(��ɾ��ջ����ֵ),pop���ջ����ֵɾ��

	return head;
}



