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
	QElement member; // �洢�����е�����
	Qnode* next;  // ָ����һ���ڵ��ָ��
} *Queuelist; // ������ Qnode* �Ķ���

typedef struct {
	Queuelist head; // ͷָ��
	Queuelist rear; // βָ��
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

void Pre_setTree(Tnode& T)//���򴴽�
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

void Pre_display(Tnode& T)//ǰ�����
{
	if (T != nullptr)
	{
		cout << T->data << " ";
		Pre_display(T->left);
		Pre_display(T->right);
	}
}

void init_queue(Queue& q)//��ʼ��
{
	q.head = nullptr;
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//�п�
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

void Push_queue(Queue& q, QElement d)//���
{
	Queuelist Newmodels = new Qnode;
	Newmodels->member = d;
	Newmodels->next = nullptr;

	if (IsEmpty_queue(q))//�������Ϊ��
	{
		q.head = Newmodels;
		q.rear = Newmodels;
	}
	else//��Ϊ�����ڶ�β����
	{
		q.rear->next = Newmodels;
		q.rear = Newmodels;
	}
}

void Pop_queue(Queue& q, QElement& data)//����
{
	if (IsEmpty_queue(q))//�п�
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

void Breadth_display(Tnode T)//�����������
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

int Breadth_max(Tnode T) // �������
{
	if (T == nullptr) {
		cout << "Max_width: 0" << endl;
		return 0;
	}

	int max_width = 1;
	Queue Q;
	init_queue(Q);
	Push_queue(Q, T);  // �����ڵ����

	while (!IsEmpty_queue(Q)) {
		int level_width = 0;  // ��ǰ��Ŀ��
		int level_nodes = count_queue(Q);  // ��ǰ��Ľڵ������������еĴ�С��

		for (int i = 0; i < level_nodes; i++) {
			QElement temp;
			Pop_queue(Q, temp);  // ����һ���ڵ�

			// ��ǰ��ڵ�����һ
			level_width++;

			// ����ǰ�ڵ�������ӽڵ����
			if (temp->left != nullptr) {
				Push_queue(Q, temp->left);
			}

			if (temp->right != nullptr) {
				Push_queue(Q, temp->right);
			}
		}

		// ���������
		max_width = max(max_width, level_width);
	}

	return max_width;
}
