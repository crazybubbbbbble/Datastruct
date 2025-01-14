#pragma once
#include<iostream>
#include <iomanip>
#include<Windows.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef string List_Vertex_Element;//������Ϣ
typedef int List_Edge_Element;//��Ȩֵ
#define  MAX 50
#define Stack_Max 50
typedef int Stack_Element;
typedef int QElement;
bool visited[MAX];
typedef struct Stack
{
	Stack_Element* data;
	int top;
	int size;
}Stack;

typedef struct Qnode {
	QElement data; // �洢�����е�����
	Qnode* next;  // ָ����һ���ڵ��ָ��
} *Queuelist; // ������ Qnode* �Ķ���

typedef struct {
	Queuelist head; // ͷָ��
	Queuelist rear; // βָ��
} Queue;

typedef struct Edge_node {//��
	List_Vertex_Element front;
	List_Vertex_Element tail;
	int index;//��ָ����±�
	List_Edge_Element value;//Ȩֵ
	Edge_node* next;//ָ����һ����
}*Enode;

typedef struct Vertex_node {//����
	int index;//�±�
	List_Vertex_Element info;//������Ϣ
	Enode first_egde;//�����һ����
}Vnode;

typedef struct Edge_List {//�߱�
	List_Vertex_Element front;
	List_Vertex_Element tail;
	List_Edge_Element value;//Ȩֵ
}*List_Edge;

typedef struct List {
	Vnode v[MAX];//�����
	int v_num, e_num;//����ͱߵ�ʵ������
	int Is_directed = 0;//�Ƿ�����
	int Is_mesh = 0;//�Ƿ��Ȩ
}List_Graph;

// ���鼯�ṹ
struct UnionFind {
	std::vector<int> parent, rank;

	UnionFind(int n) : parent(n), rank(n, 0) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int x) {
		if (parent[x] != x) parent[x] = find(parent[x]); // ·��ѹ��
		return parent[x];
	}

	void unite(int x, int y) {
		int rootX = find(x), rootY = find(y);
		if (rootX != rootY) {
			if (rank[rootX] < rank[rootY])
				parent[rootX] = rootY;
			else if (rank[rootX] > rank[rootY])
				parent[rootY] = rootX;
			else {
				parent[rootY] = rootX;
				rank[rootX]++;
			}
		}
	}
};

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

int IsEmpty_stack(Stack s)//�п�
{
	if (s.top == -1) { return 1; }
	else { return 0; }
}

void Push_stack(Stack& s, Stack_Element d)//��ջ
{
	//cout << "C_Pushing: " << d << endl; // �����ջ���ַ�
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

Stack_Element Pop_stack(Stack& s)//��ջ
{
	if (s.top == -1)
	{
		cout << "Stack is empty!!!" << endl;
	}
	else {
		Stack_Element temp = s.data[s.top];
		s.top--;
		//C_Display_stack(s);
		//cout << "Pop successfully!!" << endl<<endl;
		return temp;
	}

}

Stack_Element Peek_stack(Stack& s)//�鿴ջ��Ԫ��
{
	if (!IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void init_queue(Queue& q)//��ʼ��
{
	q.head = nullptr;
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//�п�
{
	if (q.head == nullptr) { return 1; }
	else { return 0; }
}

void Push_queue(Queue& q, QElement d)//���
{
	Queuelist Newmodels = new Qnode;
	Newmodels->data = d;
	Newmodels->next = nullptr;

	if (IsEmpty_queue(q))//�������Ϊ��
	{
		q.head = Newmodels;
		q.rear = Newmodels;
	}
	else//��Ϊ�����ڶ�β����
	{
		q.rear->next = Newmodels;
		q.rear = Newmodels;
	}
}

void Pop_queue(Queue& q)//����
{
	if (IsEmpty_queue(q))//�п�
	{
		cout << "The queue is empty." << endl;
	}
	else
	{
		Queuelist temp = q.head;
		q.head = q.head->next;
		if (q.head == nullptr)
		{
			q.rear = nullptr;
		}
		delete temp;
	}
}

//������ͼ�ĺ���
int Locate_List_Vertex(List_Graph& G, List_Vertex_Element v)//��λ�������±�
{
	int i;
	for (i = 0; i < G.v_num; i++)
	{
		if (v == G.v[i].info)return i;
	}
	return -1;
}

void Create_List_Undirected_Graph(List_Graph& G)//��������ͼ
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		G.v[i].first_egde = nullptr;
		cin >> G.v[i].info;
	}
	cout << "Please enter the edges in the format: Vertex1 Vertex2.Enter (# #) to quit." << endl;
	for (int t = 0; t < G.e_num; t++)
	{
		
		List_Vertex_Element x1, x2;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//���ڵ�x1������x2 x1<-->x2

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//ͷ�巨���룬����ͼ��Ҫ��m,n�����߱��ж������ٱ�
		Enode temp1 = new Edge_node;
		temp1->index= n;//���ߵ���Ϣ������ڽӱ�m
		temp1->next = G.v[m].first_egde;
		if (G.v[m].first_egde == nullptr) {  // ���û�бߣ����ʼ�� first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}

		Enode temp2 = new Edge_node;
		temp2->index = m;//���ߵ���Ϣ������ڽӱ�n
		temp2->next = G.v[n].first_egde;
		if (G.v[n].first_egde == nullptr) { 
			G.v[n].first_egde = temp2;
		}
		else {
			temp2->next = G.v[n].first_egde;
			G.v[n].first_egde = temp2;
		}
	}
}

void Create_List_Undirected_Mesh(List_Graph& G)//����������
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		G.v[i].first_egde = nullptr;
		cin >> G.v[i].info;
	}
	cout << "Please enter the edges in the format: Vertex1 Vertex2.Enter (# #) to quit." << endl;
	for (int t = 0; t < G.e_num; t++)
	{

		List_Vertex_Element x1, x2;
		List_Edge_Element e;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;
		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//���ڵ�x1������x2 x1<-->x2

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//ͷ�巨���룬����ͼ��Ҫ��m,n�����߱��ж������ٱ�
		Enode temp1 = new Edge_node;
		temp1->index = n;//���ߵ���Ϣ������ڽӱ�m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		temp1->front = G.v[m].info;
		temp1->tail = G.v[n].info;
		if (G.v[m].first_egde == nullptr) {  // ���û�бߣ����ʼ�� first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}

		Enode temp2 = new Edge_node;
		temp2->index = m;//���ߵ���Ϣ������ڽӱ�n
		temp2->next = G.v[n].first_egde;
		temp2->value = e;
		temp2->front = G.v[n].info;
		temp2->tail = G.v[m].info;
		if (G.v[n].first_egde == nullptr) {
			G.v[n].first_egde = temp2;
		}
		else {
			temp2->next = G.v[n].first_egde;
			G.v[n].first_egde = temp2;
		}
	}
}

void Create_List_Directed_Graph(List_Graph& G)//��������ͼ
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		G.v[i].first_egde = nullptr;
		cin >> G.v[i].info;
	}
	cout << "Please enter the edges in the format: Vertex1 Vertex2.Enter (# #) to quit." << endl;
	for (int t = 0; t < G.e_num; t++)
	{

		List_Vertex_Element x1, x2;//����Ϊx1->x2
		List_Edge_Element e;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;

		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//���ڵ�x1������x2 x1<-->x2

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//ͷ�巨���룬����ͼֻ��Ҫ��m�߱��м����ٱ�
		Enode temp1 = new Edge_node;
		temp1->index = n;//���ߵ���Ϣ������ڽӱ�m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		if (G.v[m].first_egde == nullptr) {  // ���û�бߣ����ʼ�� first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}
	}
}

