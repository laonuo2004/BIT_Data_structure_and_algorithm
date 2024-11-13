#include <iostream>
#include <queue>
#include <stack>
#define MAXN 100
using namespace std;

typedef struct node
{
	bool visited;
	int last_x, last_y;
}NODE, *PNODE;

bool map[MAXN + 1][MAXN + 1];
NODE record[MAXN + 1][MAXN + 1];
const int dirs[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

void bfs(int, int);
void outputPath(int, int);

int main()
{
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			cin >> map[i][j];
	bfs(n, m);
	return 0;
}

void bfs(int n, int m)
{
	record[1][1].visited = true;
	queue<pair<int, int>> q;
	q.push(make_pair(1, 1));
	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();
		int x = p.first, y = p.second;
		if (x == n && y == m)
		{
			outputPath(n, m);
			return;
		}
		for (int i = 0; i < 4; ++i)
		{
			int new_x = x + dirs[i][0], new_y = y + dirs[i][1];
			if (new_x >= 1 && new_x <= n && new_y >= 1 && new_y <= m && !record[new_x][new_y].visited && !map[new_x][new_y])
			{
				record[new_x][new_y].visited = true;
				record[new_x][new_y].last_x = x;
				record[new_x][new_y].last_y = y;
				q.push(make_pair(new_x, new_y));
			}
		}
	}
	cout << "There is no solution!" << endl;
	return;
}

void outputPath(int n, int m)
{
	stack<pair<int, int>> s;
	int x = n, y = m;
	while (x != 1 || y != 1)
	{
		s.push(make_pair(x, y));
		int temp_x = record[x][y].last_x;
		y = record[x][y].last_y;
		x = temp_x;
	}
	s.push(make_pair(1, 1));
	while (!s.empty())
	{
		pair<int, int> temp = s.top();
		s.pop();
		cout << "<" << temp.first << "," << temp.second << ">" << " ";
	}
	cout << endl;
	return;
}

/*
* 思路：使用BFS搜索最短路径。
* 为了记录路径，在原来的record数组中增加了两个成员变量：last_x和last_y，用于记录当前位置的上一个位置。
* 为了输出路径，使用一个栈s，将路径上的点依次压入栈中，最后依次弹出即可。
* 收获1：STL中的queue的基本使用：
* q.push(x);      //入队，将元素 x 从队尾插入（尾插法）
* q.pop();        //出队，删除对首元素，并返回其值
* q.size();       //返回队中元素个数
* q.front();      //返回对首元素
* q.back();       //返回队尾元素
* q.empty();      //判断是否为空（空返回 1，非空返回 0）
* 收获2：pair、make_pair()用于构造pair对象
*/