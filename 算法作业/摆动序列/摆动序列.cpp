#include <iostream>
#include <vector>
using namespace std;

int wiggleMaxLength(vector<int>& nums) {
    if (nums.size() < 2) return nums.size(); // �߽����������С��2

    int prevDiff = 0; // ��¼����Ԫ��֮��Ĳ�ֵ
    int count = 1;    // ��С���г���Ϊ1

    for (int i = 1; i < nums.size(); ++i) {
        int diff = nums[i] - nums[i - 1]; // ���㵱ǰ��ֵ
        if ((diff > 0 && prevDiff <= 0) || (diff < 0 && prevDiff >= 0)) {
            count++;        // �����ֵ�������仯������ڶ�����
            prevDiff = diff; // ����ǰһ����ֵ
        }
    }

    return count; // ���ذڶ����еĳ���
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
