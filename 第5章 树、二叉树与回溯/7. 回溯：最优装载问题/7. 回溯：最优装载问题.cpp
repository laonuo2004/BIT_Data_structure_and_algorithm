#include <bits/stdc++.h>

using namespace std;

void backTracking(vector<int>& w, vector<bool>& x, vector<bool>& bestx, int cw, int lw, int& bestw, int i, int c, int n)
{
	if (i == n)
		return;

	// 及时更新当前最优解，用于剪枝
	if (cw > bestw)
	{
		bestw = cw;
		bestx = x;
	}

	// 递归搜索左子树
	x[i] = true;
	if (cw + w[i] <= c)
		backTracking(w, x, bestx, cw + w[i], lw - w[i], bestw, i + 1, c, n);

	// 递归搜索右子树
	x[i] = false;
	if (cw + lw - w[i] > bestw)
		backTracking(w, x, bestx, cw, lw - w[i], bestw, i + 1, c, n);

	// 法2：参考《算法设计与分析》P. 129
	//if (i >= n)
	//{
	//	if (cw > bestw)
	//	{
	//		bestw = cw;
	//		bestx = x;
	//	}
	//	return;
	//}

	//lw -= w[i];
	//if (cw + w[i] <= c)
	//{
	//	x[i] = true;
	//	cw += w[i];
	//	backTracking(w, x, bestx, cw, lw, bestw, i + 1, c, n);
	//	cw -= w[i];
	//}
	//if (cw + lw > bestw)
	//{
	//	x[i] = false;
	//	backTracking(w, x, bestx, cw, lw, bestw, i + 1, c, n);
	//}
	//lw += w[i];
}

int main()
{
	int c, n;
	cin >> c >> n;
	vector<int> w(n);
	int lw = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> w[i];
		lw += w[i];
	}
	vector<bool> x(n);
	vector<bool> bestx(n);
	int cw = 0, bestw = 0;
	backTracking(w, x, bestx, cw, lw, bestw, 0, c, n);
	cout << bestw << endl;
	for (int i = 0; i < n; ++i)
		if (bestx[i])
			cout << i + 1 << " ";
	cout << endl;
	return 0;
}

/*
* 错误1：传入的参数比较多，容易漏传。全部参数如下：
* 1. 题目所给参数：w、c、n；
* 2. 简单回溯所要求的参数：x(注意不是引用型，因为每一分支的装货情况是独立的)、i；
* 3. 统计最大装货量所要求的参数：cw、bestw；
* 4. 统计最大装货方案所要求的参数：bestx；
* 5. 用于剪枝的参数：lw，同时记得及时更新bestw、lw；
* 错误2：两处是>=而非>，因为之前已经及时更新了当前最优解，如果用>的话就无法进入函数；
* 错误3：注意先右后左，这样可以保证最优解在左子树中，使最优解表示的二进制数最大；
*/