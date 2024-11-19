#include <bits/stdc++.h>

using namespace std;

int ans = 0;

bool check(int n, int x, int y, vector<bool>& occupiedRows, vector<bool>& occupiedCols, vector<bool>& occupiedLeftDiagonals, vector<bool>& occupiedRightDiagonals)
{
	if (occupiedRows[x] || occupiedCols[y] || occupiedLeftDiagonals[x + y - 1] || occupiedRightDiagonals[x - y + n])
		return false;
	return true;
}

void queen(int n, int m, int diff, vector<int>& emptyRows, vector<int>& everyQueen, vector<bool>& occupiedRows, vector<bool>& occupiedCols, vector<bool>& occupiedLeftDiagonals, vector<bool>& occupiedRightDiagonals, int currentRow, int currentQueen)
{
	if (currentRow > n)
	{
		// ����Ƿ����ȫ�����򣬼�diff������������Ƿ񱻿���
		vector<int> emptyCols(diff + 1, 0);
		for(int j = 1; j <= n; ++j)
			if(!occupiedCols[j])
				emptyCols[++emptyCols[0]] = j; // ������ز����������ʵ���±���ۼӣ�ͬʱ���ܼ�¼Ԫ�ظ���
		for (int j = 1; j <= diff; ++j)
			occupiedRows[emptyRows[j]] = false;
		bool flag = true;
		// �������Ƿ񱻿���
		for(int j = 1; j <= diff; ++j)
			for(int k = 1; k <= n; ++k)
				if(check(n, emptyRows[j], k, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
				{
					flag = false;
					goto p; // gotoֱ����������ѭ��������ֻ��Ҫ����һ������
				}
		// �������Ƿ񱻿���
		for(int j = 1; j <= diff; ++j)
			for(int k = 1; k <= n; ++k)
				if(check(n, k, emptyCols[j], occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
				{
					flag = false;
					goto p;
				}
		if (flag)
			++ans;
	p:
		// �ָ��ֳ���Ҫ�ǵ�����DFS�����Ա������滹���õ���
		for (int j = 1; j <= diff; ++j)
			occupiedRows[emptyRows[j]] = true;
		return;
	}

	// ������ǰ���õĿ��У�ֱ������
	if(occupiedRows[currentRow])
		queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, currentRow + 1, currentQueen);

	for (int j = 1; j <= n; ++j)
	{
		if (check(n, currentRow, j, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals))
		{
			everyQueen[currentQueen] = j;
			occupiedRows[currentRow] = true;
			occupiedCols[j] = true;
			occupiedLeftDiagonals[currentRow + j - 1] = true;
			occupiedRightDiagonals[currentRow - j + n] = true;
			queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, currentRow + 1, currentQueen + 1);
			// �ǵû��ݣ�
			occupiedRows[currentRow] = false;
			occupiedCols[j] = false;
			occupiedLeftDiagonals[currentRow + j - 1] = false;
			occupiedRightDiagonals[currentRow - j + n] = false;
		}
	}
}

void combination(int n, int m, int diff, vector<int> emptyRows, int t)
{
	if (t > diff)
	{
		// ���ûʺ���
		vector<int> everyQueen(m + 1, 0);
		vector<bool> occupiedRows(n + 1, false), occupiedCols(n + 1, false), occupiedLeftDiagonals(2 * n, false), occupiedRightDiagonals(2 * n, false);
		for (int i = 1; i <= diff; ++i)
			occupiedRows[emptyRows[i]] = true;
		queen(n, m, diff, emptyRows, everyQueen, occupiedRows, occupiedCols, occupiedLeftDiagonals, occupiedRightDiagonals, 1, 1);

		//// �������emptyRows
		//for(int i = 1; i <= diff; ++i)
		//	cout << emptyRows[i] << " ";
		//cout << endl;
		return;
	}

	for (int i = emptyRows[t - 1] + 1; i <= n - diff + t; ++i)
	{
		emptyRows[t] = i;
		combination(n, m, diff, emptyRows, t + 1);
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	int diff = n - m;
	vector<int> emptyRows(diff + 1, 0);
	combination(n, m, diff, emptyRows, 1);
	cout << ans << endl;
	return 0;
}

/*
* ˼·�������ԭ����N�ʺ����⣬��������diff���ʺ���˻���diff����diff�У��������ǿ���ͨ��������ϣ���ȷ��diff�����У�Ȼ�����ڻᱻoccupy�����Ͻ���N�ʺ��������⡣�����������£�ʱ������Ϊԭ����10C5=252����Ҳ�ǿ��Խ��ܵġ�
* �����ɺ�������Ҫ������еĿ��������(ָ��Ӧ��/����û�лʺ�)�Ƿ񶼱����ƣ�����������ˣ�˵���ǿ��Եģ�++ans��
* 
* �ջ�1��ʹ��goto�������ڶ���ѭ����ֱ��������������Ҫʹ��flag��־λ��ͬʱ�ô���ֻ��Ҫ����һ�����ڼ��ɡ�
* �ջ�2��ʹ�õݹ�ʵ��������ϣ�ʵ�����ǹ�����һ�ŵݹ�����ÿһ�����һ�����У�ÿ���ڵ����һ�����е�ѡ�����һ��������п��е�ѡ����ɣ�Ȼ�����N�ʺ��������⡣
* �ջ�3�������ʹ�þ���ֵ���ж϶Խ��߱�ռ�ã����ǿ���ʹ����������occupiedLeftDiagonals��occupiedRightDiagonals����¼���Խ���ռ�����������LeftDiagonals���±�Ϊx+y-1�������ϵ����£�RightDiagonals���±�Ϊx-y+n�������ϵ����¡������С��Ϊ2n(0~2n-1)��
* 
* ע��1��ʹ�õݹ����ʱ��Ҫ�ǵø�ԭ�ֳ�����������Ҫ��ԭ�ֳ��ĵط�������queen�����У�
* 1. ���ûʺ���̵��еĸ�ԭ�ֳ���
* 2. �ж��Ƿ�ȫ�����Ƶ�ʱ����ʱ�Ե��޸���occupiedRows��ֵ����Ϊ�˷������check������ʹ����Ϻ���Ҫ��ԭ�ֳ���
*/