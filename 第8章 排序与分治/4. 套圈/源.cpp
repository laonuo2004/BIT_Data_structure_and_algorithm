#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// 定义点结构
struct Point {
    double x, y;
};

// 比较函数，用于按x坐标排序
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// 比较函数，用于按y坐标排序
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 计算两点之间的欧几里得距离
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 计算最近距离，直接暴力计算
double bruteForce(const vector<Point>& points, int left, int right) {
    double minDist = 1e20; // 初始设为无限大
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            minDist = min(minDist, distance(points[i], points[j]));
        }
    }
    return minDist;
}

// 跨中线的点对检查
double stripClosest(const vector<Point>& strip, double d) {
    double minDist = d;
    int n = strip.size();

    // 按y坐标排序
    vector<Point> sortedStrip = strip;
    sort(sortedStrip.begin(), sortedStrip.end(), compareY);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n && (sortedStrip[j].y - sortedStrip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(sortedStrip[i], sortedStrip[j]));
        }
    }

    return minDist;
}

// 分治法求解最近点对距离
double closestPair(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        // 小规模问题直接暴力计算
        return bruteForce(points, left, right);
    }

    int mid = left + (right - left) / 2;
    double midX = points[mid].x;

    // 分别计算左右部分的最近距离
    double dLeft = closestPair(points, left, mid);
    double dRight = closestPair(points, mid + 1, right);
    double d = min(dLeft, dRight);

    // 构造跨中线的点集
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - midX) < d) {
            strip.push_back(points[i]);
        }
    }

    // 检查跨中线的最近距离
    return min(d, stripClosest(strip, d));
}

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        // 按x坐标排序
        sort(points.begin(), points.end(), compareX);

        // 计算最近点对距离
        double minDist = closestPair(points, 0, n - 1);

        // 输出半径
        cout << fixed << setprecision(2) << minDist / 2 << endl;
    }

    return 0;
}
