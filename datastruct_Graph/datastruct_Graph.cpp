#include"Adjacency_Matrix_Graph.h"
//#include"Adjacency_List_Graph.h"
int main()
{
	Matrix_Graph G;
	Create_Matrix_Graph(G);
	Display_Matrix(G);
	MinTree_Prim(G);
	MinTree_Kruskal(G);
	TopologicalSort(G);
	//Dijkstra(G);
	//Floyd_Warshall(G);
	// 
	//List_Graph G;
	//string V;
	//Create_List_Graph(G);
	//Display_List(G);
}

