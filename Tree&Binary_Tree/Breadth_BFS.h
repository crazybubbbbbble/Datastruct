#pragma once
#include<iostream>
#include<stdlib.h>
#include <algorithm>
using namespace std;

typedef char Element;

typedef struct Tree {
	Element data;
	struct Tree* left;
	struct Tree* right;
}Tree, * Tnode;

typedef Tnode QElement;

typedef struct Qnode {
	QElement member; // 存储队列中的数据
	Qnode* next;  // 指向下一个节点的指针
} *Queuelist; // 这里是 Qnode* 的定义

typedef struct {
	Queuelist head; // 头指针
	Queuelist rear; // 尾指针
} Queue;

void init_tree(Tnode& T)
{
	T = new Tree;
	T->data = '\0';
	T->left = nullptr;
	T->right = nullptr;
}

void destroy_tree(Tnode& T)
{
	if (T == nullptr)return;
	else {
		destroy_tree(T->left);
		destroy_tree(T->right);
		delete T;
		T = nullptr;
	}
}

void Pre_setTree(Tnode& T)//先序创建
{
	Element e;
	cin >> e;
	if (e == '#')
	{
		T = nullptr;
		return;
	}
	else
	{
		init_tree(T);
		T->data = e;
		Pre_setTree(T->left);
		Pre_setTree(T->right);
	}
}

void Pre_display(Tnode& T)//前序输出
{
	if (T != nullptr)
	{
		cout << T->data << " ";
		Pre_display(T->left);
		Pre_display(T->right);
	}
}

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

int count_queue(Queue q)
{
	Queuelist temp = q.head;
	int count = 0;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	//cout << "Count: " << count << endl;
	return count;
}

void Push_queue(Queue& q, QElement d)//入队
{
	Queuelist Newmodels = new Qnode;
	Newmodels->member = d;
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
		data = q.head->member;
		q.head = q.head->next;
		if (q.head == nullptr)
		{
			q.rear = nullptr;
		}
		delete temp;
	}
}

void Breadth_display(Tnode T)//广度优先历遍
{
	Queue Q;
	init_queue(Q);
	Push_queue(Q, T);
	while (!IsEmpty_queue(Q))
	{
		QElement temp;
		Pop_queue(Q, temp);
		cout << temp->data << " ";

		if (temp->left != nullptr) {
			Push_queue(Q, temp->left);
		}

		if (temp->right != nullptr) {
			Push_queue(Q, temp->right);
		}
	}
	cout << endl;
}

int Breadth_max(Tnode T) // 求最大宽度
{
	if (T == nullptr) {
		cout << "Max_width: 0" << endl;
		return 0;
	}

	int max_width = 1;
	Queue Q;
	init_queue(Q);
	Push_queue(Q, T);  // 将根节点入队

	while (!IsEmpty_queue(Q)) {
		int level_width = 0;  // 当前层的宽度
		int level_nodes = count_queue(Q);  // 当前层的节点数量（即队列的大小）

		for (int i = 0; i < level_nodes; i++) {
			QElement temp;
			Pop_queue(Q, temp);  // 出队一个节点

			// 当前层节点数加一
			level_width++;

			// 将当前节点的左右子节点入队
			if (temp->left != nullptr) {
				Push_queue(Q, temp->left);
			}

			if (temp->right != nullptr) {
				Push_queue(Q, temp->right);
			}
		}

		// 更新最大宽度
		max_width = max(max_width, level_width);
	}

	return max_width;
}