void Create_List_Directed_Mesh(List_Graph& G)//����������
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		G.v[i].first_egde = nullptr;
		cin >> G.v[i].info;
	}
	cout << "Please enter the edges in the format: Vertex1 Vertex2.Enter (# #) to quit." << endl;
	for (int t = 0; t < G.e_num; t++)
	{

		List_Vertex_Element x1, x2;
		List_Edge_Element e;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;

		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//���ڵ�x1������x2 x1<-->x2

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//ͷ�巨���룬����ͼ��Ҫ��m,n�����߱��ж������ٱ�
		Enode temp1 = new Edge_node;
		temp1->index = n;//���ߵ���Ϣ������ڽӱ�m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		if (G.v[m].first_egde == nullptr) {  // ���û�бߣ����ʼ�� first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}
	}
}

void Create_List_Graph(List_Graph& G)//�жϲ��Ҵ���ͼ
{
	cout << "Please enter the vertex number,the edge number,directed(0 False,1 True),mesh(0 False,1 True)." << endl;
	cin >> G.v_num >> G.e_num >> G.Is_directed >> G.Is_mesh;
	if (G.Is_directed == 0)
	{
		if (G.Is_mesh == 0)
		{
			cout << "Create undirected List_Graph......" << endl;
			Create_List_Undirected_Graph(G);
		}
		else
		{
			cout << "Create List undirected List_mesh......" << endl;
			Create_List_Undirected_Mesh(G);
		}
	}
	else
	{
		if (G.Is_mesh == 0)
		{
			cout << "Create List directed List_Graph......" << endl;
			Create_List_Directed_Graph(G);
		}
		else
		{
			cout << "Create List directed List_mesh......" << endl;
			Create_List_Directed_Mesh(G);
		}
	}
}

void Display_List(List_Graph& G)//���
{
	cout << "Creating Graph......" << endl;
	Sleep(1000);
	for (int i = 0; i < G.v_num; i++)
	{
		cout << "v" << i<<" ";
		Enode temp=G.v[i].first_egde;
		if(G.Is_directed==0)
		{
			if(G.Is_mesh==0)
			{
				while (temp != nullptr)
				{
					cout << "<����>";
					cout << setw(3) << G.v[temp->index].info << "  ";
					temp = temp->next;
				}
			}
			else
			{
				while (temp != nullptr)
				{
					cout << "<����>";
					cout <<" (" << setw(2) << temp->index << "," << setw(2) << temp->value << ") ";
					temp = temp->next;
				}
			}
		}
		else
		{
			if (G.Is_mesh == 0)
			{
				while (temp != nullptr)
				{
					cout << "����>";
					cout << setw(3) << temp->index << "  ";
					temp = temp->next;
				}
			}
			else
			{
				while (temp != nullptr)
				{
					cout << "����>";
					cout << " <" << setw(2) << temp->index << "," << setw(2) << temp->value << "> ";
					temp = temp->next;
				}
			}
		}
		cout << endl;
	}

}

