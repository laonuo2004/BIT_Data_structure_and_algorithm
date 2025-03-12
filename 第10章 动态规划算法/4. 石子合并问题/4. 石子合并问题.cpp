#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<ll>> stones(2 * n, vector<ll>(2 * n, 0));
	vector<vector<ll>> dp(2 * n, vector<ll>(2 * n, 0));
	for(int i = 1; i < n; i++)
	{
		cin >> stones[i][i];
		stones[i + n][i + n] = stones[i][i];
	}
	cin >> stones[n][n];

	for (int diff = 1; diff <= n - 1; diff++)
	{
		for (int i = 1; i <= 2 * n - 1 - diff; i++)
		{
			int j = i + diff;
			stones[i][j] = stones[i][j - 1] + stones[j][j];
			dp[j][i] = LLONG_MAX;
			for(int k = i; k < j; k++)
			{
				dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + stones[i][j]);
				dp[j][i] = min(dp[j][i], dp[k][i] + dp[j][k + 1] + stones[i][j]);
			}
		}
	}

	ll max = 0, min = LLONG_MAX;
	for (int i = 1; i <= n; i++)
	{
		if(dp[i][i + n - 1] > max)
			max = dp[i][i + n - 1];
		if(dp[i + n - 1][i] < min)
			min = dp[i + n - 1][i];
	}
	cout << min << endl << max << endl;
	return 0;
}

// ---------------------------------------------------

//#include <bits/stdc++.h>
//#define ll long long
//using namespace std;
//
//int main() {
//    int n;
//    cin >> n;
//
//    vector<int> stones(2 * n + 1, 0);
//    vector<vector<ll>> dp_min(2 * n + 1, vector<ll>(2 * n + 1, LLONG_MAX));
//    vector<vector<ll>> dp_max(2 * n + 1, vector<ll>(2 * n + 1, 0));
//
//    // 读取石子数量并扩展到 2n 长度
//    for (int i = 1; i <= n; i++) {
//        cin >> stones[i];
//        stones[i + n] = stones[i]; // 环形扩展
//    }
//
//    // 前缀和计算，快速求子区间和
//    vector<ll> prefix(2 * n + 1, 0);
//    for (int i = 1; i <= 2 * n; i++) {
//        prefix[i] = prefix[i - 1] + stones[i];
//    }
//
//    // 初始化：单堆石子的合并代价为 0
//    for (int i = 1; i <= 2 * n; i++) {
//        dp_min[i][i] = dp_max[i][i] = 0;
//    }
//
//    // 动态规划，枚举区间长度
//    for (int len = 2; len <= n; len++) { // 子区间长度从 2 到 n
//        for (int i = 1; i <= 2 * n - len + 1; i++) {
//            int j = i + len - 1; // 区间右端点
//            ll sum = prefix[j] - prefix[i - 1]; // stones[i] 到 stones[j] 的和
//
//            // 枚举分割点
//            for (int k = i; k < j; k++) {
//                dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k + 1][j] + sum);
//                dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k + 1][j] + sum);
//            }
//        }
//    }
//
//    // 环形处理：取 n 段的最优值
//    ll min_score = LLONG_MAX, max_score = 0;
//    for (int i = 1; i <= n; i++) {
//        min_score = min(min_score, dp_min[i][i + n - 1]);
//        max_score = max(max_score, dp_max[i][i + n - 1]);
//    }
//
//    cout << min_score << endl;
//    cout << max_score << endl;
//
//    return 0;
//}
