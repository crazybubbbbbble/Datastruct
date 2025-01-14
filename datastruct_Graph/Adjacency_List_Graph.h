#pragma once
#include<iostream>
#include <iomanip>
#include<Windows.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef string List_Vertex_Element;//顶点信息
typedef int List_Edge_Element;//边权值
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
	QElement data; // 存储队列中的数据
	Qnode* next;  // 指向下一个节点的指针
} *Queuelist; // 这里是 Qnode* 的定义

typedef struct {
	Queuelist head; // 头指针
	Queuelist rear; // 尾指针
} Queue;

typedef struct Edge_node {//边
	List_Vertex_Element front;
	List_Vertex_Element tail;
	int index;//被指向的下标
	List_Edge_Element value;//权值
	Edge_node* next;//指向下一个边
}*Enode;

typedef struct Vertex_node {//顶点
	int index;//下标
	List_Vertex_Element info;//顶点信息
	Enode first_egde;//储存第一个边
}Vnode;

typedef struct Edge_List {//边表
	List_Vertex_Element front;
	List_Vertex_Element tail;
	List_Edge_Element value;//权值
}*List_Edge;

typedef struct List {
	Vnode v[MAX];//顶点表
	int v_num, e_num;//顶点和边的实际数量
	int Is_directed = 0;//是否有向
	int Is_mesh = 0;//是否带权
}List_Graph;

// 并查集结构
struct UnionFind {
	std::vector<int> parent, rank;

	UnionFind(int n) : parent(n), rank(n, 0) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int x) {
		if (parent[x] != x) parent[x] = find(parent[x]); // 路径压缩
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

void Push_stack(Stack& s, Stack_Element d)//入栈
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

Stack_Element Pop_stack(Stack& s)//出栈
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

Stack_Element Peek_stack(Stack& s)//查看栈顶元素
{
	if (!IsEmpty_stack(s))
	{
		//cout << "Top data: " << s.data[s.top] << endl;
		return s.data[s.top];
	}

}

void init_queue(Queue& q)//初始化
{
	q.head = nullptr;
	q.rear = nullptr;
}

int IsEmpty_queue(Queue& q)//判空
{
	if (q.head == nullptr) { return 1; }
	else { return 0; }
}

void Push_queue(Queue& q, QElement d)//入队
{
	Queuelist Newmodels = new Qnode;
	Newmodels->data = d;
	Newmodels->next = nullptr;

	if (IsEmpty_queue(q))//如果队列为空
	{
		q.head = Newmodels;
		q.rear = Newmodels;
	}
	else//不为空则在队尾插入
	{
		q.rear->next = Newmodels;
		q.rear = Newmodels;
	}
}

void Pop_queue(Queue& q)//出队
{
	if (IsEmpty_queue(q))//判空
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

//以下是图的函数
int Locate_List_Vertex(List_Graph& G, List_Vertex_Element v)//定位输入点的下标
{
	int i;
	for (i = 0; i < G.v_num; i++)
	{
		if (v == G.v[i].info)return i;
	}
	return -1;
}

void Create_List_Undirected_Graph(List_Graph& G)//创建无向图
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
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
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//即在点x1处链接x2 x1<-->x2

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//头插法插入，无向图需要在m,n两个边表中都加入临边
		Enode temp1 = new Edge_node;
		temp1->index= n;//将边的信息输入给邻接表m
		temp1->next = G.v[m].first_egde;
		if (G.v[m].first_egde == nullptr) {  // 如果没有边，则初始化 first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}

		Enode temp2 = new Edge_node;
		temp2->index = m;//将边的信息输入给邻接表n
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

void Create_List_Undirected_Mesh(List_Graph& G)//创建无向网
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
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
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;
		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//即在点x1处链接x2 x1<-->x2

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//头插法插入，无向图需要在m,n两个边表中都加入临边
		Enode temp1 = new Edge_node;
		temp1->index = n;//将边的信息输入给邻接表m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		temp1->front = G.v[m].info;
		temp1->tail = G.v[n].info;
		if (G.v[m].first_egde == nullptr) {  // 如果没有边，则初始化 first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}

		Enode temp2 = new Edge_node;
		temp2->index = m;//将边的信息输入给邻接表n
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

void Create_List_Directed_Graph(List_Graph& G)//创建有向图
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
	{
		G.v[i].index = i;
		G.v[i].first_egde = nullptr;
		cin >> G.v[i].info;
	}
	cout << "Please enter the edges in the format: Vertex1 Vertex2.Enter (# #) to quit." << endl;
	for (int t = 0; t < G.e_num; t++)
	{

		List_Vertex_Element x1, x2;//方向为x1->x2
		List_Edge_Element e;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;

		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//即在点x1处链接x2 x1<-->x2

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//头插法插入，有向图只需要在m边表中加入临边
		Enode temp1 = new Edge_node;
		temp1->index = n;//将边的信息输入给邻接表m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		if (G.v[m].first_egde == nullptr) {  // 如果没有边，则初始化 first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}
	}
}

void Create_List_Directed_Mesh(List_Graph& G)//创建有向网
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
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
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;

		cin >> e;

		m = Locate_List_Vertex(G, x1);
		n = Locate_List_Vertex(G, x2);//即在点x1处链接x2 x1<-->x2

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}

		//头插法插入，无向图需要在m,n两个边表中都加入临边
		Enode temp1 = new Edge_node;
		temp1->index = n;//将边的信息输入给邻接表m
		temp1->next = G.v[m].first_egde;
		temp1->value = e;
		if (G.v[m].first_egde == nullptr) {  // 如果没有边，则初始化 first_egde
			G.v[m].first_egde = temp1;
		}
		else {
			temp1->next = G.v[m].first_egde;
			G.v[m].first_egde = temp1;
		}
	}
}

