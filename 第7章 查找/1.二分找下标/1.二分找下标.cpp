#include <bits/stdc++.h>
#define MAXBATCH 100000

using namespace std;

bool flag = false;
void find(vector<int> a, vector<bool>& b, int begin, int end, int i)
{
	if (begin > end)
		return;
	int mid = begin + (end - begin) / 2;
	if (a[mid] == i * MAXBATCH + mid)
	{
		flag = true;

		//b[mid] = true;
		//find(a, b, begin, mid - 1, i);
		//find(a, b, mid + 1, end, i);

		stack<int> s;
		for (int j = mid; j >= 0; --j)
		{
			if (a[j] == i * MAXBATCH + j)
				s.push(i * MAXBATCH + j);
			else
				break;
		}
		while (!s.empty())
		{
			cout << s.top() << " ";
			s.pop();
		}
		for(int j = mid + 1; j <= end; ++j)
			if(a[j] == i * MAXBATCH + j)
				cout << a[j] << " ";
			else
				break;
	}
	else if (a[mid] > i * MAXBATCH + mid)
		find(a, b, begin, mid - 1, i);
	else
		find(a, b, mid + 1, end, i);
}

int main()
{
	int n;
	cin >> n;
	if(!n)
	{
		cout << "No" << endl;
		return 0;
	}
	for (int i = 0; n > 0; ++i)
	{
		int size = min(n, MAXBATCH);
		n -= MAXBATCH;
		vector<int> a(size);
		for(int j = 0; j < size; ++j)
			cin >> a[j];

		//if (a[size - 1] < i * MAXBATCH + size - 1)
		//	continue;
		//else if (a[0] == i * MAXBATCH)
		//{
		//	flag = true;
		//	if (a[size - 1] == i * MAXBATCH + size - 1)
		//	{
		//		for (int j = 0; j < size; ++j)
		//			cout << i * MAXBATCH + j << " ";
		//		int temp, k = 0;
		//		while (cin >> temp, temp == i * MAXBATCH + size + k)
		//		{
		//			cout << temp << " ";
		//			++k;
		//		}
		//	}
		//	else
		//		for(int j = 0; j < size; ++j)
		//			if(a[j] == i * MAXBATCH + j)
		//				cout << a[j] << " ";
		//			else
		//				break;
		//}
		//else if (a[size - 1] == i * MAXBATCH + size - 1)
		//{
		//	flag = true;
		//	stack <int> s;
		//	for (int j = size - 1; j >= 0; --j)
		//	{
		//		if (a[j] == i * MAXBATCH + j)
		//			s.push(i * MAXBATCH + j);
		//		else
		//			break;
		//	}
		//	while (!s.empty())
		//	{
		//		cout << s.top() << " ";
		//		s.pop();
		//	}
		//	int temp, k = 0;
		//	while(cin >> temp, temp == i * MAXBATCH + size + k)
		//	{
		//		cout << temp << " ";
		//		++k;
		//	}
		//}
		//else if (a[0] < i * MAXBATCH && a[size - 1] > i * MAXBATCH + size - 1)
		//{
		//	vector<bool> b(size, false);
		//	find(a, b, 0, size - 1);
		//	for(int j = 0; j < size; ++j)
		//		if(b[j])
		//			cout << i * MAXBATCH + j << " ";
		//}
		//else if (a[0] > i * MAXBATCH)
		//	break;

		vector<bool> b(size, false);
		find(a, b, 0, size - 1, i);
		for(int j = 0; j < size; ++j)
			if(b[j])
				cout << i * MAXBATCH + j << " ";
	}
	if (!flag)
		cout << "No ";
	cout << endl;
	return 0;
}

/*
* 思路：二分查找，但是由于数据量较大，需要分批处理，每次处理100000个数据，因此最多需要处理10批数据。
* 
* 对于每一批数据，可以按照首尾的情况分为以下几种情况：
* 
* 首部 | 尾部 | 情况
* ----|----|----
* 小于 | 小于 | 无效数据，跳过
* 小于 | 等于 | 从尾部开始找到第一个不符合的数据，注意由于需要按照从小到大的顺序输出，因此需要使用栈来存储数据。随后使用while循环输出后续数据直到不符合为止
* 小于 | 大于 | 使用二分查找，找到所有符合条件的数据。在这之后的数据都不符合条件，因此直接跳出循环
* 等于 | 小于 | 不可能情况，因为斜率至少为1
* 等于 | 等于 | 输出整个数组，随后使用while循环输出后续数据直到不符合为止
* 等于 | 大于 | 从首部开始找到第一个不符合的数据
* 大于 | 小于 | 不可能情况，因为斜率至少为1
* 大于 | 等于 | 不可能情况，因为斜率至少为1
* 大于 | 大于 | 无效数据，并且后续数据都不符合条件，直接跳出循环
*/