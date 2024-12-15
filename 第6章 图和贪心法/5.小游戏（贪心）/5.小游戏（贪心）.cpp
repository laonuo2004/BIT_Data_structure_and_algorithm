#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

typedef struct node
{
	int index;
	struct node* next;
}NODE, * PNODE;

typedef vector<NODE> adjList;
typedef vector<int> edgeCount;

typedef struct
{
	adjList list;
	edgeCount count;
}unDirectedTree;

void insertNode(NODE& listHead, int index)
{
	PNODE node = new NODE;
	node->index = index;
	node->next = NULL;
	if (listHead.next == NULL)
		listHead.next = node;
	else
	{
		NODE* p = &listHead;
		while (p->next != NULL)
			p = p->next;
		p->next = node;
	}
}

void deleteNode(NODE& listHead, int index)
{
	NODE* p = &listHead;
	while (p->next != NULL)
	{
		if (p->next->index == index)
		{
			NODE* q = p->next;
			p->next = q->next;
			delete q;
			break;
		}
		p = p->next;
	}
}

void deleteList(NODE& listHead)
{
	NODE* p = listHead.next;
	while (p != NULL)
	{
		NODE* q = p;
		p = p->next;
		delete q;
	}
	listHead.next = NULL;
}

unDirectedTree createUnDirectedTree(int n)
{
	unDirectedTree tree;
	tree.list.resize(n);
	for(int i = 0; i < n; ++i)
		tree.list[i].next = NULL;
	tree.count.resize(n);
	return tree;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		unDirectedTree tree = createUnDirectedTree(n);

		int index, count;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d:(%d)", &index, &count);
			tree.count[index] += count;
			for (int j = 0; j < count; ++j)
			{
				int child;
				scanf(" %d", &child);
				insertNode(tree.list[index], child);
				insertNode(tree.list[child], index);
				tree.count[child]++;
			}
		}

		int soldiers = 0, maxCountVertex = 0;
		for(int i = 0; i < n; ++i)
			if(tree.count[i] > tree.count[maxCountVertex])
				maxCountVertex = i;
		while (tree.count[maxCountVertex] > 0) // ������ӽڵ���ĿΪ0ʱ����ʾ���б߶���ʿ����
		{
			soldiers++;

			// ɾ����
			NODE* p = tree.list[maxCountVertex].next;
			while(p != NULL)
			{
				deleteNode(tree.list[p->index], maxCountVertex);
				tree.count[p->index]--;
				p = p->next;
			}
			deleteList(tree.list[maxCountVertex]);
			tree.count[maxCountVertex] = 0;

			maxCountVertex = 0;
			for(int i = 0; i < n; ++i)
				if(tree.count[i] > tree.count[maxCountVertex])
					maxCountVertex = i;
		}

		cout << soldiers << endl;
	}
	return 0;
}

/*
* ˼·��̰���㷨��ÿ��ѡ���ӽڵ���Ŀ���Ľڵ㣬ɾ�����������ıߣ�ֱ�����б߶���ʿ����
* ����1��֮ǰ���õĲ����Ƕ�Count�������򣬵�������һ��Ѱ��ɾȥ�ıߵ���һ�����ʱ�临�Ӷ�ΪO(n^3)�����һ�Ҫ��Count�����ٴν�������ʱ�临�Ӷ�ΪO(n^2logn)�����������ᳬʱ��
*		��ʵ�ϣ�ÿ����Ҫ��ֻ���ӽڵ���Ŀ���Ľڵ㣬����ֻ��Ҫ����һ��Count���鼴�ɣ�ʱ�临�Ӷ�ΪO(n^2)��
* ����2��֮ǰ�Ĵ����У����õ����ڽӾ��󣬵��������ᳬʱ�����Ը�Ϊ�ڽӱ�
*/

/*---------------------------------------------------------- �ָ��� ----------------------------------------------------------*/

// ����ʵ�����Ǿ������С֧�伯���⣬����һ������ͼ�У��ҵ�һ����С�Ķ��㼯��ʹ��������㼯�еĶ�������ڽӵĶ���Ĳ����������ж���ļ���
// ʹ��̰���㷨���ܻᵼ�¾ֲ����Ž⣬���ԲŻ���ִ𰸴�������
// ��ʵ�ϣ���С֧�伯������һ��NP��ȫ���⣬������Ҫ�������������������һ�־���ķ����Ƕ�̬�滮��GPT�Ĵ������£�(��ϸ�Ľ��Ϳ��Բο�Obsidian��2024-12-15 ���ݽṹ)

//#include <bits/stdc++.h>
//using namespace std;
//
//vector<vector<int>> tree;   // �ڽӱ�洢��
//vector<vector<int>> dp;     // dp[u][0] �� dp[u][1] ��״̬
//vector<bool> visited;       // ��ǽڵ��Ƿ��ѷ��ʣ������ظ�������
//
//void dfs(int u) {
//	visited[u] = true;
//	dp[u][0] = 0; // ��ǰ�ڵ㲻��ʿ��
//	dp[u][1] = 1; // ��ǰ�ڵ��ʿ��
//
//	for (int v : tree[u]) {
//		if (!visited[v]) {
//			dfs(v);
//			dp[u][0] += dp[v][1]; // �ӽڵ�����ʿ��
//			dp[u][1] += min(dp[v][0], dp[v][1]); // �ӽڵ��ѡ�Ż򲻷�
//		}
//	}
//}
//
//int main() {
//	int n;
//	while (cin >> n) {
//		tree.assign(n, vector<int>());
//		dp.assign(n, vector<int>(2, 0));
//		visited.assign(n, false);
//
//		for (int i = 0; i < n; ++i) {
//			int u, k;
//			scanf("%d:(%d)", &u, &k);
//			for (int j = 0; j < k; ++j) {
//				int v;
//				scanf("%d", &v);
//				tree[u].push_back(v);
//				tree[v].push_back(u);
//			}
//		}
//
//		// �����Խڵ�0Ϊ����������ͨ�ģ�����ڵ㶼�����Ǹ���
//		dfs(0);
//
//		// ������
//		cout << min(dp[0][0], dp[0][1]) << endl;
//	}
//
//	return 0;
//}
