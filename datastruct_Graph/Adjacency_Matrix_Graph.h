#pragma once
#include<iostream>
#include <iomanip>
#include<vector>
#include<queue>
#include <algorithm>
using namespace std;

#define INF 32767
#define  MAX 50
typedef string Matrix_Vertex_Element;//������Ϣ
typedef int Matrix_Edge_Element;//��Ȩֵ
bool visited[MAX];

#define Stack_Max 50
typedef int Stack_Element;
typedef int QElement;

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

typedef struct Vertex {
	int index;                        // ������
	Matrix_Vertex_Element info;       // ������Ϣ
} Vertex;

typedef struct Edge {
	Vertex head;                      // ���
	Vertex tail;                      // �յ�
	Matrix_Edge_Element value;        // Ȩֵ
} Edge;

typedef struct Matrix {
	Vertex v[MAX];                    // ���㼯��
	Edge e[MAX][MAX];                 // �߼���
	int v_num, e_num;                 // ����ͱ�����
	int Is_directed = 0;              // �Ƿ�����
	int Is_mesh = 1;                  // �Ƿ��Ȩ
} Matrix_Graph;

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
int Locate_Matrix_Vertex(Matrix_Graph& G, Matrix_Vertex_Element v)//��λ�������±�
{
	int i;
	for (i = 0; i < G.v_num; i++)
	{
		if (v == G.v[i].info)return i;
	}
	return -1;
}

void calculateInDegree(Matrix_Graph& G, vector<int>& inDegree) {
	for (int i = 0; i < G.v_num; i++) {
		for (int j = 0; j < G.v_num; j++) {
			if (G.e[i][j].value != 0 && G.e[i][j].value != INF) {
				inDegree[j]++; // ����б� i->j���� j ����ȼ� 1
			}
		}
	}
}

void Create_Matrix_Undirected_Graph(Matrix_Graph& G)//��������ͼ
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���ڽӾ���
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2." << endl;//�����ڽӾ���
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = G.e[n][m].value = 1;
	}
}

void Create_Matrix_Undirected_Mesh(Matrix_Graph& G)//����������
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���ڽӾ���
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2 Weight." << endl;//�����ڽӾ���
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;
		Matrix_Edge_Element e;//Ȩֵ
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;
		cin >> e;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);
		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = G.e[n][m].value = e;
	}
}

void Create_Matrix_Directed_Graph(Matrix_Graph& G)//��������ͼ
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���ڽӾ���
	{
		for(int j=0;j<G.v_num;j++)
			G.e[i][j].value = INF;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���Խ���
	{
			G.e[i][i].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2." << endl;//�����ڽӾ���
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;//�������Ϊx1-->x2
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);

		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = 1;
	}
}

void Create_Matrix_Directed_Mesh(Matrix_Graph& G)//����������
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//������������Ϣ
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���ڽӾ���
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = INF;
	}

	for (int i = 0; i < G.v_num; i++)//��ʼ���Խ���
	{
		G.e[i][i].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2 Weight." << endl;//�����ڽӾ���
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;//�������Ϊx1-->x2
		Matrix_Edge_Element e;//Ȩֵ
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//����# #����
			break;
		cin >> e;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);
		if (m == -1 || n == -1) //�ж������Ƿ���Ч
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = e;
	}
}

void Create_Matrix_Graph(Matrix_Graph& G)//�жϲ��Ҵ���ͼ
{
	cout << "Please enter the vertex number,the edge number,directed(0 False,1 True),mesh(0 False,1 True)." << endl;
	cin >> G.v_num >> G.e_num >> G.Is_directed >> G.Is_mesh;
	if (G.Is_directed == 0)
	{
		if (G.Is_mesh == 0)
		{
			cout << "Create_Matrix_Matrix undirected Matrix_Graph......" << endl;
			Create_Matrix_Undirected_Graph(G);
		}
		else
		{
			cout << "Create_Matrix_Matrix undirected mesh......" << endl;
			Create_Matrix_Undirected_Mesh(G);
		}
	}
	else
	{
		if (G.Is_mesh == 0)
		{
			cout << "Create_Matrix_Matrix directed Matrix_Graph......" << endl;
			Create_Matrix_Directed_Graph(G);
		}
		else
		{
			cout << "Create_Matrix_Matrix directed mesh......" << endl;
			Create_Matrix_Directed_Mesh(G);
		}
	}
}

