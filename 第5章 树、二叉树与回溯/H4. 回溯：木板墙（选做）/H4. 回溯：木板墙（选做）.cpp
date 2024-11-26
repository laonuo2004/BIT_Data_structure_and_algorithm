//#include <bits/stdc++.h>
//#define ll long long
//using namespace std;
//
//void backTrack(vector<ll>& height, int i, int startPos, ll heightMin, ll& maxArea)
//{
//	if (i == height.size())
//	{
//		ll area = (height.size() - startPos) * heightMin;
//		maxArea = max(maxArea, area);
//		return;
//	}
//
//	if (height[i] < heightMin)
//	{
//		ll area = (i - startPos) * heightMin;
//		maxArea = max(maxArea, area);
//		backTrack(height, i + 1, startPos, height[i], maxArea);
//	}
//	else
//	{
//		if(height[i] > heightMin)
//			backTrack(height, i + 1, i, height[i], maxArea);
//		backTrack(height, i + 1, startPos, heightMin, maxArea);
//	}
//}
//
//int main()
//{
//	int n;
//	while (cin >> n, n)
//	{
//		ll temp, maxArea = 0;
//		vector<ll> height;
//		while (n--)
//		{
//			cin >> temp;
//			if(temp)
//				height.push_back(temp);
//			else
//			{
//				if(height.empty())
//					continue;
//				backTrack(height, 0, 0, height[0], maxArea);
//				height.clear();
//			}
//		}
//		if(!height.empty())
//			backTrack(height, 0, 0, height[0], maxArea);
//		cout << maxArea << endl;
//	}
//	return 0;
//}
//
// ���������޸ģ����ᳬʱ������ֻ����ջ����

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    long long height; // ľ��߶�
    int width;        // ��ǰľ�����Կ��
};

int main() {
    int n;
    while (cin >> n && n) {
        vector<long long> heights(n);
        for (int i = 0; i < n; ++i) {
            cin >> heights[i];
        }

        stack<Node> St;
        long long maxArea = 0;

        for (int i = 0; i < n; ++i) {
            int accumulatedWidth = 0;
            while (!St.empty() && St.top().height > heights[i]) {
                // �������ߵ�ľ�壬�������
                Node top = St.top();
                St.pop();
                accumulatedWidth += top.width;
                maxArea = max(maxArea, top.height * accumulatedWidth);
            }
            // ��ǰľ�����ջ
            St.push({ heights[i], accumulatedWidth + 1 });
        }

        // ����ʣ���ľ��
        int accumulatedWidth = 0;
        while (!St.empty()) {
            Node top = St.top();
            St.pop();
            accumulatedWidth += top.width;
            maxArea = max(maxArea, top.height * accumulatedWidth);
        }

        cout << maxArea << endl;
    }

    return 0;
}

/*
* ˼·������ջ
* 1. �����ұ���ľ�壬ά��һ������������ջ��ջ�д�ŵ���ľ��ĸ߶ȺͿ��
* 2. �����ǰľ��ĸ߶�С��ջ��ľ��ĸ߶ȣ��򵯳�ջ��ľ�壬�������
* 3. �������ʱ������ǵ�ǰľ��Ŀ�ȼ���ջ��ľ��Ŀ��
* 4. ��󣬴���ʣ���ľ��
*/