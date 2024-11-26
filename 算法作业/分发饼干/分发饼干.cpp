#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m; // n是孩子的数量，m是饼干的数量
    cin >> n >> m;

    vector<int> g(n), s(m); // g存储孩子的胃口值，s存储饼干的尺寸
    for (int i = 0; i < n; ++i) cin >> g[i];
    for (int i = 0; i < m; ++i) cin >> s[i];

    sort(g.begin(), g.end()); // 按胃口值排序
    sort(s.begin(), s.end()); // 按饼干尺寸排序

    int i = 0, j = 0; // 双指针，分别指向孩子和饼干
    int satisfied = 0; // 记录满足的孩子数量

    while (i < n && j < m) {
        if (s[j] >= g[i]) { // 如果当前饼干能满足当前孩子
            ++satisfied;    // 满足孩子数量加一
            ++i;            // 移动到下一个孩子
        }
        ++j; // 无论是否满足孩子，饼干都要用掉
    }

    cout << satisfied << endl; // 输出满足的最大孩子数量

    return 0;
}
