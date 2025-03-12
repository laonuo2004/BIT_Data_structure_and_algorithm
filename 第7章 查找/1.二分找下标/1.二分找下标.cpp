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
* ˼·�����ֲ��ң����������������ϴ���Ҫ��������ÿ�δ���100000�����ݣ���������Ҫ����10�����ݡ�
* 
* ����ÿһ�����ݣ����԰�����β�������Ϊ���¼��������
* 
* �ײ� | β�� | ���
* ----|----|----
* С�� | С�� | ��Ч���ݣ�����
* С�� | ���� | ��β����ʼ�ҵ���һ�������ϵ����ݣ�ע��������Ҫ���մ�С�����˳������������Ҫʹ��ջ���洢���ݡ����ʹ��whileѭ�������������ֱ��������Ϊֹ
* С�� | ���� | ʹ�ö��ֲ��ң��ҵ����з������������ݡ�����֮������ݶ����������������ֱ������ѭ��
* ���� | С�� | �������������Ϊб������Ϊ1
* ���� | ���� | ����������飬���ʹ��whileѭ�������������ֱ��������Ϊֹ
* ���� | ���� | ���ײ���ʼ�ҵ���һ�������ϵ�����
* ���� | С�� | �������������Ϊб������Ϊ1
* ���� | ���� | �������������Ϊб������Ϊ1
* ���� | ���� | ��Ч���ݣ����Һ������ݶ�������������ֱ������ѭ��
*/