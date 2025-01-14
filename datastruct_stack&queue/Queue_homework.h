#pragma once
#include<iostream>
using namespace std;

typedef int QElement;

typedef struct Qnode {
	QElement data; 
	Qnode* next;  
} *Queuelist; 

typedef struct {
	Queuelist rear; // 尾指针
} Queue;

void init_queue(Queue& q)//初始化
{
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//判空
{
	return q.rear == nullptr;
}

void count_queue(Queue q)
{
	Queuelist temp = q.rear->next;
	int count = 0;
	do {
		count++;
		temp = temp->next;
	} while (temp != q.rear->next);
	cout << "Count: " << count << endl;
}

void display_queue(Queue q) {
	if (IsEmpty_queue(q)) {  // 如果队列为空，直接返回
		cout << "Queue is empty." << endl;
		return;
	}

	Queuelist temp = q.rear->next;  // 从队头开始遍历
	cout << "Queue: ";
	do {
		cout << temp->data << " ";  // 打印当前结点的数据
		temp = temp->next;  // 移动到下一个结点
	} while (temp != q.rear->next);  // 循环直到回到队头
	cout << endl;

	count_queue(q);  // 打印队列的元素数量
	cout << endl;
}

void Push_queue(Queue& q, QElement d) {
	Queuelist Newmodels = new Qnode;  // 创建新节点
	Newmodels->data = d;  // 设置数据
	Newmodels->next = nullptr;  // 初始化新节点的 next 指针

	if (IsEmpty_queue(q)) {  // 如果队列为空
		q.rear = Newmodels;  // 将新节点设为队尾
		Newmodels->next = Newmodels;  // 队尾指向自身，形成循环
	}
	else {  // 队列不为空
		Newmodels->next = q.rear->next;  // 新节点指向队头
		q.rear->next = Newmodels;  // 当前队尾指向新节点
		q.rear = Newmodels;  // 更新队尾
	}
}

void Pop_queue(Queue& q, QElement& data)//出队
{
	if (IsEmpty_queue(q))//判空
	{
		cout << "The queue is empty." << endl;
	}
	else
	{
		Queuelist temp = q.rear->next;
		data = temp->data;
		if (q.rear->next == q.rear) {  // 只有一个元素
			delete temp;
			q.rear = nullptr;  // 队列为空
		}
		else {
			q.rear->next = temp->next;  // 更新队头
			delete temp;
		}
		cout << "Pop successfully!!" << endl;
		display_queue(q);
	}
}

// 设置并初始化队列
void set_queue(Queue& q) {
	init_queue(q);  // 初始化队列
	QElement data;
	cout << "Please input queue data. Enter 9999 to quit." << endl;
	cin >> data;
	while (data != 9999) {
		Push_queue(q, data);  // 入队
		cin >> data;
	}
	display_queue(q);  // 显示队列
}