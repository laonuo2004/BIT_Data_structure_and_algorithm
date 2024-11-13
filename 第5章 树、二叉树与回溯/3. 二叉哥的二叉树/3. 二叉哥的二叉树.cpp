#include <bits/stdc++.h>

using namespace std;

//// 回溯法求解第m层最大节点数
//void maxNumBacktracking(ll n, ll m, ll& maxNum, ll curNum, ll curSum, ll leftNum, ll index)
//{
//    if (index == m)
//    {
//        if (curNum > maxNum)
//            maxNum = curNum;
//        return;
//    }
//
//    for (ll i = 1; i <= 2 * curNum; ++i)
//    {
//        ll newLeftNum = leftNum - i;
//        if (newLeftNum < 0 || (m - index <= 26 && 1 << (m - index) * i <= maxNum)) // 剪枝，约束条件：最多只能取n个节点，即剩余节点数不小于0；限界条件：在当前节点的情况下，最好情况是构成一颗满二叉子树，但如果这样也不可能超过当前最大值，则不必继续搜索
//            break;
//        maxNumBacktracking(n, m, maxNum, i, curSum + i, newLeftNum, index + 1);
//    }
//}

//// 非递归回溯法求解第m层最大节点数
//void maxnumnonrecursive(ll n, ll m, ll& maxnum)
//{
//    stack<tuple<ll, ll, ll, ll, ll, ll>> st;
//    st.push(make_tuple(1, 1, n - 1, 0, 0, 0));
//
//    while (!st.empty())
//    {
//        ll curnum, cursum, leftnum, index, i, level;
//        tie(curnum, cursum, leftnum, index, i, level) = st.top();
//        st.pop();
//
//        if (index == m)
//        {
//            if (curnum > maxnum)
//                maxnum = curnum;
//            continue;
//        }
//
//        for (; i <= 2 * curnum; ++i)
//        {
//            ll newleftnum = leftnum - i;
//            if (newleftnum < 0 || (m - index <= 26 && 1 << (m - index) * i <= maxnum))
//                break;
//            st.push(make_tuple(i, cursum + i, newleftnum, index + 1, 1, level + 1));
//        }
//    }
//}
//
//int main()
//{
//    ll t;
//    cin >> t;
//    while (t--)
//    {
//        ll n, m;
//        cin >> n >> m;
//        if (n < m)
//            cout << 0 << endl;
//        else if (m <= 26 && n >= (2 << m) - 1)
//            cout << (1 << m) << endl;
//        else
//        {
//            ll maxnum = 0;
//            maxnumnonrecursive(n, m, maxnum);
//            cout << maxnum << endl;
//        }
//    }
//    return 0;
//}

void maxNumRecursion(int n, int m, int& index, int startIndex, int& curNum, int& curSum)
{
	if (curSum + m - index > n) // 小于单枝二叉树
		return;
	else if(m <= 26 && curSum + (1 << m - index + 1) - 1 <= n) // 大于等于满二叉树
	{
		curNum += 1 << m - index;
		return;
	}
	else // 大于等于单枝二叉树，小于满二叉树
	{
		curSum += m - index; // 先构建单枝二叉树
		curNum++;
		index = m - 1;

		while (curSum + (1 << m - index) - 1 <= n && index >= startIndex) // 自下往上构建满二叉树，但是由于小于满二叉树所以中途肯定会停止
		{
			curSum += (1 << m - index) - 1;
			curNum += 1 << m - index - 1;
			index--;
		}

		index++; // 停止之后进入右子树，视右子树的根节点为一个全新的树，递归
		curSum++;
		maxNumRecursion(n, m, index, index, curNum, curSum);
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		int index = 0;
		int curNum = 0;
		int curSum = 1;
		maxNumRecursion(n, m, index, 0, curNum, curSum);
		cout << curNum << endl;
	}
	return 0;
}

/*
* 注意1：小心溢出！尤其是涉及到位运算的地方。经过计算，2^26 > 10^8，因此在数据范围内，可以限制m <= 26以保证不会溢出。
* 注意2：原递归会超内存，因此需要改为非递归回溯法。
* 注意3：之前回溯法其实不是一个很好的方法。新写的递归方法可以视为两侧逼近，在最小单枝二叉树到最大满二叉树之间逐渐逼近，最后逼近到结果。
*/