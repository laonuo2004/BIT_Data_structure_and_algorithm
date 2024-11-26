#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> adjMatrix;

typedef struct {
	adjMatrix adj; // 邻接矩阵
	//adjMatrix path; // 最短路径，不过本题不需要
	int vexnum, arcnum; // 顶点数和弧数
} Floyd;

Floyd G;

int main()
{
	char startPoint; // 指定从某点开始
	scanf("%d,%d,%c", &G.vexnum, &G.arcnum, &startPoint);
	for(int i = 0; i < G.vexnum; i++)
	{
		vector<int> temp;
		for(int j = 0; j < G.vexnum; j++)
		{
			if(i == j)
				temp.push_back(0);
			else
				temp.push_back(INT_MAX);
		}
		G.adj.push_back(temp);
	}
	for(int i = 0; i < G.arcnum; i++)
	{
		char u, v;
		int w;
		getchar(); // 吸收回车
		scanf("<%c,%c,%d>", &u, &v, &w);
		G.adj[u - 'a'][v - 'a'] = w;
	}

	// Floyd核心部分
	for(int k = 0; k < G.vexnum; k++) // 中间点
		for(int i = 0; i < G.vexnum; i++) // 起点
			for(int j = 0; j < G.vexnum; j++) // 终点
				if(G.adj[i][k] != INT_MAX && G.adj[k][j] != INT_MAX && G.adj[i][j] > G.adj[i][k] + G.adj[k][j]) // 如果经过中间点k的路径比直接连接的路径短，就更新。前面两个判断可以防止溢出
					G.adj[i][j] = G.adj[i][k] + G.adj[k][j];

	for (int i = 0; i < G.vexnum; i++)
		printf("%c:%d\n", 'a' + i, G.adj[startPoint - 'a'][i]);
	return 0;
}

/*
* 思路：基本的Floyd算法，不过这里不需要输出路径，只需要输出最短路径长度。完整的Floyd算法过程如下：
* 1. 初始化：将邻接矩阵G.adj初始化为各边的权值，如果两点之间没有边，则初始化为INT_MAX；将路径矩阵G.path初始化为终点前驱，如果两点之间没有边，则初始化为-1，对角线初始化为-1。
* 2. 三重循环：对于每一个中间点k，对于每一对顶点i和j，如果G.adj[i][k] != INT_MAX && G.adj[k][j] != INT_MAX，并且途径中间点k的路径比直接连接的路径短，就更新路径长度和路径矩阵。这里有个易错点：更新路径矩阵的时候，填入的值不是中间点k，而是path[k][j]，即中间点到终点的路径上终点的前一个点。
* 3. 输出：路径长度很容易输出，但是路径矩阵的输出需要使用递归。
* 时间复杂度：O(n^3)，其中n为顶点数。
*/