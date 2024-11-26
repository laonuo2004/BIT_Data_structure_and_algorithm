#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m; // n�Ǻ��ӵ�������m�Ǳ��ɵ�����
    cin >> n >> m;

    vector<int> g(n), s(m); // g�洢���ӵ�θ��ֵ��s�洢���ɵĳߴ�
    for (int i = 0; i < n; ++i) cin >> g[i];
    for (int i = 0; i < m; ++i) cin >> s[i];

    sort(g.begin(), g.end()); // ��θ��ֵ����
    sort(s.begin(), s.end()); // �����ɳߴ�����

    int i = 0, j = 0; // ˫ָ�룬�ֱ�ָ���Ӻͱ���
    int satisfied = 0; // ��¼����ĺ�������

    while (i < n && j < m) {
        if (s[j] >= g[i]) { // �����ǰ���������㵱ǰ����
            ++satisfied;    // ���㺢��������һ
            ++i;            // �ƶ�����һ������
        }
        ++j; // �����Ƿ����㺢�ӣ����ɶ�Ҫ�õ�
    }

    cout << satisfied << endl; // �����������������

    return 0;
}
