#pragma once
#pragma once
#include<iostream>
using namespace std;

#define D_Stack_Max 20
typedef double D_Element;

typedef struct D_stack
{
	D_Element* data;
	int top;
	int size;
}D_Stack;

void D_Init_stack(D_Stack& s)//初始化
{
	s.top = -1;
	s.data = new D_Element[D_Stack_Max];
	s.size = D_Stack_Max;
}

void D_Destroy_Stack(D_Stack& s)//销毁
{
	delete[] s.data;
	s.data = nullptr;
	s.top = -1;
	s.size = 0;
}

void D_Display_stack(D_Stack s)
{
	cout << "Stack: ";
	for (int i = 0; i <= s.top; i++)
	{
		cout << s.data[i] << " ";
	}
	cout << "count: " << s.top + 1 << endl;
	cout << endl;
}

void D_Expand_stack(D_Stack& s)//扩展栈
{
	int expandedDatasize = s.size * 2;
	D_Element* expandedData = new D_Element[expandedDatasize];
	for (int i = 0; i <= s.top; i++)
	{
		expandedData[i] = s.data[i];
	}
	delete[] s.data;
	s.data = expandedData;
	s.size = expandedDatasize;
}

int D_IsEmpty_stack(D_Stack s)//判空
{
	if (s.top == -1) { return 1; }
	else { return 0; }
}

void D_Push_stack(D_Stack& s, D_Element d)//入栈
{
	cout << "Pushing: " << d << endl; // 输出入栈的字符
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

double D_Pop_stack(D_Stack& s)//出栈
{
	if (s.top == -1)
	{
		cout << "Stack is empty!!!" << endl;
	}
	else {
		double temp = s.data[s.top];
		s.top--;
		//D_Display_stack(s);
		//cout << "Pop successfully!!" << endl << endl;
		return temp;
	}

}

double D_Peek_stack(D_Stack& s)//查看栈顶元素
{
	if (!D_IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void D_Set_stack(D_Stack& s) // 设置一个栈
{
	D_Init_stack(s);
	double data; // 保持为 char 类型
	cout << "Please enter the data. Input '9999' to quit." << endl;
	cin >> data;
	while (data != '9999') // 使用 '#' 作为退出条件
	{
		D_Push_stack(s, data);
		cin >> data; // 再次读取输入
	}
	D_Display_stack(s);
}