#include <bits/stdc++.h>
#define ll long long

using namespace std;

// 使用递归输出括号表达式
void printStr(int i, int j, vector<vector<int>>& cut)
{
	if (i == j)
	{
		cout << "A" << i;
		return;
	}
	cout << "(";
	printStr(i, cut[i][j], cut);
	printStr(cut[i][j] + 1, j, cut);
	cout << ")";
}

int main()
{
	int n;
	cin >> n;
	if(n == 1) // 特判
	{
		cout << 0 << endl;
		cout << "(A1)" << endl;
		return 0;
	}
	vector<ll> dim(n + 1);
	for(int i = 0; i < n + 1; i++)
		cin >> dim[i];

	vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0)); // 使用右上角区域
	vector<vector<int>> cut(n + 1, vector<int>(n + 1, 0)); // 注意，记录分割位置只需要记录左边界即可
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = 0;
		cut[i][i] = 0;
	}

	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= n - i + 1; j++)
		{
			dp[j][j + i - 1] = LLONG_MAX;
			for (int k = 1; k <= i - 1; k++) // 注意，对于dp[x][y]，其来源有不止两种(左边和下面)！而有y-x种
			{
				ll temp = dp[j][j + k - 1] + dp[j + k][j + i - 1] + dim[j - 1] * dim[j + k - 1] * dim[j + i - 1];
				if (temp < dp[j][j + i - 1])
				{
					dp[j][j + i - 1] = temp;
					cut[j][j + i - 1] = j + k - 1;
				}
			}
		}

	cout << dp[1][n] << endl;
	printStr(1, n, cut);
	cout << endl;
	return 0;
}