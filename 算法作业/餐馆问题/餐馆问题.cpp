#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Customer {
    int people; // ������
    int money;  // Ԥ�����ѽ��
};

bool cmp(const Customer& a, const Customer& b) {
    return a.money > b.money; // �����ѽ��Ӵ�С����
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> tables(n); // ��������
    for (int i = 0; i < n; ++i) {
        cin >> tables[i];
    }

    vector<Customer> customers(m); // ������Ϣ
    for (int i = 0; i < m; ++i) {
        cin >> customers[i].people >> customers[i].money;
    }

    // ������������С��������
    sort(tables.begin(), tables.end());
    // ���������ѽ��Ӵ�С����
    sort(customers.begin(), customers.end(), cmp);

    multiset<int> availableTables(tables.begin(), tables.end()); // ʹ��multiset�洢����������֧�ָ�Ч����

    int totalMoney = 0;
    for (const auto& customer : customers) {
        // ���ҵ�һ�������ɸÿ��˵�����
        auto it = availableTables.lower_bound(customer.people);
        if (it != availableTables.end()) { // �ҵ���������
            totalMoney += customer.money;  // �������ѽ��
            availableTables.erase(it);    // �Ƴ���ʹ�õ�����
        }
    }

    cout << totalMoney << endl;
    return 0;
}
