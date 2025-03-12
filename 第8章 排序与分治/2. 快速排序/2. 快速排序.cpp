#include <bits/stdc++.h>

using namespace std;

void print(vector<int> arr, int left, int right)
{
	for (int i = left; i <= right; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

void quickSort(vector<int>& arr, int left, int right, queue<int>& median)
{
	//cout << "The current array is: ";
	//print(arr, left, right);

	if (right - left <= 4)
	{
		for (int i = left; i <= right; ++i)
		{
			int temp = arr[i];
			int j = i - 1;
			for (; j >= left && arr[j] > temp; --j)
				arr[j + 1] = arr[j];
			arr[j + 1] = temp;
		}
		return;
	}

	int mid = left + (right - left) / 2;
	if(arr[left] > arr[mid])
		swap(arr[left], arr[mid]);
	if(arr[left] > arr[right])
		swap(arr[left], arr[right]);
	if(arr[mid] > arr[right])
		swap(arr[mid], arr[right]);
	swap(arr[mid], arr[left + 1]);
	median.push(arr[left + 1]);
	//cout << "After Median3 Value:" << arr[left + 1] << endl;

	int i = left + 1, j = right, pivotVal = arr[left + 1];
	while (i < j)
	{
		while(i < j && arr[j] > pivotVal)
			--j;
		if(i < j)
			arr[i++] = arr[j];
		while(i < j && arr[i] < pivotVal)
			++i;
		if(i < j)
			arr[j--] = arr[i];
	}
	arr[i] = pivotVal;

	quickSort(arr, left, i - 1, median);
	quickSort(arr, i + 1, right, median);
}

int main()
{
	string num;
	vector<int> arr;
	while (cin >> num, num != "#")
		arr.push_back(stoi(num));

	queue<int> median;
	quickSort(arr, 0, arr.size() - 1, median);

	cout << "After Sorting:" << endl;
	print(arr, 0, arr.size() - 1);
	cout << "Median3 Value:" << endl;
	if(median.empty())
		cout << "none";
	else
		while (!median.empty())
		{
			cout << median.front() << " ";
			median.pop();
		}
	cout << endl;
	return 0;
}

//-----------------------------------Solution 2-----------------------------------

//#include<iostream> 
//#include<algorithm> 
//#include<vector> 
//using namespace std;
//
//const int cutoff = 5;
//vector<int> median;
//
//void print(vector<int> arr, int left, int right)
//{
//	for (int i = left; i <= right; ++i)
//		cout << arr[i] << " ";
//	cout << endl;
//}
//
//// 插入排序 
//void insertionSort(vector<int>& arr, int left, int right) {
//    for (int i = left + 1; i <= right; i++) {
//        int tmp = arr[i], j = i;
//        for (; j > left && arr[j - 1] > tmp; j--)
//            arr[j] = arr[j - 1];
//        arr[j] = tmp;
//    }
//}
//
//// 计算中位数 
//void median3(vector<int>& arr, int left, int right) {
//    int center = (left + right) / 2;
//
//    if (arr[left] > arr[center])
//        swap(arr[left], arr[center]);
//    if (arr[left] > arr[right])
//        swap(arr[left], arr[right]);
//    if (arr[center] > arr[right])
//        swap(arr[center], arr[right]);
//
//    //将中位数放到right-1位置作为枢纽元 
//    swap(arr[center], arr[right - 1]);
//}
//
//// 快速排序 
//void quickSort(vector<int>& arr, int left, int right) {
//    cout << "The current array is: ";
//    print(arr, left, right);
//
//    if (right - left + 1 <= cutoff) {
//        insertionSort(arr, left, right);
//        return;
//    }
//
//    median3(arr, left, right);
//    median.push_back(arr[right - 1]);
//    cout << "After Median3 Value:" << arr[right - 1] << endl;
//
//    int i = left, j = right - 1;
//    int pivot = arr[right - 1];
//    for (;;) {
//        while (arr[++i] < pivot) {}
//        while (arr[--j] > pivot) {}
//        if (i < j)
//            swap(arr[i], arr[j]);
//        else
//            break;
//    }
//    swap(arr[i], arr[right - 1]);
//
//    quickSort(arr, left, i - 1);
//    quickSort(arr, i + 1, right);
//}
//
//// 主函数处理输入输出 
//int main() {
//    int num;
//    vector<int> nums;
//
//    while (cin >> num && cin.peek() != '#') {
//        nums.push_back(num);
//    }
//
//    quickSort(nums, 0, nums.size() - 1);
//
//    cout << "After Sorting:" << endl;
//    for (const auto& n : nums) {
//        cout << n << " ";
//    }
//    cout << endl;
//    cout << "Median3 Value:" << endl;
//
//    if (nums.size() > 5) {
//        for (int i = 0; i < median.size(); i++) {
//            cout << median[i] << " ";
//        }
//    }
//    else cout << "none";
//    cout << endl;
//    return 0;
//}