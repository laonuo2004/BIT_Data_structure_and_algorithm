#include <iostream>
#include <vector>
using namespace std;

int wiggleMaxLength(vector<int>& nums) {
    if (nums.size() < 2) return nums.size(); // 边界情况：长度小于2

    int prevDiff = 0; // 记录相邻元素之间的差值
    int count = 1;    // 最小序列长度为1

    for (int i = 1; i < nums.size(); ++i) {
        int diff = nums[i] - nums[i - 1]; // 计算当前差值
        if ((diff > 0 && prevDiff <= 0) || (diff < 0 && prevDiff >= 0)) {
            count++;        // 如果差值方向发生变化，计入摆动序列
            prevDiff = diff; // 更新前一个差值
        }
    }

    return count; // 返回摆动序列的长度
}

int main() {
    int n, val;
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        nums.push_back(val);
    }

    cout << wiggleMaxLength(nums) << endl;
    return 0;
}
