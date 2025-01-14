#pragma once
#include<iostream>
#include <iomanip>
#include<vector>
#include<queue>
#include <algorithm>
using namespace std;

#define INF 32767
#define  MAX 50
typedef string Matrix_Vertex_Element;//顶点信息
typedef int Matrix_Edge_Element;//边权值
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
	QElement data; // 存储队列中的数据
	Qnode* next;  // 指向下一个节点的指针
} *Queuelist; // 这里是 Qnode* 的定义

typedef struct {
	Queuelist head; // 头指针
	Queuelist rear; // 尾指针
} Queue;

typedef struct Vertex {
	int index;                        // 顶点编号
	Matrix_Vertex_Element info;       // 顶点信息
} Vertex;

typedef struct Edge {
	Vertex head;                      // 起点
	Vertex tail;                      // 终点
	Matrix_Edge_Element value;        // 权值
} Edge;

typedef struct Matrix {
	Vertex v[MAX];                    // 顶点集合
	Edge e[MAX][MAX];                 // 边集合
	int v_num, e_num;                 // 顶点和边数量
	int Is_directed = 0;              // 是否有向
	int Is_mesh = 1;                  // 是否带权
} Matrix_Graph;

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
int Locate_Matrix_Vertex(Matrix_Graph& G, Matrix_Vertex_Element v)//定位输入点的下标
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
				inDegree[j]++; // 如果有边 i->j，则 j 的入度加 1
			}
		}
	}
}

void Create_Matrix_Undirected_Graph(Matrix_Graph& G)//创建无向图
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//初始化邻接矩阵
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2." << endl;//创建邻接矩阵
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = G.e[n][m].value = 1;
	}
}

void Create_Matrix_Undirected_Mesh(Matrix_Graph& G)//创建无向网
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//初始化邻接矩阵
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2 Weight." << endl;//创建邻接矩阵
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;
		Matrix_Edge_Element e;//权值
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;
		cin >> e;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);
		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = G.e[n][m].value = e;
	}
}

void Create_Matrix_Directed_Graph(Matrix_Graph& G)//创建有向图
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//初始化邻接矩阵
	{
		for(int j=0;j<G.v_num;j++)
			G.e[i][j].value = INF;
	}

	for (int i = 0; i < G.v_num; i++)//初始化对角线
	{
			G.e[i][i].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2." << endl;//创建邻接矩阵
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;//设有向边为x1-->x2
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);

		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = 1;
	}
}

void Create_Matrix_Directed_Mesh(Matrix_Graph& G)//创建有向网
{
	int m, n;
	cout << "Please enter the vertexs in order(V0 V1 V2......)." << endl;
	for (int i = 0; i < G.v_num; i++)//依次输入点的信息
	{
		G.v[i].index = i;
		cin >> G.v[i].info;
	}

	for (int i = 0; i < G.v_num; i++)//初始化邻接矩阵
	{
		for (int j = 0; j < G.v_num; j++)
			G.e[i][j].value = INF;
	}

	for (int i = 0; i < G.v_num; i++)//初始化对角线
	{
		G.e[i][i].value = 0;
	}

	cout << "Please enter the edges in the format: Vertex1 Vertex2 Weight." << endl;//创建邻接矩阵
	for (int t = 0; t < G.e_num; t++)
	{
		Matrix_Vertex_Element x1, x2;//设有向边为x1-->x2
		Matrix_Edge_Element e;//权值
		cin >> x1 >> x2;
		if (x1 == "#" && x2 == "#")//输入# #结束
			break;
		cin >> e;

		m = Locate_Matrix_Vertex(G, x1);
		n = Locate_Matrix_Vertex(G, x2);
		if (m == -1 || n == -1) //判断输入是否有效
		{
			cout << "Error: Invalid vertex input!" << endl;
			continue;
		}
		G.e[m][n].value = e;
	}
}

void Create_Matrix_Graph(Matrix_Graph& G)//判断并且创建图
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

