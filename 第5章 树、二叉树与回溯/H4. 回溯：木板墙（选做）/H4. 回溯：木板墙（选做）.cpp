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
// 不管怎样修改，都会超时，所以只能用栈来做

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    long long height; // 木板高度
    int width;        // 当前木板的相对跨度
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
                // 弹出更高的木板，计算面积
                Node top = St.top();
                St.pop();
                accumulatedWidth += top.width;
                maxArea = max(maxArea, top.height * accumulatedWidth);
            }
            // 当前木板加入栈
            St.push({ heights[i], accumulatedWidth + 1 });
        }

        // 处理剩余的木板
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
* 思路：单调栈
* 1. 从左到右遍历木板，维护一个单调递增的栈，栈中存放的是木板的高度和宽度
* 2. 如果当前木板的高度小于栈顶木板的高度，则弹出栈顶木板，计算面积
* 3. 计算面积时，宽度是当前木板的宽度加上栈顶木板的宽度
* 4. 最后，处理剩余的木板
*/