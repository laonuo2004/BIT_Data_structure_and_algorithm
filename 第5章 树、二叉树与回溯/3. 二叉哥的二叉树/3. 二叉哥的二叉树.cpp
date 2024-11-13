#include <bits/stdc++.h>

using namespace std;

//// ���ݷ�����m�����ڵ���
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
//        if (newLeftNum < 0 || (m - index <= 26 && 1 << (m - index) * i <= maxNum)) // ��֦��Լ�����������ֻ��ȡn���ڵ㣬��ʣ��ڵ�����С��0���޽��������ڵ�ǰ�ڵ������£��������ǹ���һ�����������������������Ҳ�����ܳ�����ǰ���ֵ���򲻱ؼ�������
//            break;
//        maxNumBacktracking(n, m, maxNum, i, curSum + i, newLeftNum, index + 1);
//    }
//}

//// �ǵݹ���ݷ�����m�����ڵ���
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
	if (curSum + m - index > n) // С�ڵ�֦������
		return;
	else if(m <= 26 && curSum + (1 << m - index + 1) - 1 <= n) // ���ڵ�����������
	{
		curNum += 1 << m - index;
		return;
	}
	else // ���ڵ��ڵ�֦��������С����������
	{
		curSum += m - index; // �ȹ�����֦������
		curNum++;
		index = m - 1;

		while (curSum + (1 << m - index) - 1 <= n && index >= startIndex) // �������Ϲ���������������������С����������������;�϶���ֹͣ
		{
			curSum += (1 << m - index) - 1;
			curNum += 1 << m - index - 1;
			index--;
		}

		index++; // ֹ֮ͣ����������������������ĸ��ڵ�Ϊһ��ȫ�µ������ݹ�
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
* ע��1��С��������������漰��λ����ĵط����������㣬2^26 > 10^8����������ݷ�Χ�ڣ���������m <= 26�Ա�֤���������
* ע��2��ԭ�ݹ�ᳬ�ڴ棬�����Ҫ��Ϊ�ǵݹ���ݷ���
* ע��3��֮ǰ���ݷ���ʵ����һ���ܺõķ�������д�ĵݹ鷽��������Ϊ����ƽ�������С��֦�������������������֮���𽥱ƽ������ƽ��������
*/