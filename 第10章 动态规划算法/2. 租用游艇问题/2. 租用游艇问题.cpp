#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> r(n, vector<int>(n));
	for(int i = 0; i < n - 1; ++i)
		for(int j = i + 1; j < n; ++j)
			cin >> r[i][j];
	vector<vector<int>> dp(n, vector<int>(n));
	for(int i = 1; i < n; ++i)
		dp[0][i] = r[0][i];
	for(int i = 1; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			dp[i][j] = min(dp[i - 1][j], dp[i -1][i] + r[i][j]);
	cout << dp[n - 2][n - 1] << endl;
	return 0;
}