#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> intervals(n); // �洢�������������
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    // ���������Ҷ˵���������
    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
        });

    int count = 0; // ��¼���԰��ŵ���������
    int end = INT_MIN; // ��ʼ����һ������Ľ���ʱ��

    for (const auto& interval : intervals) {
        if (interval.first >= end) { // �����ǰ�������㲻������һ������Ľ���ʱ��
            ++count;
            end = interval.second; // ������һ������Ľ���ʱ��
        }
    }

    cout << n - count << endl; // �����Ҫ�Ƴ�����С��������
    return 0;
}
