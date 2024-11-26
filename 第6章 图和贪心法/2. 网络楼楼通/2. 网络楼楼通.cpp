#include <bits/stdc++.h>

using namespace std;

class UnionFindSet // 并查集
{
public:
    UnionFindSet(int size) : size(size) // 构造函数，后面的size是参数，前面的size是成员变量，表示初始化成员变量size的值为参数size
    {
        parent.resize(size); // 用resize函数初始化数组
        rank.resize(size);
        for (int i = 0; i <= size - 1; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) // 查找函数
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // 路径压缩
        return parent[x];
    }

    void merge(int x, int y) // 合并函数，使用了rank优化
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool check() // 检查是否只有一个集合
	{
		int cnt = 0;
		for (int i = 1; i <= size - 1; i++)
		{
			if (parent[i] == i)
				cnt++;
			if (cnt > 1)
				return false;
		}
		return true;
	}

private:
    int size;
    vector<int> parent; // 直接前驱
    vector<int> rank;  // 秩，用于优化merge操作，使树尽量平衡
};

typedef struct Edge // 边
{
	int u, v, w;
	bool operator<(const Edge& e) const // 重载<运算符，边的权重越小，优先级越高，在优先队列中就越靠前，从而实现小根堆。最后的const表示函数不会修改成员变量
	{
		return w > e.w;
	}
}Edge;

int main()
{
	int n, m;
	cin >> n >> m;
    UnionFindSet ufs(n + 1);
    priority_queue<Edge> pq;
    for (int i = 0; i < m; i++)
	{
		Edge e;
		cin >> e.u >> e.v >> e.w;
		pq.push(e);
	}

    int ans = 0;
    while (!pq.empty())
	{
		Edge e = pq.top();
		pq.pop();
		if (ufs.find(e.u) != ufs.find(e.v)) // 如果两个端点已经在同一个集合中，说明这条边会形成环，直接跳过
		{
			ufs.merge(e.u, e.v);
            ans += e.w;
		}
	}
    if(!ufs.check())
        cout << -1 << endl;
    else
        cout << ans << endl;
	return 0;
}

/*
* 思路：Kruskal算法，使用并查集存储节点，使用优先队列(小根堆)存储边，每次取出权重最小的边，如果两个端点不在同一个集合中，就合并这两个集合，否则跳过这条边。时间复杂度：O(mlogm)，m为边的数量。
* 
* 收获1：类的定义和使用，类的成员变量和成员函数，类的构造函数，类的对象的定义和使用。
* 收获2：并查集模板，实现了构建、查找、合并、检查是否只有一个集合的基本操作，使用了路径压缩来优化查找操作，使用了秩来优化合并操作。
* 收获3：STL的resize函数，用于初始化容器大小，适用于这种先定义后初始化的情况。
* 收获4：STL的priority_queue优先队列，用于存储边，实现小根堆。具体而言，在边节点当中重载<运算符，使得边的权重越小，优先级越高，从而实现小根堆。
*/