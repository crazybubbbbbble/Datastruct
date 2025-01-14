#pragma once
#include<iostream>
using namespace std;

typedef int QElement;

typedef struct Qnode {
	QElement data; // �洢�����е�����
	Qnode* next;  // ָ����һ���ڵ��ָ��
} *Queuelist; // ������ Qnode* �Ķ���

typedef struct {
	Queuelist head; // ͷָ��
	Queuelist rear; // βָ��
} Queue;

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

void Push_queue(Queue& q, QElement d)//���
{
	Queuelist Newmodels = new Qnode;
	Newmodels->data = d;
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
		data = q.head->data;
		q.head = q.head->next;
		if (q.head == nullptr)
		{
			q.rear = nullptr;
		}
		delete temp;
	}
}

void set_queue(Queue& q)//����һ������
{
	init_queue(q); // ��ʼ������
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