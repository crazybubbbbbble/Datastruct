#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef char Tree_Element;

typedef struct Tree {
	Tree_Element data;
	struct Tree* left;
	struct Tree* right;
}Tree, * Tnode;

#define Stack_Max 20
typedef Tnode Stack_Element;

typedef struct Stack
{
	Stack_Element* data;
	int top;
	int size;
}Stack;

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
		T = nullptr;
	}
}

void Pre_setTree(Tnode& T)//先序创建
{
	Tree_Element e;
	cin >> e;
	if (e == '#')
	{
		T = nullptr;
		return;
	}
	else
	{
		Init_tree(T);
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

void Init_stack(Stack& s)//初始化
{
	s.top = -1;
	s.data = new Stack_Element[Stack_Max];
	s.size = Stack_Max;
}

void Destroy_Stack(Stack& s)//销毁
{
	delete[] s.data;
	s.data = nullptr;
	s.top = -1;
	s.size = 0;
}

int IsEmpty_stack(Stack s)//判空
{
	if (s.top == -1) { return 1; }
	else { return 0; }
}

void Push_stack(Stack& s, Tnode d)//入栈
{
	//cout << "C_Pushing: " << d << endl; // 输出入栈的字符
	if (s.top >= s.size - 1)
	{
		cout << "Stack is full!!!" << endl;
	}
	else
	{
		s.top++;
		s.data[s.top] = d; // 添加元素
	}
}

Tnode Pop_stack(Stack& s)//出栈
{
	if (s.top == -1)
	{
		cout << "Stack is empty!!!" << endl;
	}
	else {
		Tnode temp = s.data[s.top];
		s.top--;
		//C_Display_stack(s);
		//cout << "Pop successfully!!" << endl<<endl;
		return temp;
	}

}

Tnode Peek_stack(Stack& s)//查看栈顶元素
{
	if (!IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void Depth_display(Tnode& T)//深度优先历遍
{
	Stack S;
	Init_stack(S);
	Push_stack(S, T);
	while (!IsEmpty_stack(S))
	{
		Stack_Element temp=Pop_stack(S);
		cout << temp->data<<" ";

		if (temp->right != nullptr) {
			Push_stack(S, temp->right);
		}

		if (temp->left != nullptr) {
			Push_stack(S, temp->left);
		}
	}
	cout << endl;
}

void Post_display1(Tnode& T)//后序输出
{
	if (T != nullptr)
	{
		Post_display1(T->left);
		Post_display1(T->right);
		cout << T->data << " ";
	}
}

void Post_display2(Tnode& T)//后序输出非递归
{
	Stack S1,S2;
	Init_stack(S1);
	Init_stack(S2);
	Push_stack(S1, T);
	while (!IsEmpty_stack(S1))
	{
		Stack_Element temp = Peek_stack(S1);
		Pop_stack(S1);
		Push_stack(S2, temp);
		if (temp->left)Push_stack(S1, temp->left);
		if (temp->right)Push_stack(S1, temp->right);
	}
	while (!IsEmpty_stack(S2))
	{
		cout << Peek_stack(S2)->data << " ";
		Pop_stack(S2);
	}
}