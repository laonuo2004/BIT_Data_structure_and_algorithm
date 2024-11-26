#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canJump(const vector<int>& nums) {
    int n = nums.size();
    int maxReach = 0; // 能到达的最远距离

    for (int i = 0; i < n; ++i) {
        if (i > maxReach) { // 如果当前位置超出了当前最远距离，返回false
            return false;
        }
        maxReach = max(maxReach, i + nums[i]); // 更新最远距离
        if (maxReach >= n - 1) { // 如果最远距离已经覆盖了终点，直接返回true
            return true;
        }
    }
    return true;
}

int main() {
    vector<int> nums;
    int n, val;
    cin >> n; // 输入数组长度
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