void Display_Matrix(Matrix_Graph& G)//����ڽӾ���
{
	cout << "Creating Graph......" << endl;
	//Sleep(1000);
	// ��ӡ���������
	cout << "   ";  
	for (int i = 0; i < G.v_num; i++) 
	{
		cout << setw(2) <<"v"  << i  << " ";
	}
	cout << endl;

	// ��ӡ�ڽӾ���
	for (int i = 0; i < G.v_num; i++) 
	{
		cout << "v" << i << " ";  

		for (int j = 0; j < G.v_num; j++) 
		{
			if (G.e[i][j].value == INF) 
			{
				cout  << "  ��" << " ";  // ���INF�ַ���
			}
			else 
			{
				cout << setw(3) << G.e[i][j].value << " ";  // ʹ��setw���������Ԫ�أ�ȷ��ÿ��Ԫ��ռ��3���ַ����
			}
		}
		cout << endl;
	}
}

void Visited(Matrix_Graph& G, Matrix_Vertex_Element V)
{
	int m=Locate_Matrix_Vertex(G, V);
	visited[m] = 1;
	//cout << V << " ";
}

void Clear_visited(Matrix_Graph& G)
{
	for (int i = 0; i < G.v_num; i++)
	{
		visited[i] = 0;
	}
}

void Matrix_DFS(Matrix_Graph& G, Matrix_Vertex_Element V)//������� �ݹ���ǵݹ�
{
	//�ݹ�
	//int L = Locate_Matrix_Vertex(G, V);
	//if (L == -1)
	//{
		//cout << "Error: Invalid vertex input!" << endl;
		//return;
	//}
	//Visited(G, V);
	//for (int i = 0; i < G.v_num; i++)
	//{
		//if (G.e[L][i].value != 0)
			//if (!visited[i])
				//Matrix_DFS(G, G.v[i].info);
	//}
	//�ǵݹ�
	Stack S;
	Init_stack(S);  

	int L = Locate_Matrix_Vertex(G, V);
	if (L == -1) {
		cout << "Error: Invalid vertex input!" << endl;
		return;
	}

	Visited(G, V);  
	Push_stack(S, L);  
	while (!IsEmpty_stack(S)) {
		int temp = Peek_stack(S);  
		Pop_stack(S);  

		cout << G.v[temp].info << " ";  

		// �����뵱ǰ�������ڵ�����δ���ʵĶ���
		for (int i = 0; i < G.v_num; i++) {
			if ((G.e[temp][i].value != 0) && (G.e[temp][i].value != INF) && visited[i] == 0) {  // ���ڱ߲���δ����
				visited[i] = 1;  // ���Ϊ�ѷ���
				Push_stack(S, i);  // ���ö�����ջ
			}
		}
	}
	Destroy_Stack(S);
}

void Matrix_BFS(Matrix_Graph& G, Matrix_Vertex_Element V)
{
	Queue Q;
	init_queue(Q);

	int L = Locate_Matrix_Vertex(G, V);
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
		cout<< G.v[temp].info << " ";
		// �����뵱ǰ�������ڵ�����δ���ʵĶ���
		for (int i = 0; i < G.v_num; i++) {
			if ((G.e[temp][i].value != 0) && (G.e[temp][i].value != INF) && visited[i] == 0) {  // ���ڱ߲���δ����
				visited[i] = 1;  // ���Ϊ�ѷ���
				Push_queue(Q, i);  // ���ö�����ջ
			}
		}
	}
}

void Matrix_DFS_Traverse(Matrix_Graph& G)//����ͨͼ����ÿһ������
{
	cout << "DFS Traversing every vertex......" << endl;
	Clear_visited(G);
	for (int i = 0; i < G.v_num; i++)
	{
		if (!visited[i])
		{
			Matrix_DFS(G, G.v[i].info);
			cout << endl;
			Clear_visited(G);
		}
	}
}

void Matrix_BFS_Traverse(Matrix_Graph& G)//����ͨͼ����ÿһ������
{
	cout << "BFS Traversing every vertex......" << endl;
	Clear_visited(G);
	for (int i = 0; i < G.v_num; i++)
	{
		if (!visited[i])
		{
			Matrix_BFS(G, G.v[i].info);
			cout << endl;
			Clear_visited(G);
		}
	}
}

