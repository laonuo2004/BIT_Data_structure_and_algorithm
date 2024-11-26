#include <bits/stdc++.h>

using namespace std;

class UnionFindSet // ���鼯
{
public:
    UnionFindSet(int size) : size(size) // ���캯���������size�ǲ�����ǰ���size�ǳ�Ա��������ʾ��ʼ����Ա����size��ֵΪ����size
    {
        parent.resize(size); // ��resize������ʼ������
        rank.resize(size);
        for (int i = 0; i <= size - 1; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) // ���Һ���
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // ·��ѹ��
        return parent[x];
    }

    void merge(int x, int y) // �ϲ�������ʹ����rank�Ż�
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

    bool check() // ����Ƿ�ֻ��һ������
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
    vector<int> parent; // ֱ��ǰ��
    vector<int> rank;  // �ȣ������Ż�merge������ʹ������ƽ��
};

typedef struct Edge // ��
{
	int u, v, w;
	bool operator<(const Edge& e) const // ����<��������ߵ�Ȩ��ԽС�����ȼ�Խ�ߣ������ȶ����о�Խ��ǰ���Ӷ�ʵ��С���ѡ�����const��ʾ���������޸ĳ�Ա����
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
		if (ufs.find(e.u) != ufs.find(e.v)) // ��������˵��Ѿ���ͬһ�������У�˵�������߻��γɻ���ֱ������
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
* ˼·��Kruskal�㷨��ʹ�ò��鼯�洢�ڵ㣬ʹ�����ȶ���(С����)�洢�ߣ�ÿ��ȡ��Ȩ����С�ıߣ���������˵㲻��ͬһ�������У��ͺϲ����������ϣ��������������ߡ�ʱ�临�Ӷȣ�O(mlogm)��mΪ�ߵ�������
* 
* �ջ�1����Ķ����ʹ�ã���ĳ�Ա�����ͳ�Ա��������Ĺ��캯������Ķ���Ķ����ʹ�á�
* �ջ�2�����鼯ģ�壬ʵ���˹��������ҡ��ϲ�������Ƿ�ֻ��һ�����ϵĻ���������ʹ����·��ѹ�����Ż����Ҳ�����ʹ���������Ż��ϲ�������
* �ջ�3��STL��resize���������ڳ�ʼ��������С�������������ȶ�����ʼ���������
* �ջ�4��STL��priority_queue���ȶ��У����ڴ洢�ߣ�ʵ��С���ѡ�������ԣ��ڱ߽ڵ㵱������<�������ʹ�ñߵ�Ȩ��ԽС�����ȼ�Խ�ߣ��Ӷ�ʵ��С���ѡ�
*/