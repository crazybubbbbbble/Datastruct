#pragma once
#include<iostream>
#include <cstdlib> // ���� rand() �� srand()
using namespace std;
#define Sqlist_maxsize 10000000
typedef struct Sqlist {
	int* data;
	int length;
};

void Init_sqlist(Sqlist* L)//˳���
{
	L->data = new int[Sqlist_maxsize];
	L->length = 0;
}

void display_Sqlist(Sqlist* L)//չʾ
{
	cout << "Sqlist : ";
	for (int i = 0; i < L->length; i++)
	{
		cout << L->data[i] << " ";
	}
	cout << endl << "Count : " << L->length << endl;
}

void set_Sqlist(Sqlist* L, int n)//��ʼ������Ϊn��˳���
{
	Init_sqlist(L);
	for (int i = 0; i < n; i++)
	{
		L->data[i]=i+10123;
		L->length++;
	}
	//display_Sqlist(L);
}

int Insert_Sqlist(Sqlist* L, int position, int newdata) {
	cout << "Insert " << newdata << " into the position " << position << endl;
	if (position < 1 || position > L->length + 1) {
		cout << "Error position!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize) {
		cout << "Full list!!" << endl;
		return -1;
	}
	for (int j = L->length; j > position - 1; j--) { // �޸�ѭ���߽�
		L->data[j] = L->data[j - 1];
	}
	L->data[position - 1] = newdata;
	L->length++;
	cout << "Correct inserting!!!" << endl;
	display_Sqlist(L);
	return 1;
}

int Delete_Sqlist(Sqlist* L, int position) {
	cout << "Delete the data in the position " << position << endl;
	if (position < 1 || position > L->length) {
		cout << "Error position!!" << endl;
		return 0;
	}
	for (int j = position; j < L->length; j++) { // �޸�ѭ���߽�
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	cout << "Correct deleting" << endl;
	display_Sqlist(L);
	return 1;
}

int Search_Sqlist(Sqlist* L, int position)//����
{
	if (position<1 || position>L->length + 1)//������λ��
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//����
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	cout << "The data is: " << L->data[position - 1] << endl;//����
}

int Change_Sqlist(Sqlist* L, int position, int newdata)//��������
{
	if (position<1 || position>L->length + 1)//������λ��
	{
		cout << "Error pisition!!" << endl;
		return 0;
	}
	if (L->length == Sqlist_maxsize)//����
	{
		cout << "Full list!!" << endl;
		return -1;
	}
	L->data[position - 1] = newdata;//����
	cout << "Correct changing" << endl;
	display_Sqlist(L);
}

void Free_sqlist(Sqlist* L) {
	delete[] L->data; // �ͷŶ�̬���������
	L->data = nullptr; // ��ָ������Ϊnullptr�Ա�������ָ��
}
