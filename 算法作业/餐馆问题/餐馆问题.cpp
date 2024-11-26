#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Customer {
    int people; // 客人数
    int money;  // 预计消费金额
};

bool cmp(const Customer& a, const Customer& b) {
    return a.money > b.money; // 按消费金额从大到小排序
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> tables(n); // 桌子容量
    for (int i = 0; i < n; ++i) {
        cin >> tables[i];
    }

    vector<Customer> customers(m); // 客人信息
    for (int i = 0; i < m; ++i) {
        cin >> customers[i].people >> customers[i].money;
    }

    // 按桌子容量从小到大排序
    sort(tables.begin(), tables.end());
    // 按客人消费金额从大到小排序
    sort(customers.begin(), customers.end(), cmp);

    multiset<int> availableTables(tables.begin(), tables.end()); // 使用multiset存储桌子容量，支持高效查找

    int totalMoney = 0;
    for (const auto& customer : customers) {
        // 查找第一个能容纳该客人的桌子
        auto it = availableTables.lower_bound(customer.people);
        if (it != availableTables.end()) { // 找到合适桌子
            totalMoney += customer.money;  // 增加消费金额
            availableTables.erase(it);    // 移除已使用的桌子
        }
    }

    cout << totalMoney << endl;
    return 0;
}
