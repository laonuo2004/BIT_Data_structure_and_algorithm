#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

typedef char VertexType;

// 邻接表AdjList结构体定义
typedef struct ArcNode // 边表结点
{
	int adjvex; // 该弧所指向的顶点的位置
	struct ArcNode* nextarc;
	//int info; // 网的边权值等信息，本题为无权图，因此不需要
}ArcNode;

typedef struct VNode // 顶点表结点
{
	VertexType data; // 顶点信息
	ArcNode* firstarc;
}VNode;

typedef struct // 邻接表
{
	vector<VNode> vertices;
	int vexnum, arcnum; // 顶点数和弧数
}ALGraph;

ALGraph G;

void outPutGraph()
{
	cout << "the ALGraph is" << endl;

	for (int i = 0; i < G.vexnum; ++i)
	{
		cout << G.vertices[i].data;
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			cout << " " << p->adjvex;
			p = p->nextarc;
		}
		cout << endl;
	}
}

void BFS()
{
	cout << "the Breadth-First-Seacrh list:";

	// BFS的基本配置：一个队列和一个visited数组
	queue<int> Q;
	vector<bool> visited(G.vexnum, false);

	for (int i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i]) // 把每个连通分量的第一个顶点入队
			Q.push(i);

		while (!Q.empty()) // 一个连通分量里的BFS
		{
			// 取当前顶点进行操作
			int v = Q.front();
			Q.pop();
			if (!visited[v])
			{
				cout << G.vertices[v].data;
				visited[v] = true;
			}

			// 加入邻接点
			ArcNode* p = G.vertices[v].firstarc;
			while (p)
			{
				if (!visited[p->adjvex]) // 注意如果已经访问过就没必要入队了
					Q.push(p->adjvex);
				p = p->nextarc;
			}
		}
	}

	cout << endl;
}

int main()
{
	char data;
	while (cin >> data, data != '*')
	{
		VNode v;
		v.data = data;
		v.firstarc = NULL;
		G.vertices.push_back(v);
		G.vexnum++;
	}

	int v1, v2;
	while(scanf("%d,%d", &v1, &v2), v1 != -1 && v2 != -1)
	{
		ArcNode* p = new ArcNode;
		p->adjvex = v2;
		p->nextarc = G.vertices[v1].firstarc; // 头插法
		G.vertices[v1].firstarc = p;

		p = new ArcNode; // 无向图，两个方向都要存
		p->adjvex = v1;
		p->nextarc = G.vertices[v2].firstarc;
		G.vertices[v2].firstarc = p;
		G.arcnum++;
	}

	outPutGraph();
	BFS();

	return 0;
}

/*
* 收获1：邻接表的基本定义：顶点表、边表以及整个邻接表
* 收获2：BFS的基本配置：一个队列和一个visited数组
* 
* 注意1：对于无向图，每条边都要存两次！不论是邻接表还是邻接矩阵
* 注意2：BFS的稳健性：在原来的while(!Q.empty())外面再套一个循环，从而可以处理多个连通分量，在非连通图中也同样适用，保障了BFS的稳健性
*/