//���·��
void Dijkstra(Matrix_Graph& G) {
	cout << "Enter your start vertex :" << endl;
	Matrix_Vertex_Element startVertex;
	cin >> startVertex;
	Clear_visited(G);
	int start = Locate_Matrix_Vertex(G, startVertex);

	if (start == -1) {
		cout << "Error: Invalid start !" << endl;
		return;
	}

	int dist[MAX];          // �洢����㵽ÿ���������̾���
	int prev[MAX];          // �洢·���е�ǰ���ڵ�

	for (int i = 0; i < G.v_num; i++)
	{
		dist[i] = INF;
		prev[i] = -1;
		visited[i] = false;
	}
	dist[start] = 0;

	for (int i = 0; i < G.v_num; i++)
	{
		int u = -1, minDist = INF;
		for (int j = 0; j < G.v_num; j++)
		{
			if (!visited[j] && dist[j] <= minDist)
			{
				u = j;
				minDist = dist[j];
			}
		}
		if (u == -1)break;
		visited[u] = true;

		for (int v = 0; v < G.v_num; v++)
		{
			if (!visited[v] && G.e[u][v].value != INF)
			{
				int newDist = dist[u] + G.e[u][v].value;
				if (newDist < dist[v])
				{
					dist[v] = newDist;
					prev[v] = u;
				}
			}
		}
		
	}
	// ������·�����
	cout << "Shortest distances from vertex " << startVertex << ":" << endl;
	for (int i = 0; i < G.v_num; i++) {
		cout << "To " << G.v[i].info << ": ";
		if (dist[i] == INF) {
			cout << "��" << endl;
		}
		else {
			cout << dist[i] << " Path: ";
			// ���·��
			int temp = i;
			vector<int> path;
			while (temp != -1) {
				path.push_back(temp);
				temp = prev[temp];
			}
			reverse(path.begin(), path.end());
			for (size_t i = 0; i < path.size(); i++) {
				cout << G.v[path[i]].info;
				if (i != path.size() - 1) cout << " -> ";
			}
			cout << endl;
		}
	}
}

void DijkstraTargeted(Matrix_Graph& G)
{
	cout << "Enter your start vertex and end vertex:" << endl;
	Matrix_Vertex_Element startVertex;
	Matrix_Vertex_Element endVertex;
	cin >> startVertex >> endVertex;
	Clear_visited(G);
	int start = Locate_Matrix_Vertex(G, startVertex);
	int end = Locate_Matrix_Vertex(G, endVertex);

	if (start == -1 || end == -1) {
		cout << "Error: Invalid start or end vertex!" << endl;
		return;
	}

	int dist[MAX];          // �洢����㵽ÿ���������̾���
	int prev[MAX];          // �洢·���е�ǰ���ڵ�

	// ��ʼ��
	for (int i = 0; i < G.v_num; i++) {
		dist[i] = INF;      
		prev[i] = -1;       
		visited[i] = false; 
	}
	dist[start] = 0;        // ��㵽����ľ���Ϊ0

	for (int i = 0; i < G.v_num; i++)
	{
		int u = -1, minDist = INF;

		for (int j = 0; j < G.v_num; j++)// �ҵ�δ���ʽڵ��о�����С��һ���ڵ�u
		{
			if (!visited[j] && dist[j] <= minDist)
			{
				u = j;
				minDist = dist[j];
			}
		}
		if (u == -1)break;// ���û�пɷ��ʵĽڵ㣬�˳�ѭ��
		visited[u] = true;

		if (u == end)break;// �������Ŀ��ڵ㣬ֹͣ����

		for (int v = 0; v < G.v_num; v++)// ����u���ڽӽڵ�ľ���
		{
			if (!visited[v] && G.e[u][v].value != INF)
			{
				int newDist = dist[u] + G.e[u][v].value;
				if (newDist < dist[v]) 
				{
					dist[v] = newDist;
					prev[v] = u;
				}
			}
		}
	}
	// ������
	cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;
	if (dist[end] == INF) {
		cout << "No path exists!" << endl;
	}
	else {
		cout << "Distance: " << dist[end] << endl;
		cout << "Path: ";
		// ���·��
		vector<int> path;
		int temp = end;
		while (temp != -1) {
			path.push_back(temp);
			temp = prev[temp];
		}
		reverse(path.begin(), path.end());
		for (size_t i = 0; i < path.size(); i++) {
			cout << G.v[path[i]].info;
			if (i != path.size() - 1) cout << " -> ";
		}
		cout << endl;
	}
}

