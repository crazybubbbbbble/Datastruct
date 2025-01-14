#pragma once
#include<iostream>
using namespace std;

typedef int QElement;

typedef struct Qnode {
	QElement data; // 存储队列中的数据
	Qnode* next;  // 指向下一个节点的指针
} *Queuelist; // 这里是 Qnode* 的定义

typedef struct {
	Queuelist head; // 头指针
	Queuelist rear; // 尾指针
} Queue;

void init_queue(Queue& q)//初始化
{
	q.head = nullptr;
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//判空
{
	if (q.head == nullptr) { return 1; }
	else { return 0; }
}

void count_queue(Queue q)
{
	Queuelist temp = q.head;
	int count = 0;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	cout << "Count: " << count << endl;
}

void display_queue(Queue q)
{
	Queuelist temp = q.head;
	cout << "Queue: ";
	while (temp != nullptr)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
	count_queue(q);
	cout << endl;
}

void Push_queue(Queue& q, QElement d)//入队
{
	Queuelist Newmodels = new Qnode;
	Newmodels->data = d;
	Newmodels->next = nullptr;

	if (IsEmpty_queue(q))//如果队列为空
	{
		q.head = Newmodels;
		q.rear = Newmodels;
	}
	else//不为空则在队尾插入
	{
		q.rear->next = Newmodels;
		q.rear = Newmodels;
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
		Queuelist temp = q.head;
		data = q.head->data;
		q.head = q.head->next;
		if (q.head == nullptr)
		{
			q.rear = nullptr;
		}
		delete temp;
	}
}

void set_queue(Queue& q)//设置一个队列
{
	init_queue(q); // 初始化队列
	QElement data;
	cout << "Please input queue data.Enter 9999 to quit." << endl;
	cin >> data;
	while (data != 9999)
	{
		Push_queue(q, data);
		cin >> data;
	}
	display_queue(q);
}