void Display_Matrix(Matrix_Graph& G)//输出邻接矩阵
{
	cout << "Creating Graph......" << endl;
	//Sleep(1000);
	// 打印顶点表（横向）
	cout << "   ";  
	for (int i = 0; i < G.v_num; i++) 
	{
		cout << setw(2) <<"v"  << i  << " ";
	}
	cout << endl;

	// 打印邻接矩阵
	for (int i = 0; i < G.v_num; i++) 
	{
		cout << "v" << i << " ";  

		for (int j = 0; j < G.v_num; j++) 
		{
			if (G.e[i][j].value == INF) 
			{
				cout  << "  ∞" << " ";  // 输出INF字符串
			}
			else 
			{
				cout << setw(3) << G.e[i][j].value << " ";  // 使用setw来对齐矩阵元素，确保每个元素占据3个字符宽度
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

void Matrix_DFS(Matrix_Graph& G, Matrix_Vertex_Element V)//深度历遍 递归与非递归
{
	//递归
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
	//非递归
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

		// 遍历与当前顶点相邻的所有未访问的顶点
		for (int i = 0; i < G.v_num; i++) {
			if ((G.e[temp][i].value != 0) && (G.e[temp][i].value != INF) && visited[i] == 0) {  // 存在边并且未访问
				visited[i] = 1;  // 标记为已访问
				Push_stack(S, i);  // 将该顶点入栈
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
		// 遍历与当前顶点相邻的所有未访问的顶点
		for (int i = 0; i < G.v_num; i++) {
			if ((G.e[temp][i].value != 0) && (G.e[temp][i].value != INF) && visited[i] == 0) {  // 存在边并且未访问
				visited[i] = 1;  // 标记为已访问
				Push_queue(Q, i);  // 将该顶点入栈
			}
		}
	}
}

void Matrix_DFS_Traverse(Matrix_Graph& G)//非连通图历遍每一个顶点
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

void Matrix_BFS_Traverse(Matrix_Graph& G)//非连通图历遍每一个顶点
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

//最短路径
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

	int dist[MAX];          // 存储从起点到每个顶点的最短距离
	int prev[MAX];          // 存储路径中的前驱节点

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
	// 输出最短路径结果
	cout << "Shortest distances from vertex " << startVertex << ":" << endl;
	for (int i = 0; i < G.v_num; i++) {
		cout << "To " << G.v[i].info << ": ";
		if (dist[i] == INF) {
			cout << "∞" << endl;
		}
		else {
			cout << dist[i] << " Path: ";
			// 输出路径
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

	int dist[MAX];          // 存储从起点到每个顶点的最短距离
	int prev[MAX];          // 存储路径中的前驱节点

	// 初始化
	for (int i = 0; i < G.v_num; i++) {
		dist[i] = INF;      
		prev[i] = -1;       
		visited[i] = false; 
	}
	dist[start] = 0;        // 起点到自身的距离为0

	for (int i = 0; i < G.v_num; i++)
	{
		int u = -1, minDist = INF;

		for (int j = 0; j < G.v_num; j++)// 找到未访问节点中距离最小的一个节点u
		{
			if (!visited[j] && dist[j] <= minDist)
			{
				u = j;
				minDist = dist[j];
			}
		}
		if (u == -1)break;// 如果没有可访问的节点，退出循环
		visited[u] = true;

		if (u == end)break;// 如果到达目标节点，停止搜索

		for (int v = 0; v < G.v_num; v++)// 更新u的邻接节点的距离
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
	// 输出结果
	cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;
	if (dist[end] == INF) {
		cout << "No path exists!" << endl;
	}
	else {
		cout << "Distance: " << dist[end] << endl;
		cout << "Path: ";
		// 输出路径
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
	int n = G.v_num; // 顶点数量
	int dist[MAX][MAX]; // 最短路径矩阵

	// 初始化最短路径矩阵
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
		{
			if (i == j) 
			{
				dist[i][j] = 0; // 自己到自己的距离为 0
			}
			else if (G.e[i][j].value != 0) 
			{
				dist[i][j] = G.e[i][j].value; // 有边则赋权值
			}
			else 
			{
				dist[i][j] = INF; // 无边赋无穷大
			}
		}
	}

	// 核心算法
	for (int k = 0; k < n; k++) { // 中间点
		for (int i = 0; i < n; i++) { // 起点
			for (int j = 0; j < n; j++) { // 终点
				if (dist[i][k] != INF && dist[k][j] != INF &&dist[i][j] > dist[i][k] + dist[k][j]) 
				{
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	// 输出最短路径矩阵
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
				cout << setw(4) << "∞";
			}
			else {
				cout << setw(4) << dist[i][j];
			}
		}
		cout << endl;
	}
}

//最小生成树
void MinTree_Prim(Matrix_Graph G) // Prim最小生成树
{
	cout << "Finding Prim MinTree......" << endl;
	Clear_visited(G);
	visited[0] = 1; // 设定起始点
	int Prim_result = 0; // 最小生成树的总权重

	cout << "Minimum Spanning Tree (MST):" << endl;
	for (int m = 1; m < G.v_num; m++) // 一共G.v_num-1条边，循环这些次
	{
		int minweight = INF; // 记录最小边的权重
		int x = -1, y = -1;  // 记录最小边的两个顶点

		// 遍历所有已访问的顶点，找到最小边
		for (int i = 0; i < G.v_num; i++)
		{
			if (visited[i]) // 如果顶点i已访问
			{
				for (int j = 0; j < G.v_num; j++)
				{
					// 如果顶点j未访问，且边i->j的权重小于当前最小权重
					if (!visited[j] && G.e[i][j].value < minweight && G.e[i][j].value != 0)
					{
						minweight = G.e[i][j].value; // 更新最小权重
						x = i; // 记录边的起点
						y = j; // 记录边的终点
					}
				}
			}
		}

		// 如果找到最小边
		if (x != -1 && y != -1)
		{
			visited[y] = 1; // 标记终点为已访问
			Prim_result += minweight; // 累加总权重

			// 输出边的形状：A->B (weight: w)
			cout << G.v[x].info << " -> " << G.v[y].info << " (weight: " << minweight << ")" << endl;
		}
	}

	// 输出最小生成树的总权重
	cout << "Total weight of MST: " << Prim_result << endl;
}

int parent[MAX];// 并查集数据结构
int find(int i) {// 查找根节点
	while (parent[i] != i) {
		i = parent[i];
	}
	return i;
}
void union_sets(int i, int j) {// 合并两个集合
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}
void MinTree_Kruskal(Matrix_Graph& G) {// Kruskal算法实现
	// 初始化并查集
	for (int i = 0; i < G.v_num; i++) {
		parent[i] = i;
	}

	// 存储所有边的向量
	vector<Edge> edges;

	// 将图中的所有边添加到edges向量中
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

	// 按边的权重升序排序
	sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		return a.value < b.value;
		});

	// Kruskal算法核心部分
	int edge_count = 0;
	int total_weight = 0;
	cout << "Minimum Spanning Tree (MST):" << endl;
	for (Edge e : edges) {
		int u = find(e.head.index);
		int v = find(e.tail.index);

		if (u != v) {
			// 输出边的形状：A->B
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

//拓扑排序,用于有向无环图
void TopologicalSort(Matrix_Graph& G)
{
	vector<int>indegree(G.v_num, 0);
	calculateInDegree(G, indegree);

	queue<int>q;// 用于存储入度为 0 的顶点
	for (int i = 0; i < G.v_num; i++) {
		if (indegree[i] == 0) {
			q.push(i); // 将入度为 0 的顶点加入队列
		}
	}

	vector<Matrix_Vertex_Element> result; // 存储拓扑排序的结果
	while (!q.empty())
	{
		int u = q.front();// 取出一个入度为 0 的顶点
		q.pop();
		result.push_back(G.v[u].info);

		// 遍历 u 的所有邻接顶点
		for (int v = 0; v < G.v_num; v++)
		{
			if (G.e[u][v].value != 0 && G.e[u][v].value != INF)
			{
				indegree[v]--;// 将邻接顶点的入度减 1
				if (indegree[v] == 0)
				{
					q.push(v);// 如果入度变为 0，加入队列
				}
			}
		}
	}

	if (result.size() != G.v_num)// 检查是否所有顶点都被排序
	{
		cout << "The graph has a cycle, topological sort is not possible!" << endl;
		return;
	}
	// 输出拓扑排序结果
	cout << "Topological Sort: ";
	for (const auto& vertex : result) {
		cout << vertex << " ";
	}
	cout << endl;
}


//无向图输入示例：
//8 9 0 0
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 v0 v2 v1 v3 v1 v4 v2 v5 v2 v6 v3 v7 v4 v7 v5 v6  两个一行竖着输入也行（后面）,为了方便测试这里采用横行输入
//-------------------------------------------------------------------------------------------------
//无向网输入示例：
//8 9 0 1
//v0 v1 v2 v3 v4 v5 v6 v7
//v0 v1 2 v0 v2 4 v1 v3 5 v1 v4 6 v2 v5 2 v2 v6 8 v3 v7 5 v4 v7 7 v5 v6 4 
//-------------------------------------------------------------------------------------------------
//有向图输入示例：
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
//无向网输入示例：
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
//无向图输出示例：
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
//有向图输出示例
//    v1  v2  v3  v4  v5  v6  v7  v8
//v1   0   1   1   ∞   ∞   ∞   ∞   ∞
//v2   ∞   0   ∞   1   1   ∞   ∞   ∞
//v3   ∞   ∞   0   ∞   ∞   1   1   ∞
//v4   ∞   ∞   ∞   0   ∞   ∞   ∞   1
//v5   ∞   ∞   ∞   ∞   0   ∞   ∞   1
//v6   ∞   ∞   ∞   ∞   ∞   0   1   ∞
//v7   ∞   ∞   ∞   ∞   ∞   ∞   0   ∞
//v8   ∞   ∞   ∞   ∞   ∞   ∞   ∞   0