void Floyd_Warshall(Matrix_Graph& G) {
	int n = G.v_num; // ��������
	int dist[MAX][MAX]; // ���·������

	// ��ʼ�����·������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
		{
			if (i == j) 
			{
				dist[i][j] = 0; // �Լ����Լ��ľ���Ϊ 0
			}
			else if (G.e[i][j].value != 0) 
			{
				dist[i][j] = G.e[i][j].value; // �б���Ȩֵ
			}
			else 
			{
				dist[i][j] = INF; // �ޱ߸������
			}
		}
	}

	// �����㷨
	for (int k = 0; k < n; k++) { // �м��
		for (int i = 0; i < n; i++) { // ���
			for (int j = 0; j < n; j++) { // �յ�
				if (dist[i][k] != INF && dist[k][j] != INF &&dist[i][j] > dist[i][k] + dist[k][j]) 
				{
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	// ������·������
	cout << "Shortest Path Matrix:" << endl;
	cout << "   ";
	for (int i = 0; i < n; i++) {
		cout << setw(3) << "v" << i;
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "v" << i ;
		for (int j = 0; j < n; j++) {
			if (dist[i][j] == INF) {
				cout << setw(4) << "��";
			}
			else {
				cout << setw(4) << dist[i][j];
			}
		}
		cout << endl;
	}
}

//��С������
void MinTree_Prim(Matrix_Graph G) // Prim��С������
{
	cout << "Finding Prim MinTree......" << endl;
	Clear_visited(G);
	visited[0] = 1; // �趨��ʼ��
	int Prim_result = 0; // ��С����������Ȩ��

	cout << "Minimum Spanning Tree (MST):" << endl;
	for (int m = 1; m < G.v_num; m++) // һ��G.v_num-1���ߣ�ѭ����Щ��
	{
		int minweight = INF; // ��¼��С�ߵ�Ȩ��
		int x = -1, y = -1;  // ��¼��С�ߵ���������

		// ���������ѷ��ʵĶ��㣬�ҵ���С��
		for (int i = 0; i < G.v_num; i++)
		{
			if (visited[i]) // �������i�ѷ���
			{
				for (int j = 0; j < G.v_num; j++)
				{
					// �������jδ���ʣ��ұ�i->j��Ȩ��С�ڵ�ǰ��СȨ��
					if (!visited[j] && G.e[i][j].value < minweight && G.e[i][j].value != 0)
					{
						minweight = G.e[i][j].value; // ������СȨ��
						x = i; // ��¼�ߵ����
						y = j; // ��¼�ߵ��յ�
					}
				}
			}
		}

		// ����ҵ���С��
		if (x != -1 && y != -1)
		{
			visited[y] = 1; // ����յ�Ϊ�ѷ���
			Prim_result += minweight; // �ۼ���Ȩ��

			// ����ߵ���״��A->B (weight: w)
			cout << G.v[x].info << " -> " << G.v[y].info << " (weight: " << minweight << ")" << endl;
		}
	}

	// �����С����������Ȩ��
	cout << "Total weight of MST: " << Prim_result << endl;
}

int parent[MAX];// ���鼯���ݽṹ
int find(int i) {// ���Ҹ��ڵ�
	while (parent[i] != i) {
		i = parent[i];
	}
	return i;
}
void union_sets(int i, int j) {// �ϲ���������
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}
void MinTree_Kruskal(Matrix_Graph& G) {// Kruskal�㷨ʵ��
	// ��ʼ�����鼯
	for (int i = 0; i < G.v_num; i++) {
		parent[i] = i;
	}

	// �洢���бߵ�����
	vector<Edge> edges;

	// ��ͼ�е����б���ӵ�edges������
	for (int i = 0; i < G.v_num; i++) {
		for (int j = i + 1; j < G.v_num; j++) {
			if (G.e[i][j].value != INF && G.e[i][j].value != 0) {
				Edge edge;
				edge.head = G.v[i];
				edge.tail = G.v[j];
				edge.value = G.e[i][j].value;
				edges.push_back(edge);
			}
		}
	}

	// ���ߵ�Ȩ����������
	sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		return a.value < b.value;
		});

	// Kruskal�㷨���Ĳ���
	int edge_count = 0;
	int total_weight = 0;
	cout << "Minimum Spanning Tree (MST):" << endl;
	for (Edge e : edges) {
		int u = find(e.head.index);
		int v = find(e.tail.index);

		if (u != v) {
			// ����ߵ���״��A->B
			cout << e.head.info << " -> " << e.tail.info << " (weight: " << e.value << ")" << endl;
			total_weight += e.value;
			union_sets(u, v);
			edge_count++;
		}

		if (edge_count == G.v_num - 1) {
			break;
		}
	}

	cout << "Total weight of MST: " << total_weight << endl;
}

//��������,���������޻�ͼ
void TopologicalSort(Matrix_Graph& G)
{
	vector<int>indegree(G.v_num, 0);
	calculateInDegree(G, indegree);

	queue<int>q;// ���ڴ洢���Ϊ 0 �Ķ���
	for (int i = 0; i < G.v_num; i++) {
		if (indegree[i] == 0) {
			q.push(i); // �����Ϊ 0 �Ķ���������
		}
	}

	vector<Matrix_Vertex_Element> result; // �洢��������Ľ��
	while (!q.empty())
	{
		int u = q.front();// ȡ��һ�����Ϊ 0 �Ķ���
		q.pop();
		result.push_back(G.v[u].info);

		// ���� u �������ڽӶ���
		for (int v = 0; v < G.v_num; v++)
		{
			if (G.e[u][v].value != 0 && G.e[u][v].value != INF)
			{
				indegree[v]--;// ���ڽӶ������ȼ� 1
				if (indegree[v] == 0)
				{
					q.push(v);// �����ȱ�Ϊ 0���������
				}
			}
		}
	}

	if (result.size() != G.v_num)// ����Ƿ����ж��㶼������
	{
		cout << "The graph has a cycle, topological sort is not possible!" << endl;
		return;
	}
	// �������������
	cout << "Topological Sort: ";
	for (const auto& vertex : result) {
		cout << vertex << " ";
	}
	cout << endl;
}


//����ͼ����ʾ����
//8 9 0 0
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 v0 v2 v1 v3 v1 v4 v2 v5 v2 v6 v3 v7 v4 v7 v5 v6  ����һ����������Ҳ�У����棩,Ϊ�˷������������ú�������
//-------------------------------------------------------------------------------------------------
//����������ʾ����
//8 9 0 1
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 2 v0 v2 4 v1 v3 5 v1 v4 6 v2 v5 2 v2 v6 8 v3 v7 5 v4 v7 7 v5 v6 4 
//-------------------------------------------------------------------------------------------------
//����ͼ����ʾ����
//8 9 1 0
//v1 v2 v3 v4 v5 v6 v7 v8
//v1 v2 
//v1 v3 
//v2 v4
//v2 v5 
//v3 v6 
//v3 v7 
//v4 v8 
//v5 v8 
//v6 v7 
//-------------------------------------------------------------------------------------------------
//����������ʾ����
//8 9 1 1
//v1 v2 v3 v4 v5 v6 v7 v8
//v1 v2 2
//v1 v3 4
//v2 v4 5
//v2 v5 6
//v3 v6 2
//v3 v7 8
//v4 v8 5
//v5 v8 7
//v6 v7 4 
// //-------------------------------------------------------------------------------------------------
//����ͼ���ʾ����
//    v1  v2  v3  v4  v5  v6  v7  v8
//v1   0   1   1   0   0   0   0   0
//v2   1   0   0   1   1   0   0   0
//v3   1   0   0   0   0   1   1   0
//v4   0   1   0   0   0   0   0   1
//v5   0   1   0   0   0   0   0   1
//v6   0   0   1   0   0   0   1   0
//v7   0   0   1   0   0   1   0   0
//v8   0   0   0   1   1   0   0   0
//
//����ͼ���ʾ��
//    v1  v2  v3  v4  v5  v6  v7  v8
//v1   0   1   1   ��   ��   ��   ��   ��
//v2   ��   0   ��   1   1   ��   ��   ��
//v3   ��   ��   0   ��   ��   1   1   ��
//v4   ��   ��   ��   0   ��   ��   ��   1
//v5   ��   ��   ��   ��   0   ��   ��   1
//v6   ��   ��   ��   ��   ��   0   1   ��
//v7   ��   ��   ��   ��   ��   ��   0   ��
//v8   ��   ��   ��   ��   ��   ��   ��   0