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
		while (tree.count[maxCountVertex] > 0) // 当最大子节点数目为0时，表示所有边都有士兵看
		{
			soldiers++;

			// 删除边
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
* 思路：贪心算法，每次选择子节点数目最多的节点，删除与其相连的边，直到所有边都有士兵看
* 错误1：之前采用的策略是对Count数组排序，但是这样一来寻找删去的边的另一顶点的时间复杂度为O(n^3)，而且还要对Count数组再次进行排序，时间复杂度为O(n^2logn)，所以这样会超时；
*		事实上，每次需要的只是子节点数目最多的节点，所以只需要遍历一次Count数组即可，时间复杂度为O(n^2)；
* 错误2：之前的代码中，采用的是邻接矩阵，但是这样会超时，所以改为邻接表；
*/

/*---------------------------------------------------------- 分割线 ----------------------------------------------------------*/

// 本题实质上是经典的最小支配集问题，即在一个无向图中，找到一个最小的顶点集，使得这个顶点集中的顶点和其邻接的顶点的并集等于所有顶点的集合
// 使用贪心算法可能会导致局部最优解，所以才会出现答案错误的情况
// 事实上，最小支配集问题是一个NP完全问题，所以需要采用其他方法来解决。一种经典的方法是动态规划，GPT的代码如下：(详细的解释可以参考Obsidian的2024-12-15 数据结构)

//#include <bits/stdc++.h>
//using namespace std;
//
//vector<vector<int>> tree;   // 邻接表存储树
//vector<vector<int>> dp;     // dp[u][0] 和 dp[u][1] 的状态
//vector<bool> visited;       // 标记节点是否已访问（避免重复遍历）
//
//void dfs(int u) {
//	visited[u] = true;
//	dp[u][0] = 0; // 当前节点不放士兵
//	dp[u][1] = 1; // 当前节点放士兵
//
//	for (int v : tree[u]) {
//		if (!visited[v]) {
//			dfs(v);
//			dp[u][0] += dp[v][1]; // 子节点必须放士兵
//			dp[u][1] += min(dp[v][0], dp[v][1]); // 子节点可选放或不放
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
//		// 假设以节点0为根（树是连通的，任意节点都可以是根）
//		dfs(0);
//
//		// 输出结果
//		cout << min(dp[0][0], dp[0][1]) << endl;
//	}
//
//	return 0;
//}
