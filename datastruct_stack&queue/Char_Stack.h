#pragma once
#include<iostream>
using namespace std;

#define Stack_Max 20
typedef char Stack_Element;

typedef struct Stack
{
	Stack_Element* data;
	int top;
	int size;
}Stack;

void C_Init_stack(Stack& s)//初始化
{
	s.top = -1;
	s.data = new Stack_Element[Stack_Max];
	s.size = Stack_Max;
}

void C_Destroy_Stack(Stack& s)//销毁
{
	delete[] s.data;
	s.data = nullptr;
	s.top = -1;
	s.size = 0;
}

void C_Display_stack(Stack s)
{
	cout << "Stack: ";
	for (int i = 0; i <= s.top; i++)
	{
		cout << s.data[i] << " ";
	}
	cout << "count: " << s.top + 1 << endl;
	cout << endl;
}

void C_Expand_stack(Stack& s)//扩展栈
{
	int C_expandedDatasize = s.size * 2;
	Stack_Element  * C_expandedData = new Stack_Element[C_expandedDatasize];
	for (int i = 0; i <= s.top; i++)
	{
		C_expandedData[i] = s.data[i];
	}
	delete[] s.data;
	s.data = C_expandedData;
	s.size = C_expandedDatasize;
}

int C_IsEmpty_stack(Stack s)//判空
{
	if (s.top == -1){return 1;}
	else {return 0;}
}

void C_Push_stack(Stack& s, char d)//入栈
{
	cout << "C_Pushing: " << d << endl; // 输出入栈的字符
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

char C_Pop_stack(Stack& s)//出栈
{
	if (s.top == -1)
	{
		cout << "Stack is empty!!!" << endl;
	}
	else {
		char temp=s.data[s.top];
		s.top--;
		//C_Display_stack(s);
		//cout << "Pop successfully!!" << endl<<endl;
		return temp;
	}
	
}

char C_Peek_stack(Stack& s)//查看栈顶元素
{
	if(!C_IsEmpty_stack(s))
	{ 
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}
	
}

void C_Set_stack(Stack& s) // 设置一个栈
{
	C_Init_stack(s);
	char data; // 保持为 char 类型
	cout << "Please enter the data. Input '#' to quit." << endl;
	cin >> data;
	while (data != '#') // 使用 '#' 作为退出条件
	{
		C_Push_stack(s, data);
		cin >> data; // 再次读取输入
	}
	C_Display_stack(s);
}