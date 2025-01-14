#include"Char_Stack.h"
#include"Double_Stack.h"
//#include"Queue_base.h"
#include"Queue_homework.h"


int flag = 0;

double caculate(double x, double y, char m)
{
	if (m == '+')return x + y;
	if (m == '-')return y - x;
	if (m == '*')return x * y;
	if (m == '/') {
		if (y == 0)
		{
			cout << "Error!!" << endl;
		}
		else {
			return (y / x);
		}
	}
}

char relationship(char a, char b)
{
	if (b == '+' || b == '-') {
		if (a == '(' || a == '#')
			return '<';
		else
			return '>';
	}
	else if (b == '*' || b == '/') {
		if (a == '*' || a == '/' || a == ')')
			return '>';
		else
			return '<';
	}
	else if (b == '(')
		return '<';
	else if (b == ')') {
		if (a != '(')
			return '>';
		else
			return '=';
	}
	else if (b == '#') {
		if (a != '#')
			return '>';
		else
			return '=';
	}
}

int datatype(char x)
{
	char num[20] = { '1','2','3','4','5','6','7','8','9','0' };
	char cacu[10] = { '+','-','*','/','(',')','#' };
	for (int i = 0; i < 20; i++)
	{
		if (x == num[i])
			return 1;
	}
	for (int i = 0; i < 10; i++)
	{
		if (x == num[i])
			return 2;
	}
	return 0;
}

double operate()
{
	Stack OPTR;//ÔËËã·ûÕ»
	D_Stack OPND;//²Ù×÷ÊýÕ»
	C_Init_stack(OPTR);
	D_Init_stack(OPND);
	C_Push_stack(OPTR, '#');
	char x, y;
	double a, b;
	cout << "Please input the expression." << endl;
	x = getchar();
	while (x != '#'||C_Peek_stack(OPTR)!='#')
	{
		if (x == '\n')
		{
			break;
		}
		else if (datatype(x) == 1)
		{
			x = x - '0';
			if (flag == 1)
			{
				double temp = D_Pop_stack(OPND);
				temp = temp * 10 + x;
				D_Push_stack(OPND, temp);
			}
			else
			{
				D_Push_stack(OPND, x);
				flag = 1;
			}
				x = getchar();
		}
		else 
		{
			flag = 0;
			switch (relationship(C_Peek_stack(OPTR), x))
			{
			case '<':
				C_Push_stack(OPTR, x);
				x = getchar();
				break;
			case '>':
				a = D_Pop_stack(OPND);
				b = D_Pop_stack(OPND);
				y = C_Pop_stack(OPTR);
				D_Push_stack(OPND, caculate(a, b, y));
				break;
			case '=':
				C_Pop_stack(OPTR);
				x = getchar();
				break;
			}

		}
	}
	C_Display_stack(OPTR);
	D_Display_stack(OPND);
	return D_Peek_stack(OPND);
}

int main()
{
	//double result;
	//result = operate();
	//cout << "Result : " << result << endl;
	Queue Q;
	int data;
	set_queue(Q);
	Push_queue(Q, 12346);
	display_queue(Q);
	Push_queue(Q, 10086);
	display_queue(Q);
	Pop_queue(Q, data);

}