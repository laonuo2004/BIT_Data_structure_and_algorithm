#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> intervals(n); // 存储区间的左右坐标
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    // 按照区间右端点升序排序
    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
        });

    int count = 0; // 记录可以安排的区间数量
    int end = INT_MIN; // 初始化上一个区间的结束时间

    for (const auto& interval : intervals) {
        if (interval.first >= end) { // 如果当前区间的起点不早于上一个区间的结束时间
            ++count;
            end = interval.second; // 更新上一个区间的结束时间
        }
    }

    cout << n - count << endl; // 输出需要移除的最小区间数量
    return 0;
}
