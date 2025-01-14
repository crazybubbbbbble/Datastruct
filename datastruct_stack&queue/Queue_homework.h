#pragma once
#include<iostream>
using namespace std;

typedef int QElement;

typedef struct Qnode {
	QElement data; 
	Qnode* next;  
} *Queuelist; 

typedef struct {
	Queuelist rear; // βָ��
} Queue;

void init_queue(Queue& q)//��ʼ��
{
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//�п�
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
	if (IsEmpty_queue(q)) {  // �������Ϊ�գ�ֱ�ӷ���
		cout << "Queue is empty." << endl;
		return;
	}

	Queuelist temp = q.rear->next;  // �Ӷ�ͷ��ʼ����
	cout << "Queue: ";
	do {
		cout << temp->data << " ";  // ��ӡ��ǰ��������
		temp = temp->next;  // �ƶ�����һ�����
	} while (temp != q.rear->next);  // ѭ��ֱ���ص���ͷ
	cout << endl;

	count_queue(q);  // ��ӡ���е�Ԫ������
	cout << endl;
}

void Push_queue(Queue& q, QElement d) {
	Queuelist Newmodels = new Qnode;  // �����½ڵ�
	Newmodels->data = d;  // ��������
	Newmodels->next = nullptr;  // ��ʼ���½ڵ�� next ָ��

	if (IsEmpty_queue(q)) {  // �������Ϊ��
		q.rear = Newmodels;  // ���½ڵ���Ϊ��β
		Newmodels->next = Newmodels;  // ��βָ�������γ�ѭ��
	}
	else {  // ���в�Ϊ��
		Newmodels->next = q.rear->next;  // �½ڵ�ָ���ͷ
		q.rear->next = Newmodels;  // ��ǰ��βָ���½ڵ�
		q.rear = Newmodels;  // ���¶�β
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
		Queuelist temp = q.rear->next;
		data = temp->data;
		if (q.rear->next == q.rear) {  // ֻ��һ��Ԫ��
			delete temp;
			q.rear = nullptr;  // ����Ϊ��
		}
		else {
			q.rear->next = temp->next;  // ���¶�ͷ
			delete temp;
		}
		cout << "Pop successfully!!" << endl;
		display_queue(q);
	}
}

// ���ò���ʼ������
void set_queue(Queue& q) {
	init_queue(q);  // ��ʼ������
	QElement data;
	cout << "Please input queue data. Enter 9999 to quit." << endl;
	cin >> data;
	while (data != 9999) {
		Push_queue(q, data);  // ���
		cin >> data;
	}
	display_queue(q);  // ��ʾ����
}