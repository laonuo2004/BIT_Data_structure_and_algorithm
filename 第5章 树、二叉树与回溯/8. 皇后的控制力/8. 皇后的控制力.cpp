#include <bits/stdc++.h>

using namespace std;

int ans = 0;

bool check(int n, int x, int y, vector<bool>& occupiedRows, vector<bool>& occupiedCols, vector<bool>& occupiedLeftDiagonals, vector<bool>& occupiedRightDiagonals)
{
	if (occupiedRows[x] || occupiedCols[y] || occupiedLeftDiagonals[x + y - 1] || occupiedRightDiagonals[x - y + n])
		return false;
	return true;
}

void queen(int n, int m, int diff, vector<int>& emptyRows, vector<int>& everyQueen, vector<bool>& occupiedRows, vector<bool>& occupiedCols, vector<bool>& occupiedLeftDiagonals, vector<bool>& occupiedRightDiagonals, int currentRow, int currentQueen)
{
	if (currentRow > n)
	{
		// 检查是否控制全部区域，即diff个空行与空列是否被控制
		vector<int> emptyCols(diff + 1, 0);
		for(int j = 1; j <= n; ++j)
			if(!occupiedCols[j])
				emptyCols[++emptyCols[0]] = j; // 很巧妙地不用另设变量实现下标的累加，同时还能记录元素个数
		for (int j = 1; j <= diff; ++j)
			occupiedRows[emptyRows[j]] = false;
		bool flag = true;
		// 检查空行是否被控制
		for(int j = 1; j <= diff; ++j)
			for(int k = 1; k <= n; ++k)
				if(check(n, emptyRows[j], k, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
				{
					flag = false;
					goto p; // goto直接跳出多重循环，而且只需要设置一个出口
				}
		// 检查空列是否被控制
		for(int j = 1; j <= diff; ++j)
			for(int k = 1; k <= n; ++k)
				if(check(n, k, emptyCols[j], occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
				{
					flag = false;
					goto p;
				}
		if (flag)
			++ans;
	p:
		// 恢复现场！要记得这是DFS，所以变量后面还会用到的
		for (int j = 1; j <= diff; ++j)
			occupiedRows[emptyRows[j]] = true;
		return;
	}

	// 遇到提前设置的空行，直接跳过
	if(occupiedRows[currentRow])
		queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, currentRow + 1, currentQueen);

	for (int j = 1; j <= n; ++j)
	{
		if (check(n, currentRow, j, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
		{
			everyQueen[currentQueen] = j;
			occupiedRows[currentRow] = true;
			occupiedCols[j] = true;
			occupiedLeftDiagonals[currentRow + j - 1] = true;
			occupiedRightDiagonals[currentRow - j + n] = true;
			queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, currentRow + 1, currentQueen + 1);
			// 记得回溯！
			occupiedRows[currentRow] = false;
			occupiedCols[j] = false;
			occupiedLeftDiagonals[currentRow + j - 1] = false;
			occupiedRightDiagonals[currentRow - j + n] = false;
		}
	}
}

void combination(int n, int m, int diff, vector<int> emptyRows, int t)
{
	if (t > diff)
	{
		// 调用皇后函数
		vector<int> everyQueen(m + 1, 0);
		vector<bool> occupiedRows(n + 1, false), occupiedCols(n + 1, false), occupiedLeftDiagonals(2 * n, false), occupiedRightDiagonals(2 * n, false);
		for (int i = 1; i <= diff; ++i)
			occupiedRows[emptyRows[i]] = true;
		queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, 1, 1);

		//// 测试输出emptyRows
		//for(int i = 1; i <= diff; ++i)
		//	cout << emptyRows[i] << " ";
		//cout << endl;
		return;
	}

	for (int i = emptyRows[t - 1] + 1; i <= n - diff + t; ++i)
	{
		emptyRows[t] = i;
		combination(n, m, diff, emptyRows, t + 1);
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	int diff = n - m;
	vector<int> emptyRows(diff + 1, 0);
	combination(n, m, diff, emptyRows, 1);
	cout << ans << endl;
	return 0;
}

/*
* 思路：相比于原来的N皇后问题，由于少了diff个皇后，因此会少diff行与diff列，于是我们可以通过排列组合，先确定diff个空行，然后再在会被occupy的行上进行N皇后问题的求解。即便是最坏情况下，时间增长为原来的10C5=252倍，也是可以接受的。
* 求解完成后，我们需要检查所有的空行与空列(指对应行/列上没有皇后)是否都被控制，如果被控制了，说明是可以的，++ans。
* 
* 收获1：使用goto语句可以在多重循环中直接跳出，而不需要使用flag标志位；同时好处是只需要设置一个出口即可。
* 收获2：使用递归实现排列组合，实际上是构建了一颗递归树，每一层代表一个空行，每个节点代表一个空行的选择，最后一层代表所有空行的选择完成，然后进行N皇后问题的求解。
* 收获3：相比于使用绝对值来判断对角线被占用，我们可以使用两个数组occupiedLeftDiagonals、occupiedRightDiagonals来记录各对角线占用情况。其中LeftDiagonals的下标为x+y-1，从左上到右下；RightDiagonals的下标为x-y+n，从右上到左下。数组大小均为2n(0~2n-1)。
* 
* 注意1：使用递归回溯时，要记得复原现场！本题中需要复原现场的地方集中在queen函数中：
* 1. 放置皇后过程当中的复原现场；
* 2. 判断是否全部控制的时候，暂时性地修改了occupiedRows的值，是为了方便调用check函数；使用完毕后，需要复原现场。
*/