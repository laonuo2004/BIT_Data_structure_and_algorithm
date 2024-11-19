#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

typedef char VertexType;

// �ڽӱ�AdjList�ṹ�嶨��
typedef struct ArcNode // �߱���
{
	int adjvex; // �û���ָ��Ķ����λ��
	struct ArcNode* nextarc;
	//int info; // ���ı�Ȩֵ����Ϣ������Ϊ��Ȩͼ����˲���Ҫ
}ArcNode;

typedef struct VNode // �������
{
	VertexType data; // ������Ϣ
	ArcNode* firstarc;
}VNode;

typedef struct // �ڽӱ�
{
	vector<VNode> vertices;
	int vexnum, arcnum; // �������ͻ���
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

	// BFS�Ļ������ã�һ�����к�һ��visited����
	queue<int> Q;
	vector<bool> visited(G.vexnum, false);

	for (int i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i]) // ��ÿ����ͨ�����ĵ�һ���������
			Q.push(i);

		while (!Q.empty()) // һ����ͨ�������BFS
		{
			// ȡ��ǰ������в���
			int v = Q.front();
			Q.pop();
			if (!visited[v])
			{
				cout << G.vertices[v].data;
				visited[v] = true;
			}

			// �����ڽӵ�
			ArcNode* p = G.vertices[v].firstarc;
			while (p)
			{
				if (!visited[p->adjvex]) // ע������Ѿ����ʹ���û��Ҫ�����
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
		p->nextarc = G.vertices[v1].firstarc; // ͷ�巨
		G.vertices[v1].firstarc = p;

		p = new ArcNode; // ����ͼ����������Ҫ��
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
* �ջ�1���ڽӱ�Ļ������壺������߱��Լ������ڽӱ�
* �ջ�2��BFS�Ļ������ã�һ�����к�һ��visited����
* 
* ע��1����������ͼ��ÿ���߶�Ҫ�����Σ��������ڽӱ����ڽӾ���
* ע��2��BFS���Ƚ��ԣ���ԭ����while(!Q.empty())��������һ��ѭ�����Ӷ����Դ�������ͨ�������ڷ���ͨͼ��Ҳͬ�����ã�������BFS���Ƚ���
*/