void Create_List_Graph(List_Graph& G)//判断并且创建图
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

void Display_List(List_Graph& G)//输出
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
					cout << "<——>";
					cout << setw(3) << G.v[temp->index].info << "  ";
					temp = temp->next;
				}
			}
			else
			{
				while (temp != nullptr)
				{
					cout << "<——>";
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
					cout << "——>";
					cout << setw(3) << temp->index << "  ";
					temp = temp->next;
				}
			}
			else
			{
				while (temp != nullptr)
				{
					cout << "——>";
					cout << " <" << setw(2) << temp->index << "," << setw(2) << temp->value << "> ";
					temp = temp->next;
				}
			}
		}
		cout << endl;
	}

}

int Out_Degree(List_Graph& G)//计算出度
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

int In_Degree(List_Graph& G)//计算入度
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

void List_DFS(List_Graph& G, List_Vertex_Element V)//深度历遍
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
			if (visited[index] == 0) {  // 存在边并且未访问
				visited[index] = 1;  // 标记为已访问
				Push_stack(S, index);  // 将该顶点入栈
				value += e->value;
				//cout << "  index  " << index << "  ";
			}
		}
	}
	cout << value << " ";
}

void List_BFS(List_Graph& G, List_Vertex_Element V)//广度历遍
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
		// 遍历与当前顶点相邻的所有未访问的顶点
		for (Enode e = G.v[temp].first_egde; e != nullptr; e = e->next) {
			int index = e->index;
			if (visited[index] == 0) {  // 存在边并且未访问
				visited[index] = 1;  // 标记为已访问
				Push_queue(Q, index);  // 将该顶点入栈
				//cout << "  index  " << index << "  ";
			}
		}
	}
}

void List_DFS_Traverse(List_Graph& G)//非连通图历遍每一个顶点
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

void List_BFS_Traverse(List_Graph& G)//非连通图历遍每一个顶点
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


//图输入示例：
//8 9 0 0
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 v0 v2 v1 v3 v1 v4 v2 v5 v2 v6 v3 v7 v4 v7 v5 v6  两个一行竖着输入也行（后面）,为了方便测试这里采用横行输入
//-------------------------------------------------------------------------------------------------
//网输入示例：
//8 9 0 1
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 2 v0 v2 4 v1 v3 5 v1 v4 6 v2 v5 2 v2 v6 8 v3 v7 5 v4 v7 7 v5 v6 4 