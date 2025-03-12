#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// �����ṹ
struct Point {
    double x, y;
};

// �ȽϺ��������ڰ�x��������
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// �ȽϺ��������ڰ�y��������
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// ��������֮���ŷ����þ���
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// ����������룬ֱ�ӱ�������
double bruteForce(const vector<Point>& points, int left, int right) {
    double minDist = 1e20; // ��ʼ��Ϊ���޴�
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            minDist = min(minDist, distance(points[i], points[j]));
        }
    }
    return minDist;
}

// �����ߵĵ�Լ��
double stripClosest(const vector<Point>& strip, double d) {
    double minDist = d;
    int n = strip.size();

    // ��y��������
    vector<Point> sortedStrip = strip;
    sort(sortedStrip.begin(), sortedStrip.end(), compareY);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n && (sortedStrip[j].y - sortedStrip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(sortedStrip[i], sortedStrip[j]));
        }
    }

    return minDist;
}

// ���η���������Ծ���
double closestPair(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        // С��ģ����ֱ�ӱ�������
        return bruteForce(points, left, right);
    }

    int mid = left + (right - left) / 2;
    double midX = points[mid].x;

    // �ֱ�������Ҳ��ֵ��������
    double dLeft = closestPair(points, left, mid);
    double dRight = closestPair(points, mid + 1, right);
    double d = min(dLeft, dRight);

    // ��������ߵĵ㼯
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - midX) < d) {
            strip.push_back(points[i]);
        }
    }

    // �������ߵ��������
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

        // ��x��������
        sort(points.begin(), points.end(), compareX);

        // ���������Ծ���
        double minDist = closestPair(points, 0, n - 1);

        // ����뾶
        cout << fixed << setprecision(2) << minDist / 2 << endl;
    }

    return 0;
}
