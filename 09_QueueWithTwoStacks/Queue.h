//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题9：用两个栈实现队列
// 题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail
// 和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。

#pragma once
#include <stack>
#include <exception>

using namespace std;

template <typename T> class CQueue   // template是c++模板，泛型编程的基础
{
public:
	CQueue(void);
	~CQueue(void);

	// 在队列末尾添加一个结点
	void appendTail(const T& node);

	// 删除队列的头结点
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

template<typename T> void CQueue<T>::appendTail(const T& element) //向第一个stack中添加数据（先进后出），这里也就是向队列queue插入数据对应的函数，插入数据是插入第一个stack
{
	stack1.push(element);// 
}

template<typename T> T CQueue<T>::deleteHead()//从第一个stack中拿出数据（先进后出），然后放入第二个stack中（后进先出），然后负负得正，最终从第二个stack出来的就是（先进先出）
{                                                   // 这里对应的是从队列queue中删除数据，一旦删除数据就要把当前第一个stack中的数据全部移到第二个stack，最后操作第二个stack
	if (stack2.size() <= 0) // 第二个stack为空
	{
		while (stack1.size()>0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if (stack2.size() == 0)//第一个栈中就是空的，说明队列是空的
		throw new exception("queue is empty");

	T head = stack2.top();//取得第二个stack当前的第一个数据
	stack2.pop();// 取出之后将数据出栈  stack.pop()和stack.peek()的区别 相同点:大家都返回栈顶的值。 不同点:peek 不改变栈的值(不删除栈顶的值),pop会把栈顶的值删除

	return head;
}



