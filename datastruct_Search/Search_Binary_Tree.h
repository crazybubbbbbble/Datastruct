#pragma once
#include <chrono>  
#include <cstdlib> // ���� rand() �� srand()
#include <ctime>   // ���� time()
#include<iostream>
#include <algorithm>
using namespace chrono;
using namespace std;

typedef int Element;
#define MAX 10000

typedef struct TreeNode {//������С�ڸ�����С��������
	Element data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
}Tree, * Tnode;

void Init_tree(Tnode& T)
{
	T = nullptr;
	T->data = '\0';
	T->left = nullptr;
	T->right = nullptr;
}

Tnode searchMin(Tnode T)//����Сֵ
{
	if (T == nullptr)
		return T;
	if (T->left == nullptr)
		return T;
	else
		return searchMin(T->left);//һֱ�������ң�ֱ��û�����ӵĽ��  
}

Tnode searchMax(Tnode T)//�����ֵ
{
	if (T == nullptr)
		return T;
	if (T->right == nullptr)
		return T;
	else
		return searchMin(T->right);
}

Tnode searchData(Tnode T,int data)//�ݹ�����
{
	if (T == nullptr)
		return T;
	if (data < T->data)
		return searchData(T->left, data);
	else if (data > T->data)
		return searchData(T->right, data);
	else
		return T;
}

Tnode searchData_UnRecursive(Tnode T, int data) {// �ǵݹ����
	Tnode temp = T;
	while (temp) {
		if (temp->data == data) {
			return temp; // �ҵ�Ŀ��ڵ�
		}
		temp = (temp->data < data) ? temp->right : temp->left;
	}
	return nullptr; // δ�ҵ�Ŀ��ڵ�
}

// ����ڵ�
void Insert(Tnode& T, int data) {
	Tnode p = new TreeNode(data); // �����½ڵ�

	// �����Ϊ�գ�ֱ����Ϊ���ڵ�
	if (T == nullptr) {
		T = p;
		return;
	}

	Tnode root = T;
	Tnode parent = nullptr; // ���ڱ��游�ڵ�

	// ���Ҳ���λ��
	while (root) {
		parent = root;
		if (root->data == data) {
			cout << "Data is already in the tree." << endl;
			delete p; // �ͷ��½ڵ�
			return;
		}
		root = (root->data < data) ? root->right : root->left;
	}

	// �����½ڵ�
	if (data < parent->data) {
		parent->left = p;
	}
	else {
		parent->right = p;
	}
}

void Mid_display(Tnode& T)//�������
{
	if (T != nullptr)
	{
		Mid_display(T->left);
		cout << T->data << " ";
		Mid_display(T->right);
	}
}

void Delete(Tnode& T, int data)
{
	if (T == nullptr)
	{
		cout << "Data not found in the tree." << endl;
		return;
	}

	if (data < T->data)// ����Ҫɾ���Ľڵ�
		Delete(T->left, data);
	else if (data > T->data)
		Delete(T->right,data);
	else// �ҵ�Ҫɾ���Ľڵ�
	{
		if (T->left == nullptr && T->right == nullptr) // ���1��Ҷ�ӽڵ�
		{
			delete T;
			T = nullptr;
		}
		else if (T->left == nullptr)// ���2��ֻ�����ӽڵ�,ɾ���ýڵ㣬�������ӽڵ����ӵ��丸�ڵ㡣
		{
			Tnode temp = T;
			T = T->right;
			delete temp;

		}
		else if (T->right == nullptr) // ���2��ֻ�����ӽڵ�,ɾ���ýڵ㣬�������ӽڵ����ӵ��丸�ڵ㡣
		{
			Tnode temp = T;
			T = T->left;
			delete temp;
		}
		else// ���3���������ӽڵ�,�ҵ��������е����ڵ���������е���С�ڵ㣬�滻��ǰ�ڵ��ֵ
		{
			Tnode minNode = searchMin(T->right);
			T->data = minNode->data;
			Delete(T->right, minNode->data);// ɾ����̽ڵ�
		}
	}
}

void create(Tnode& T) 
{
	int n;
	cout << "Enter the number of elements: ";
	cin >> n;

	cout << "Enter the data: " << endl;
	for (int i = 0; i < n; i++) {
		int data;
		cin >> data;
		Insert(T, data);
	}
}

//ASL�ɹ�=�ۼӣ�ʵ���ڲ��ڵ�*��ȣ�/ʵ�Ľڵ���
//ASLʧ��=�ۼӣ��յ�Ҷ�ӽڵ�*��ȣ�/�յĽڵ���

//10 18 3 8 12 2 7