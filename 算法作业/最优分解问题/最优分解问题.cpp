#include <bits/stdc++.h>
using namespace std;

void writeToFile(const string& filename, int maxProduct) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << maxProduct << endl;
        outfile.close();
    }
    else {
        cerr << "无法打开文件" << filename << endl;
    }
}

pair<int, vector<int>> optimalDecomposition(int n) {
    vector<int> factors; // 存储分解结果
    int product = 1;     // 最大乘积
    int sum = 0;         // 当前因子的总和

    // 贪心分解为尽可能大的互不相同的自然数
    for (int i = 2; sum + i <= n; ++i) {
        factors.push_back(i);
        sum += i;
    }

    // 计算剩余部分
    int remainder = n - sum;

    // 从后向前分配剩余部分
    for (int i = factors.size() - 1; i >= 0 && remainder > 0; --i) {
        factors[i]++;
        remainder--;
    }

    // 如果还剩余一个 1，则分配到最后一个因子上
    if (remainder == 1) {
        factors[factors.size() - 1]++;
    }

    // 计算最大乘积
    for (int factor : factors) {
        product *= factor;
    }

    return { product, factors };
}

int main() {
    int n;
    cin >> n;

    // 贪心算法计算最优分解和最大乘积
    auto result = optimalDecomposition(n);
    int maxProduct = result.first;
    vector<int> factors = result.second;

    // 将最大乘积写入文件
    writeToFile("output.txt", maxProduct);

    // 打印结果（分解方案）
    cout << "最大乘积: " << maxProduct << endl;
    cout << "分解方案: ";
    for (int factor : factors) {
        cout << factor << " ";
    }
    cout << endl;

    return 0;
}
