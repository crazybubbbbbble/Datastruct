#pragma once
#include <chrono>  
#include <cstdlib> // 用于 rand() 和 srand()
#include <ctime>   // 用于 time()
#include<iostream>
#include <algorithm>
using namespace chrono;
using namespace std;

typedef int Element;
#define MAX 10000

typedef struct TreeNode {//左子树小于根，根小于右子树
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

Tnode searchMin(Tnode T)//找最小值
{
	if (T == nullptr)
		return T;
	if (T->left == nullptr)
		return T;
	else
		return searchMin(T->left);//一直往左孩子找，直到没有左孩子的结点  
}

Tnode searchMax(Tnode T)//找最大值
{
	if (T == nullptr)
		return T;
	if (T->right == nullptr)
		return T;
	else
		return searchMin(T->right);
}

Tnode searchData(Tnode T,int data)//递归版查找
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

Tnode searchData_UnRecursive(Tnode T, int data) {// 非递归查找
	Tnode temp = T;
	while (temp) {
		if (temp->data == data) {
			return temp; // 找到目标节点
		}
		temp = (temp->data < data) ? temp->right : temp->left;
	}
	return nullptr; // 未找到目标节点
}

// 插入节点
void Insert(Tnode& T, int data) {
	Tnode p = new TreeNode(data); // 创建新节点

	// 如果树为空，直接作为根节点
	if (T == nullptr) {
		T = p;
		return;
	}

	Tnode root = T;
	Tnode parent = nullptr; // 用于保存父节点

	// 查找插入位置
	while (root) {
		parent = root;
		if (root->data == data) {
			cout << "Data is already in the tree." << endl;
			delete p; // 释放新节点
			return;
		}
		root = (root->data < data) ? root->right : root->left;
	}

	// 插入新节点
	if (data < parent->data) {
		parent->left = p;
	}
	else {
		parent->right = p;
	}
}

void Mid_display(Tnode& T)//中序输出
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

	if (data < T->data)// 查找要删除的节点
		Delete(T->left, data);
	else if (data > T->data)
		Delete(T->right,data);
	else// 找到要删除的节点
	{
		if (T->left == nullptr && T->right == nullptr) // 情况1：叶子节点
		{
			delete T;
			T = nullptr;
		}
		else if (T->left == nullptr)// 情况2：只有右子节点,删除该节点，并将其子节点连接到其父节点。
		{
			Tnode temp = T;
			T = T->right;
			delete temp;

		}
		else if (T->right == nullptr) // 情况2：只有左子节点,删除该节点，并将其子节点连接到其父节点。
		{
			Tnode temp = T;
			T = T->left;
			delete temp;
		}
		else// 情况3：有两个子节点,找到左子树中的最大节点或右子树中的最小节点，替换当前节点的值
		{
			Tnode minNode = searchMin(T->right);
			T->data = minNode->data;
			Delete(T->right, minNode->data);// 删除后继节点
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

//ASL成功=累加（实的内部节点*深度）/实的节点数
//ASL失败=累加（空的叶子节点*深度）/空的节点数

//10 18 3 8 12 2 7