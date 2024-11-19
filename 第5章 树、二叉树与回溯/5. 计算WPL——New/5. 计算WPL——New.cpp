#include <bits/stdc++.h>

using namespace std;

typedef struct HTNode
{
	int weight;
	int parent, lchild, rchild;
}HTNode;

void createHuffmanTree(vector<HTNode>& huffmanTreeList, int n)
{
	// 初始化叶子节点：设置好频率之后，记得把parent、lchild、rchild都设置为-1
	for (int i = 0; i < 2 * n - 1; ++i)
		huffmanTreeList[i].parent = huffmanTreeList[i].lchild = huffmanTreeList[i].rchild = -1;
	for (int i = 0; i < n; ++i)
		cin >> huffmanTreeList[i].weight;
	int root = 2 * n - 2;

	// 创建Huffman树，基本思路：每次在前面找到最小的两个节点，合并成一个新的节点，放置在静态链表最后
	for (int i = n; i < 2 * n - 1; ++i)
	{
		// 找到最小的两个节点
		int min1 = INT_MAX, min2 = INT_MAX;
		int index1 = -1, index2 = -1;
		for (int j = 0; j < i; ++j)
		{
			if (huffmanTreeList[j].parent == -1)
			{
				if (huffmanTreeList[j].weight < min1)
				{
					min2 = min1;
					index2 = index1;
					min1 = huffmanTreeList[j].weight;
					index1 = j;
				}
				else if (huffmanTreeList[j].weight < min2)
				{
					min2 = huffmanTreeList[j].weight;
					index2 = j;
				}
			}
		}

		// 合并成一个新的节点，并设置相关指针
		huffmanTreeList[i].weight = huffmanTreeList[index1].weight + huffmanTreeList[index2].weight;
		huffmanTreeList[i].lchild = index1;
		huffmanTreeList[i].rchild = index2;
		huffmanTreeList[index1].parent = i;
		huffmanTreeList[index2].parent = i;
	}
}

// 计算WPL，基本思路：对于每个叶子节点，计算其深度，然后乘以其权值，最后累加；此外也可以使用后续递归遍历的方法，此方法要记得加上根节点的权值
int calculateWPL(vector<HTNode>& huffmanTreeList, int n)
{
	int WPL = 0;
	for (int i = 0; i < n; ++i)
	{
		int depth = 0;
		int j = i;
		while (huffmanTreeList[j].parent != -1)
		{
			++depth;
			j = huffmanTreeList[j].parent;
		}
		WPL += huffmanTreeList[i].weight * depth;
	}
	return WPL;
}

int main()
{
	int n;
	cin >> n;
	vector<HTNode> huffmanTreeList(2 * n - 1); // 注意数量为2n-1，其中0~n-1为叶子节点，n~2n-2为外节点
	createHuffmanTree(huffmanTreeList, n);
	int WPL = calculateWPL(huffmanTreeList, n);
	cout << "WPL=" << WPL << "\n";
	return 0;
}