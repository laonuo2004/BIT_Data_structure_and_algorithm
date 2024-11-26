#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canJump(const vector<int>& nums) {
    int n = nums.size();
    int maxReach = 0; // �ܵ������Զ����

    for (int i = 0; i < n; ++i) {
        if (i > maxReach) { // �����ǰλ�ó����˵�ǰ��Զ���룬����false
            return false;
        }
        maxReach = max(maxReach, i + nums[i]); // ������Զ����
        if (maxReach >= n - 1) { // �����Զ�����Ѿ��������յ㣬ֱ�ӷ���true
            return true;
        }
    }
    return true;
}

int main() {
    vector<int> nums;
    int n, val;
    cin >> n; // �������鳤��
    for (int i = 0; i < n; ++i) {
        cin >> val;
        nums.push_back(val);
    }
    if (canJump(nums)) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    return 0;
}
