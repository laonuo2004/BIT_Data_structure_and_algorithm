#include <bits/stdc++.h>
#define ll long long

using namespace std;

void selectSort(vector<ll>& Y, int left, int right)
{
	for (int i = left; i <= right; i++)
	{
		int minIndex = i;
		for(int j = i + 1; j <= right; j++)
			if(Y[j] < Y[minIndex])
				minIndex = j;
		swap(Y[i], Y[minIndex]);
	}
}

int partition(vector<ll>& Y, int left, int right, ll x)
{
	// Rowe����
	for (int j = left; j < right; j++)
		if (Y[j] == x)
		{
			swap(Y[j], Y[right]);
			break;
		}
	int i = left;
	for (int j = left; j < right; j++)
		if (Y[j] < x)
			swap(Y[i++], Y[j]);
	swap(Y[i], Y[right]);
	return i;
}

ll findMedian(vector<ll>& Y, int left, int right, int k)
{
	if(right - left < 75) // С��75��Ԫ�أ�ֱ������
	{
		selectSort(Y, left, right);
		return Y[left + k - 1];
	}

	// ��n/5(����ȡ��)�飬�ҵ�ÿ�����λ�����������Ƿ��������ǰ��
	for (int i = 0; i < (right - left - 4) / 5; i++) // �����right - left - 4��Ϊ�˱�֤���һ��Ԫ�ظ���������5��ʵ����������ȡ���Ĳ���
	{
		int l = left + 5 * i, r = l + 4;
		selectSort(Y, l, r);
		swap(Y[left + i], Y[l + 2]);
	}
	ll x = findMedian(Y, left, left + (right - left - 4) / 5, ((right - left - 4) / 5 + 1) / 2); // �ҵ���λ������λ��

	// ����λ������λ��Ϊ��׼�����л���
	int i = partition(Y, left, right, x);

	// ���ֺ�iΪ��λ����λ�ã�left��i-1��Ԫ�ض�С����λ����i+1��right��Ԫ�ض�������λ������ʱ�ٷ�����ݹ�
	int j = i - left + 1;
	if(k < j)
		return findMedian(Y, left, i, k);
	else if(k > j)
		return findMedian(Y, i + 1, right, k - j);
	else
		return Y[i];
}

int main()
{
	ll x, y;
	vector<ll> Y;
	while(scanf("%lld,%lld", &x, &y) != EOF)
		Y.push_back(y);
	//for (ll i = 0; i < 2000000; i++)
	//	Y.push_back(rand() * rand());
	int k = (Y.size() + 1) / 2;
	printf("%lld\n", findMedian(Y, 0, Y.size() - 1, k));
	return 0;
}

/* ˼·������ʱ��ѡ���㷨�����÷��η����ҵ���λ������λ����Ȼ������λ������λ��Ϊ��׼���л��֣��ٷ�����ݹ飬ֱ���ҵ���kС��Ԫ��Ϊֹ
* 
* �ջ�1��findMedian������ʵ�ֲ��裺
* 1. ���Ԫ�ظ���С��75��ֱ�����򣬷��ص�kС��Ԫ��
* 2. ��Ԫ�ط�Ϊn/5�飬�ҵ�ÿ�����λ���������Ƿ��������ǰ��
* 3. �ݹ������λ������λ��
* 4. ����λ������λ��Ϊ��׼�����л���(���ƿ���)
* 5. ���ֺ�iΪ��λ����λ�ã�left��i-1��Ԫ�ض�С����λ����i+1��right��Ԫ�ض�������λ������ʱ�ٷ�����ݹ���߻��ұ�
* 
* �ջ�2���󲿷�ʱ����λ�����ǿ����䳤��С��75������£�ֱ�������ҵ��ģ���ֱ���ҵ�i == k������Ƚ���
* 
* �ջ�3������Rowe������ʵ�֣�ֻ��Ҫ�����ұ���һ�μ��ɣ�����С�ڻ�׼��Ԫ�ؾͽ�����ǰ�棬����ٽ�����׼��i��λ�ü��ɡ�����i��С�ڻ�׼��Ԫ�صĸ���,j�䵱����ָ�롣�÷�����������ʹ�ý϶�
*/