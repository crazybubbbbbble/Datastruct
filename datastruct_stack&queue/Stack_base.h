#pragma once
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

void Init_stack(Stack& s)//��ʼ��
{
	s.top = -1;
	s.data = new Stack_Element[Stack_Max];
	s.size = Stack_Max;
}

void Destroy_Stack(Stack& s)//����
{
	delete[] s.data;
	s.data = nullptr;
	s.top = -1;
	s.size = 0;
}

void Display_stack(Stack s)
{
	cout << "Stack: ";
	for (int i = 0; i <= s.top; i++)
	{
		cout << s.data[i] << " ";
	}
	cout << "count: " << s.top + 1 << endl;
	cout << endl;
}

void Expand_stack(Stack& s)//��չջ
{
	int C_expandedDatasize = s.size * 2;
	Stack_Element* C_expandedData = new Stack_Element[C_expandedDatasize];
	for (int i = 0; i <= s.top; i++)
	{
		C_expandedData[i] = s.data[i];
	}
	delete[] s.data;
	s.data = C_expandedData;
	s.size = C_expandedDatasize;
}

int IsEmpty_stack(Stack s)//�п�
{
	if (s.top == -1) { return 1; }
	else { return 0; }
}

void Push_stack(Stack& s, char d)//��ջ
{
	cout << "C_Pushing: " << d << endl; // �����ջ���ַ�
	if (s.top >= s.size - 1)
	{
		cout << "Stack is full!!!" << endl;
	}
	else
	{
		s.top++;
		s.data[s.top] = d; // ���Ԫ��
	}
}

char Pop_stack(Stack& s)//��ջ
{
	if (s.top == -1)
	{
		cout << "Stack is empty!!!" << endl;
	}
	else {
		char temp = s.data[s.top];
		s.top--;
		//C_Display_stack(s);
		//cout << "Pop successfully!!" << endl<<endl;
		return temp;
	}

}

char Peek_stack(Stack& s)//�鿴ջ��Ԫ��
{
	if (!IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void Set_stack(Stack& s) // ����һ��ջ
{
	Init_stack(s);
	char data; // ����Ϊ char ����
	cout << "Please enter the data. Input '#' to quit." << endl;
	cin >> data;
	while (data != '#') // ʹ�� '#' ��Ϊ�˳�����
	{
		Push_stack(s, data);
		cin >> data; // �ٴζ�ȡ����
	}
	Display_stack(s);
}