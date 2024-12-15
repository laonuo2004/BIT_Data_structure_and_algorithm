#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

typedef struct vertex
{
	string name;
	int indegree, outdegree;
	int earliest, latest;
}VERTEX;

vector<VERTEX> vertices; // ��¼������Ϣ

typedef struct adjNode
{
	int index;
	int weight;
	struct adjNode* next;
}NODE, * PNODE;

vector<NODE> adjList; // ���������翪ʼʱ��
vector<NODE> reverseAdjList; // ���ڽӱ�����������ʼʱ��

//void insertNode(NODE& listHead, int index, int weight)
//{
//	PNODE node = new NODE;
//	node->index = index;
//	node->weight = weight;
//	node->next = NULL;
//	if (listHead.next == NULL)
//		listHead.next = node;
//	else
//	{
//		PNODE p = &listHead;
//		while (p->next != NULL)
//			p = p->next;
//		p->next = node;
//	}
//}

void insertNode(NODE& listHead, int index, int weight)
{
	PNODE node = new NODE;
	node->index = index;
	node->weight = weight;
	node->next = NULL;
	if (listHead.next == NULL)
		listHead.next = node;
	else
	{
		PNODE p = &listHead;
		while (p->next != NULL && p->next->index < index)
			p = p->next;
		node->next = p->next;
		p->next = node;
	}
}

// DFS����ؼ�·��
void DFS(int index, vector<int>& path)
{
	if (vertices[index].earliest == vertices[index].latest)
	{
		path.push_back(index);
		if (vertices[index].outdegree == 0)
		{
			int i = 0;
			for (; i < path.size() - 1; i++)
				cout << vertices[path[i]].name << "-";
			cout << vertices[path[i]].name << endl;
		}
		else
		{
			PNODE p = adjList[index].next;
			while (p != NULL)
			{
				DFS(p->index, path);
				p = p->next;
			}
		}
		path.pop_back();
	}
}

int main()
{
	int vertexCount, edgeCount;
	scanf("%d,%d", &vertexCount, &edgeCount);
	vertices.resize(vertexCount);
	adjList.resize(vertexCount);
	reverseAdjList.resize(vertexCount);

	// ¼�붥����Ϣ
	string nameString;
	cin >> nameString;
	for (int i = 0, last = 0, current = 0; i < vertexCount; i++)
	{
		string name;
		current = nameString.find(',', last);
		if (current == string::npos)
			name = nameString.substr(last);
		else
			name = nameString.substr(last, current - last);
		last = current + 1;
		vertices[i].name = name;
		vertices[i].indegree = vertices[i].outdegree = 0;
		vertices[i].earliest = 0;
		vertices[i].latest = INT_MAX;
	}

	// ¼��ߵ���Ϣ
	string edgeString;
	cin >> edgeString;
	for (int i = 0, last = 0, current = 0; i < edgeCount; i++)
	{
		int from, to, weight;
		string edge;
		current = edgeString.find('>', last) + 1;
		edge = edgeString.substr(last, current - last);
		sscanf(edge.c_str(), "<%d,%d,%d>", &from, &to, &weight);
		last = current + 1;
		insertNode(adjList[from], to, weight);
		insertNode(reverseAdjList[to], from, weight);
		vertices[from].outdegree++;
		vertices[to].indegree++;
	}

	// �����翪ʼʱ�䣬ͬʱ����������У����ȶ��У���indexС�Ķ������ȼ���
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 0; i < vertexCount; i++)
		if (vertices[i].indegree == 0)
			q.push(i);
	if (q.empty() || q.size() > 1)
	{
		cout << "NO TOPOLOGICAL PATH" << endl;
		return 0;
	}
	vector<int> topoSeq;
	while (!q.empty())
	{
		int index = q.top();
		q.pop();
		topoSeq.push_back(index);
		PNODE p = adjList[index].next;
		while (p != NULL)
		{
			vertices[p->index].earliest = max(vertices[p->index].earliest, vertices[index].earliest + p->weight);
			if (--vertices[p->index].indegree == 0)
				q.push(p->index);
			p = p->next;
		}
	}
	if (topoSeq.size() < vertexCount)
	{
		cout << "NO TOPOLOGICAL PATH" << endl;
		return 0;
	}

	// ������ȣ����ڻָ�
	vector<int> outdegree(vertexCount);
	for (int i = 0; i < vertexCount; i++)
		outdegree[i] = vertices[i].outdegree;

	// ������ʼʱ��
	vertices[vertexCount - 1].latest = vertices[vertexCount - 1].earliest;
	for (int i = 0; i < vertexCount; i++)
		if (vertices[i].outdegree == 0)
			q.push(i);
	while (!q.empty())
	{
		int index = q.top();
		q.pop();
		PNODE p = reverseAdjList[index].next;
		while (p != NULL)
		{
			vertices[p->index].latest = min(vertices[p->index].latest, vertices[index].latest - p->weight);
			if (--vertices[p->index].outdegree == 0)
				q.push(p->index);
			p = p->next;
		}
	}

	// �ָ�����
	for (int i = 0; i < vertexCount; i++)
		vertices[i].outdegree = outdegree[i];

	// �����������
	int i = 0;
	for (; i < topoSeq.size() - 1; i++)
		cout << vertices[topoSeq[i]].name << "-";
	cout << vertices[topoSeq[i]].name << endl;

	// ʹ��DFS����ؼ�·��
	vector<int> path;
	DFS(0, path);

	return 0;
}