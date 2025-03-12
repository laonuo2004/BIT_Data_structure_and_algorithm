#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

void heapifyGreater(vector<int>& heap, int i, int size)
{
	int left = i * 2;
	int right = i * 2 + 1;
	int largest = i;
	if(left < size && heap[left] > heap[largest])
		largest = left;
	if(right < size && heap[right] > heap[largest])
		largest = right;
	if(largest != i)
	{
		swap(heap[i], heap[largest]);
		heapifyGreater(heap, largest, size);
	}
}

void printHeap(vector<int>& heap, int size)
{
	for (int i = 1; i < size; i++)
		cout << heap[i] << " ";
	cout << endl;
}

int main()
{
	int num, n;
	cin >> n;
	vector<int> heap;
	heap.push_back(INT_MIN);
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		heap.push_back(num);
	}

	// ����
	int size = heap.size();
	for(int i = size / 2; i >= 1; i--)
		heapifyGreater(heap, i, size);
	printHeap(heap, size);

	// �ó��Ѷ�Ԫ��
	for (int i = size - 1; i >= size - 2; i--)
	{
		swap(heap[1], heap[i]);
		heapifyGreater(heap, 1, i);
		printHeap(heap, i);
	}
	return 0;
}

/*
* ����ģ�������������ע��㣺
* 1. ��ʼ���Ѳ��Ǳ߲���ߵ��������ǵ�ȫ��������֮���ٴ����һ����Ҷ�ӽڵ㿪ʼ��ǰ�������������Ա�֤������ʱ�临�Ӷ���O(n)
* 2. �����ó��Ѷ�Ԫ�ص�ʱ�򣬽��Ѷ�Ԫ�غ����һ��Ԫ�ؽ���֮��ֻ��Ҫһ�ε������ɣ���Ϊ�����еĵ����Ǵ������µݹ��
* 
* ����1����Ҫ������Ӵ�С����Ӧ��ʹ��С���Ѷ����Ǵ����
* ����2��heapify��������Ҫ����size��������Ϊ�ڵ����ѵĹ����У��ѵĴ�С���ڲ��ϱ�С�ģ�������Ĵ�С�ǹ̶��ģ���˲�����heap.size()������
*/