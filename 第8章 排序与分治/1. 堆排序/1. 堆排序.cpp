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

	// 建堆
	int size = heap.size();
	for(int i = size / 2; i >= 1; i--)
		heapifyGreater(heap, i, size);
	printHeap(heap, size);

	// 拿出堆顶元素
	for (int i = size - 1; i >= size - 2; i--)
	{
		swap(heap[1], heap[i]);
		heapifyGreater(heap, 1, i);
		printHeap(heap, i);
	}
	return 0;
}

/*
* 数组模拟堆排序，有以下注意点：
* 1. 初始建堆不是边插入边调整，而是等全部插入完之后再从最后一个非叶子节点开始向前调整，这样可以保证调整的时间复杂度是O(n)
* 2. 后续拿出堆顶元素的时候，将堆顶元素和最后一个元素交换之后只需要一次调整即可，因为函数中的调整是从上往下递归的
* 
* 错误1：想要让数组从大到小排序，应该使用小根堆而不是大根堆
* 错误2：heapify函数中需要定义size参数，因为在调整堆的过程中，堆的大小是在不断变小的，而数组的大小是固定的，因此不能用heap.size()来代替
*/