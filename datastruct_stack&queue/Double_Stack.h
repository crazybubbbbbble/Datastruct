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

void D_Init_stack(D_Stack& s)//��ʼ��
{
	s.top = -1;
	s.data = new D_Element[D_Stack_Max];
	s.size = D_Stack_Max;
}

void D_Destroy_Stack(D_Stack& s)//����
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

void D_Expand_stack(D_Stack& s)//��չջ
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

int D_IsEmpty_stack(D_Stack s)//�п�
{
	if (s.top == -1) { return 1; }
	else { return 0; }
}

void D_Push_stack(D_Stack& s, D_Element d)//��ջ
{
	cout << "Pushing: " << d << endl; // �����ջ���ַ�
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

double D_Pop_stack(D_Stack& s)//��ջ
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

double D_Peek_stack(D_Stack& s)//�鿴ջ��Ԫ��
{
	if (!D_IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void D_Set_stack(D_Stack& s) // ����һ��ջ
{
	D_Init_stack(s);
	double data; // ����Ϊ char ����
	cout << "Please enter the data. Input '9999' to quit." << endl;
	cin >> data;
	while (data != '9999') // ʹ�� '#' ��Ϊ�˳�����
	{
		D_Push_stack(s, data);
		cin >> data; // �ٴζ�ȡ����
	}
	D_Display_stack(s);
}