int Out_Degree(List_Graph& G)//�������
{
	int count = 0;
	List_Vertex_Element V;
	cout << "Outdegree counting!!!Please enter the vertex you wana search." << endl;
	cin >> V;
	int i = Locate_List_Vertex(G,V);
	if (i == -1) 
	{
		cout << "Vertex not found!" << endl;
		return -1; 
	}

	Enode temp=G.v[i].first_egde;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	cout << V << " out degree: " << count << endl;
	return count;
}

int In_Degree(List_Graph& G)//�������
{
	int count = 0;
	List_Vertex_Element V;
	cout << "Indegree counting!!!Please enter the vertex you wana search." << endl;
	cin >> V;
	int i = Locate_List_Vertex(G, V);
	if (i == -1)
	{
		cout << "Vertex not found!" << endl;
		return -1;
	}
	for (int j = 0; j < G.e_num ; j++)
	{
		Enode temp = G.v[j].first_egde;
		while (temp != nullptr)
		{
			if (temp->index == i)
			{
				count++;
			}
			temp = temp->next;
		}
	}
	cout << V << " in degree: " << count << endl;
	return count;
}

void Visited(List_Graph& G, List_Vertex_Element V)
{
	int m = Locate_List_Vertex(G, V);
	visited[m] = 1;
	//cout << V << " ";
}

void Clear_visited(List_Graph& G)
{
	for (int i = 0; i < G.v_num; i++)
	{
		visited[i] = 0;
	}
}

void List_DFS(List_Graph& G, List_Vertex_Element V)//�������
{
	Stack S;
	Init_stack(S);
	int L = Locate_List_Vertex(G, V);
	if (L == -1) {
		cout << "Error: Invalid vertex input!" << endl;
		return;
	}
	Push_stack(S, L);
	visited[L] = 1;
	int value = 0;
	while (!IsEmpty_stack(S))
	{
		int temp = Peek_stack(S);
		Pop_stack(S);
		cout << G.v[temp].info << " ";
		for (Enode e=G.v[temp].first_egde;e!=nullptr;e=e->next)
		{
			int index = e->index;
			if (visited[index] == 0) {  // ���ڱ߲���δ����
				visited[index] = 1;  // ���Ϊ�ѷ���
				Push_stack(S, index);  // ���ö�����ջ
				value += e->value;
				//cout << "  index  " << index << "  ";
			}
		}
	}
	cout << value << " ";
}

void List_BFS(List_Graph& G, List_Vertex_Element V)//�������
{
	Queue Q;
	init_queue(Q);

	int L = Locate_List_Vertex(G, V);
	if (L == -1) {
		cout << "Error: Invalid vertex input!" << endl;
		return;
	}

	Visited(G, V);
	Push_queue(Q, L);
	while (!IsEmpty_queue(Q))
	{
		int temp = Q.head->data;
		Pop_queue(Q);
		cout << G.v[temp].info << " ";
		// �����뵱ǰ�������ڵ�����δ���ʵĶ���
		for (Enode e = G.v[temp].first_egde; e != nullptr; e = e->next) {
			int index = e->index;
			if (visited[index] == 0) {  // ���ڱ߲���δ����
				visited[index] = 1;  // ���Ϊ�ѷ���
				Push_queue(Q, index);  // ���ö�����ջ
				//cout << "  index  " << index << "  ";
			}
		}
	}
}

void List_DFS_Traverse(List_Graph& G)//����ͨͼ����ÿһ������
{
	cout << "DFS Traversing every vertex......" << endl;
	Clear_visited(G);
	for (int i = 0; i < G.v_num; i++)
	{
		if (!visited[i])
		{
			List_DFS(G, G.v[i].info);
			cout << endl;
			Clear_visited(G);
		}
	}
}

void List_BFS_Traverse(List_Graph& G)//����ͨͼ����ÿһ������
{
	cout << "BFS Traversing every vertex......" << endl;
	Clear_visited(G);
	for (int i = 0; i < G.v_num; i++)
	{
		if (!visited[i])
		{
			List_BFS(G, G.v[i].info);
			cout << endl;
			Clear_visited(G);
		}
	}
}


//ͼ����ʾ����
//8 9 0 0
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 v0 v2 v1 v3 v1 v4 v2 v5 v2 v6 v3 v7 v4 v7 v5 v6  ����һ����������Ҳ�У����棩,Ϊ�˷������������ú�������
//-------------------------------------------------------------------------------------------------
//������ʾ����
//8 9 0 1
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 2 v0 v2 4 v1 v3 5 v1 v4 6 v2 v5 2 v2 v6 8 v3 v7 5 v4 v7 7 v5 v6 4 