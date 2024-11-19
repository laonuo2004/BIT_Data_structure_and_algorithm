#include <bits/stdc++.h>

using namespace std;

typedef vector<bool> Vector;
typedef vector<vector<int>> Matrix;

void backTrack(Matrix &p, Matrix &q, Vector &r, int i, int &n, int sum, int &maxSum)
{
	if (i == n)
	{
		if (sum > maxSum)
			maxSum = sum;
		return;
	}
	for (int j = 0; j < n; ++j)
	{
		if (!r[j])
		{
			r[j] = true;
			sum += p[i][j] * q[j][i];
			backTrack(p, q, r, i + 1, n, sum, maxSum);
			sum -= p[i][j] * q[j][i];
			r[j] = false;
		}
	}
}

int main()
{
	int n;
	cin >> n;
	Matrix p(n, vector<int>(n)), q(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> p[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> q[i][j];
	Vector r(n);
	int maxsum = 0;
	backTrack(p, q, r, 0, n, 0, maxsum);
	cout << maxsum << endl;
	return 0;
}