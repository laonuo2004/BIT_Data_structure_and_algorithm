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
	// Rowe方法
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
	if(right - left < 75) // 小于75个元素，直接排序
	{
		selectSort(Y, left, right);
		return Y[left + k - 1];
	}

	// 分n/5(向上取整)组，找到每组的中位数，并将它们放在数组的前部
	for (int i = 0; i < (right - left - 4) / 5; i++) // 这里的right - left - 4是为了保证最后一组元素个数不超过5，实际上是向下取整的操作
	{
		int l = left + 5 * i, r = l + 4;
		selectSort(Y, l, r);
		swap(Y[left + i], Y[l + 2]);
	}
	ll x = findMedian(Y, left, left + (right - left - 4) / 5, ((right - left - 4) / 5 + 1) / 2); // 找到中位数的中位数

	// 以中位数的中位数为基准，进行划分
	int i = partition(Y, left, right, x);

	// 划分后，i为中位数的位置，left到i-1的元素都小于中位数，i+1到right的元素都大于中位数，此时再分情况递归
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

/* 思路：线性时间选择算法，利用分治法，找到中位数的中位数，然后以中位数的中位数为基准进行划分，再分情况递归，直到找到第k小的元素为止
* 
* 收获1：findMedian函数的实现步骤：
* 1. 如果元素个数小于75，直接排序，返回第k小的元素
* 2. 将元素分为n/5组，找到每组的中位数，将它们放在数组的前部
* 3. 递归查找中位数的中位数
* 4. 以中位数的中位数为基准，进行划分(类似快排)
* 5. 划分后，i为中位数的位置，left到i-1的元素都小于中位数，i+1到right的元素都大于中位数，此时再分情况递归左边或右边
* 
* 收获2：大部分时候中位数都是靠区间长度小于75的情况下，直接排序找到的，能直接找到i == k的情况比较少
* 
* 收获3：快排Rowe方法的实现，只需要从左到右遍历一次即可，遇到小于基准的元素就交换到前面，最后再交换基准和i的位置即可。其中i是小于基准的元素的个数,j充当遍历指针。该方法在链表中使用较多
*/