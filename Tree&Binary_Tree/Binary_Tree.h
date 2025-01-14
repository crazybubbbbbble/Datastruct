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
}Tree,*Tnode;

void Init_tree(Tnode& T)
{
	T = new Tree;
	T->data = '\0';  
	T->left = nullptr;
	T->right = nullptr;
}

void Destroy_tree(Tnode& T)
{
	if (T == nullptr)return;
	else {
		Destroy_tree(T->left);
		Destroy_tree(T->right);
		delete T;
		T =nullptr;
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

void Mid_display(Tnode& T)//中序输出
{
	if (T != nullptr)
	{
		Mid_display(T->left);
		cout << T->data << " ";
		Mid_display(T->right);
	}
}

void Post_display(Tnode& T)//后序输出
{
	if (T != nullptr)
	{
		Post_display(T->left);
		Post_display(T->right);
		cout << T->data << " ";
	}
}

void Pre_setTree(Tnode& T)//先序创建
{
	Element e;
	cin >> e;
	if (e == '#')
	{
		T=nullptr;
		return;
	}
	else
	{
		T=new Tree;
		T->data = e;
		Pre_setTree(T->left);
		Pre_setTree(T->right);
	}
}

void Mid_setTree(Tnode& T)//中序创建
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
		T=new Tree;
		Mid_setTree(T->left);
		T->data = e;
		Mid_setTree(T->right);
	}
}

void Post_setTree(Tnode& T)//后序创建
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
		T=new Tree;
		Post_setTree(T->left);
		Post_setTree(T->right);
		T->data = e;
	}
}

int Count_Point(Tnode T)//先序计算总节点
{
	static int count = 0;
	if (T != nullptr)
	{
		count++;
		Count_Point(T->left);
		Count_Point(T->right);
	}
	return count;
}

int Count_Leaves(Tnode T)//先序计算叶子节点
{
	static int Lcount = 0;
	if (T != nullptr)
	{
		Count_Leaves(T->left);
		Count_Leaves(T->right);
		if (T->left == nullptr && T->right == nullptr)
		{
			Lcount++;
		}
	}
	return Lcount;
}

int Height_tree(Tnode T)//计算树的高度
{
	if (T == nullptr) {
		return 0;
	}
	int left_height = Height_tree(T->left);
	int right_height = Height_tree(T->right);
	return max(left_height, right_height) + 1;
}

