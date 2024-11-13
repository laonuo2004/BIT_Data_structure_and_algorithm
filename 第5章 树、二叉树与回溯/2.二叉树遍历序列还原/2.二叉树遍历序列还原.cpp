#include <bits/stdc++.h>

using namespace std;

typedef char elemType;

typedef struct BinTreeNode
{
	elemType data;
	struct BinTreeNode *lchild, *rchild;
}BinTreeNode, *BinTree;

// 二叉树的创建，尝试不用全局变量，也不对字符串进行分割，而是使用字符串+索引的方式确定左右子树的范围
void createBinTree(BinTreeNode*& T, string inSequence, string postSequence, int inStart, int inEnd, int postStart, int postEnd)
{
	if (postStart > postEnd || inStart > inEnd)
	{
		T = NULL;
		return;
	}

	T = new BinTreeNode;
	T->data = postSequence[postEnd];

	int rootIndex = inStart;
	while (inSequence[rootIndex] != postSequence[postEnd])
		rootIndex++;

	int leftLength = rootIndex - inStart;
	createBinTree(T->lchild, inSequence, postSequence, inStart, rootIndex - 1, postStart, postStart + leftLength - 1); // 注意等量关系：左子树的长度可以由根节点在中序遍历序列中的位置确定，随后可以用于确定后序遍历序列当中左子树的范围
	createBinTree(T->rchild, inSequence, postSequence, rootIndex + 1, inEnd, postStart + leftLength, postEnd - 1);
}

void output(BinTreeNode* T)
{
	cout << T->data;
}

void levelOrder(BinTreeNode* T, void(*visit)(BinTreeNode*))
{
	queue<BinTreeNode*> q;
	q.push(T);

	while (!q.empty())
	{
		BinTreeNode* node = q.front();
		q.pop();
		visit(node);
		if(node->lchild)
			q.push(node->lchild);
		if(node->rchild)
			q.push(node->rchild);
	}
}

int main()
{
	string inSequence, postSequence;
	BinTreeNode* T;
	cin >> inSequence >> postSequence;
	createBinTree(T, inSequence, postSequence, 0, inSequence.size() - 1, 0, postSequence.size() - 1);
	levelOrder(T, output);
	cout << endl;
	return 0;
}

/*
* 收获1：标准的使用中序序列+后序序列构建二叉树的方法，尽量不使用全局变量，因为全局变量会使得函数不可重入，不利于多线程编程；同时也避免对字符串进行分割，因为分割字符串会增加时间复杂度。最好的方法是使用字符串+索引的方式确定左右子树的范围。
* 收获2：在确定左右子树的范围时，可以利用等量关系，即左子树的长度可以由根节点在中序遍历序列中的位置确定，随后可以用于确定后序遍历序列当中左子树的范围。
* 收获3：二叉树的层次遍历，使用队列实现，每次取出队首元素，访问该元素，然后将其左右孩子入队。其实就是广度优先搜索。
*/