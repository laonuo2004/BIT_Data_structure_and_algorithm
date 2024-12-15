#include <bits/stdc++.h>

using namespace std;

typedef vector<int> Vector;
typedef vector<vector<int>> Matrix;

// 计算未配对的运动员的配对上界和
int computeUpperBound(Matrix& p, Matrix& q, Vector& r, int i, int n) {
    int upperBound = 0;
    for (int k = i; k < n; ++k) {
        int maxAdvantage = 0;
        for (int j = 0; j < n; ++j) {
            if (r[j] == -1) { // 避开已配对的运动员
                maxAdvantage = max(maxAdvantage, p[k][j] * q[j][k]);
            }
        }
        upperBound += maxAdvantage;
    }
    return upperBound;
}

void backTrack(Matrix& p, Matrix& q, Vector& r, int i, int n, int sum, int& maxSum, Vector& maxPairing) {
    if (i == n) {
        if (sum > maxSum) {
            maxSum = sum;
            for (int j = 0; j < n; ++j)
                maxPairing[j] = r[j];
        }
        return;
    }

    int upperBound = computeUpperBound(p, q, r, i, n);
    if (sum + upperBound <= maxSum) return; // 剪枝条件

    for (int j = 0; j < n; ++j) {
        if (r[j] == -1) {
            r[j] = i;
            sum += p[i][j] * q[j][i];
            backTrack(p, q, r, i + 1, n, sum, maxSum, maxPairing);
            sum -= p[i][j] * q[j][i];
            r[j] = -1;
        }
    }
}

int main() {
    int n;
    cin >> n;
    Matrix p(n, vector<int>(n)), q(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> p[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> q[i][j];

    Vector r(n, -1), maxPairing(n, -1);
    int maxSum = 0;
    backTrack(p, q, r, 0, n, 0, maxSum, maxPairing);

    cout << maxSum << endl;
    for (int i = 0; i < n; i++)
        cout << i << " " << maxPairing[i] << endl;

    return 0;
}
