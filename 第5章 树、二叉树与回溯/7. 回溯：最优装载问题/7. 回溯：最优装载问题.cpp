#include <bits/stdc++.h>

using namespace std;

void backTracking(vector<int>& w, vector<bool>& x, vector<bool>& bestx, int cw, int lw, int& bestw, int i, int c, int n)
{
	if (i == n)
		return;

	// ��ʱ���µ�ǰ���Ž⣬���ڼ�֦
	if (cw > bestw)
	{
		bestw = cw;
		bestx = x;
	}

	// �ݹ�����������
	x[i] = true;
	if (cw + w[i] <= c)
		backTracking(w, x, bestx, cw + w[i], lw - w[i], bestw, i + 1, c, n);

	// �ݹ�����������
	x[i] = false;
	if (cw + lw - w[i] > bestw)
		backTracking(w, x, bestx, cw, lw - w[i], bestw, i + 1, c, n);

	// ��2���ο����㷨����������P. 129
	//if (i >= n)
	//{
	//	if (cw > bestw)
	//	{
	//		bestw = cw;
	//		bestx = x;
	//	}
	//	return;
	//}

	//lw -= w[i];
	//if (cw + w[i] <= c)
	//{
	//	x[i] = true;
	//	cw += w[i];
	//	backTracking(w, x, bestx, cw, lw, bestw, i + 1, c, n);
	//	cw -= w[i];
	//}
	//if (cw + lw > bestw)
	//{
	//	x[i] = false;
	//	backTracking(w, x, bestx, cw, lw, bestw, i + 1, c, n);
	//}
	//lw += w[i];
}

int main()
{
	int c, n;
	cin >> c >> n;
	vector<int> w(n);
	int lw = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> w[i];
		lw += w[i];
	}
	vector<bool> x(n);
	vector<bool> bestx(n);
	int cw = 0, bestw = 0;
	backTracking(w, x, bestx, cw, lw, bestw, 0, c, n);
	cout << bestw << endl;
	for (int i = 0; i < n; ++i)
		if (bestx[i])
			cout << i + 1 << " ";
	cout << endl;
	return 0;
}

/*
* ����1������Ĳ����Ƚ϶࣬����©����ȫ���������£�
* 1. ��Ŀ����������w��c��n��
* 2. �򵥻�����Ҫ��Ĳ�����x(ע�ⲻ�������ͣ���Ϊÿһ��֧��װ������Ƕ�����)��i��
* 3. ͳ�����װ������Ҫ��Ĳ�����cw��bestw��
* 4. ͳ�����װ��������Ҫ��Ĳ�����bestx��
* 5. ���ڼ�֦�Ĳ�����lw��ͬʱ�ǵü�ʱ����bestw��lw��
* ����2��������>=����>����Ϊ֮ǰ�Ѿ���ʱ�����˵�ǰ���Ž⣬�����>�Ļ����޷����뺯����
* ����3��ע�����Һ����������Ա�֤���Ž����������У�ʹ���Ž��ʾ�Ķ����������
*/