#include <bits/stdc++.h>

using namespace std;

typedef struct HTNode
{
	int weight;
	int parent, lchild, rchild;
}HTNode;

void createHuffmanTree(vector<HTNode>& huffmanTreeList, int n)
{
	// ��ʼ��Ҷ�ӽڵ㣺���ú�Ƶ��֮�󣬼ǵð�parent��lchild��rchild������Ϊ-1
	for (int i = 0; i < 2 * n - 1; ++i)
		huffmanTreeList[i].parent = huffmanTreeList[i].lchild = huffmanTreeList[i].rchild = -1;
	for (int i = 0; i < n; ++i)
		cin >> huffmanTreeList[i].weight;
	int root = 2 * n - 2;

	// ����Huffman��������˼·��ÿ����ǰ���ҵ���С�������ڵ㣬�ϲ���һ���µĽڵ㣬�����ھ�̬�������
	for (int i = n; i < 2 * n - 1; ++i)
	{
		// �ҵ���С�������ڵ�
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

		// �ϲ���һ���µĽڵ㣬���������ָ��
		huffmanTreeList[i].weight = huffmanTreeList[index1].weight + huffmanTreeList[index2].weight;
		huffmanTreeList[i].lchild = index1;
		huffmanTreeList[i].rchild = index2;
		huffmanTreeList[index1].parent = i;
		huffmanTreeList[index2].parent = i;
	}
}

// ����WPL������˼·������ÿ��Ҷ�ӽڵ㣬��������ȣ�Ȼ�������Ȩֵ������ۼӣ�����Ҳ����ʹ�ú����ݹ�����ķ������˷���Ҫ�ǵü��ϸ��ڵ��Ȩֵ
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
	vector<HTNode> huffmanTreeList(2 * n - 1); // ע������Ϊ2n-1������0~n-1ΪҶ�ӽڵ㣬n~2n-2Ϊ��ڵ�
	createHuffmanTree(huffmanTreeList, n);
	int WPL = calculateWPL(huffmanTreeList, n);
	cout << "WPL=" << WPL << "\n";
	return 0;
}