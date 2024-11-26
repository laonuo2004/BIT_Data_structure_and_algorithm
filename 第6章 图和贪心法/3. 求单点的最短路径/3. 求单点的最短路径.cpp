#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> adjMatrix;

typedef struct {
	adjMatrix adj; // �ڽӾ���
	//adjMatrix path; // ���·�����������ⲻ��Ҫ
	int vexnum, arcnum; // �������ͻ���
} Floyd;

Floyd G;

int main()
{
	char startPoint; // ָ����ĳ�㿪ʼ
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
		getchar(); // ���ջس�
		scanf("<%c,%c,%d>", &u, &v, &w);
		G.adj[u - 'a'][v - 'a'] = w;
	}

	// Floyd���Ĳ���
	for(int k = 0; k < G.vexnum; k++) // �м��
		for(int i = 0; i < G.vexnum; i++) // ���
			for(int j = 0; j < G.vexnum; j++) // �յ�
				if(G.adj[i][k] != INT_MAX && G.adj[k][j] != INT_MAX && G.adj[i][j] > G.adj[i][k] + G.adj[k][j]) // ��������м��k��·����ֱ�����ӵ�·���̣��͸��¡�ǰ�������жϿ��Է�ֹ���
					G.adj[i][j] = G.adj[i][k] + G.adj[k][j];

	for (int i = 0; i < G.vexnum; i++)
		printf("%c:%d\n", 'a' + i, G.adj[startPoint - 'a'][i]);
	return 0;
}

/*
* ˼·��������Floyd�㷨���������ﲻ��Ҫ���·����ֻ��Ҫ������·�����ȡ�������Floyd�㷨�������£�
* 1. ��ʼ�������ڽӾ���G.adj��ʼ��Ϊ���ߵ�Ȩֵ���������֮��û�бߣ����ʼ��ΪINT_MAX����·������G.path��ʼ��Ϊ�յ�ǰ�����������֮��û�бߣ����ʼ��Ϊ-1���Խ��߳�ʼ��Ϊ-1��
* 2. ����ѭ��������ÿһ���м��k������ÿһ�Զ���i��j�����G.adj[i][k] != INT_MAX && G.adj[k][j] != INT_MAX������;���м��k��·����ֱ�����ӵ�·���̣��͸���·�����Ⱥ�·�����������и��״�㣺����·�������ʱ�������ֵ�����м��k������path[k][j]�����м�㵽�յ��·�����յ��ǰһ���㡣
* 3. �����·�����Ⱥ��������������·������������Ҫʹ�õݹ顣
* ʱ�临�Ӷȣ�O(n^3)������nΪ��������
*/