#include <bits/stdc++.h>
using namespace std;

void writeToFile(const string& filename, int maxProduct) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << maxProduct << endl;
        outfile.close();
    }
    else {
        cerr << "�޷����ļ�" << filename << endl;
    }
}

pair<int, vector<int>> optimalDecomposition(int n) {
    vector<int> factors; // �洢�ֽ���
    int product = 1;     // ���˻�
    int sum = 0;         // ��ǰ���ӵ��ܺ�

    // ̰�ķֽ�Ϊ�����ܴ�Ļ�����ͬ����Ȼ��
    for (int i = 2; sum + i <= n; ++i) {
        factors.push_back(i);
        sum += i;
    }

    // ����ʣ�ಿ��
    int remainder = n - sum;

    // �Ӻ���ǰ����ʣ�ಿ��
    for (int i = factors.size() - 1; i >= 0 && remainder > 0; --i) {
        factors[i]++;
        remainder--;
    }

    // �����ʣ��һ�� 1������䵽���һ��������
    if (remainder == 1) {
        factors[factors.size() - 1]++;
    }

    // �������˻�
    for (int factor : factors) {
        product *= factor;
    }

    return { product, factors };
}

int main() {
    int n;
    cin >> n;

    // ̰���㷨�������ŷֽ�����˻�
    auto result = optimalDecomposition(n);
    int maxProduct = result.first;
    vector<int> factors = result.second;

    // �����˻�д���ļ�
    writeToFile("output.txt", maxProduct);

    // ��ӡ������ֽⷽ����
    cout << "���˻�: " << maxProduct << endl;
    cout << "�ֽⷽ��: ";
    for (int factor : factors) {
        cout << factor << " ";
    }
    cout << endl;

    return 0;
}
