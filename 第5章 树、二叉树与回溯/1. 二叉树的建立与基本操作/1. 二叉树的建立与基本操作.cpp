#include <bits/stdc++.h>

using namespace std;

typedef char elemType;

typedef struct BinTreeNode
{
	elemType data;
	struct BinTreeNode *lchild, *rchild;
}BinTreeNode, *BinTree;

// 二叉树的创建
void createBinTree(BinTreeNode*& T, vector<elemType>& data, int& i) // 递归创建二叉树，注意可以使用字符数组+索引i的方式来取取遍数组元素
{
	if (i >= data.size())
		return;

	if (data[i] == '#')
		T = NULL;
	else
	{
		T = new BinTreeNode;
		T->data = data[i];
		createBinTree(T->lchild, data, ++i);
		createBinTree(T->rchild, data, ++i);
	}
}

// 二叉树的凹入表输出
void printRecessedTable(BinTreeNode* T, int level)
{
	if (T)
	{
		for(int i = 0; i < level; i++)
			cout << "    ";
		cout << T->data << endl;
		printRecessedTable(T->lchild, level + 1);
		printRecessedTable(T->rchild, level + 1);
	}
}

// 二叉树的输出
void output(BinTreeNode* T)
{
	cout << T->data;
}

// 二叉树的遍历，使用函数指针作为参数，提高代码复用性。注意函数指针的使用！定义参数时不用写参数名，只写参数类型即可。
void preOrder(BinTreeNode* T, void(*visit)(BinTreeNode*))
{
	if (T)
	{
		visit(T);
		preOrder(T->lchild, visit);
		preOrder(T->rchild, visit);
	}
}

void inOrder(BinTreeNode* T, void(*visit)(BinTreeNode*))
{
	if (T)
	{
		inOrder(T->lchild, visit);
		visit(T);
		inOrder(T->rchild, visit);
	}
}

void postOrder(BinTreeNode* T, void(*visit)(BinTreeNode*))
{
	if (T)
	{
		postOrder(T->lchild, visit);
		postOrder(T->rchild, visit);
		visit(T);
	}
}

// 求二叉树的叶子结点个数
int leaves = 0;

void leafCount(BinTreeNode* T)
{
	if(!T->lchild && !T->rchild)
		leaves++;
}

// 翻转二叉树
void invertBinTree(BinTreeNode* T)
{
	if (T)
	{
		BinTreeNode* temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

int main()
{
	string str;
	cin >> str;
	vector<elemType> data;
	for (int i = 0; i < str.size(); i++)
		data.push_back(str[i]);
	BinTreeNode* THead = NULL;
	int i = 0;
	createBinTree(THead, data, i);
	cout << "BiTree" << endl;
	printRecessedTable(THead, 0);
	cout << "pre_sequence  : ";
	preOrder(THead, output);
	cout << endl;
	cout << "in_sequence   : ";
	inOrder(THead, output);
	cout << endl;
	cout << "post_sequence : ";
	postOrder(THead, output);
	cout << endl;
	leaves = 0;
	cout << "Number of leaf: ";
	preOrder(THead, leafCount);
	cout << leaves << endl;
	preOrder(THead, invertBinTree);
	cout << "BiTree swapped" << endl;
	printRecessedTable(THead, 0);
	cout << "pre_sequence  : ";
	preOrder(THead, output);
	cout << endl;
	cout << "in_sequence   : ";
	inOrder(THead, output);
	cout << endl;
	cout << "post_sequence : ";
	postOrder(THead, output);
	cout << endl;
	return 0;
}

/*
* 收获1：二叉树创建函数的参数中，BinTreeNode*& T，表示传入的是指针的引用，这样在函数内部对T的修改会影响到外部的T；如果只是BinTreeNode* T，那么对T的修改只会在函数内部生效，这时候可以使用返回值传递修改后的T；
* 收获2：二叉树创建的时候，可以使用字符数组+索引i的方式来取取遍数组元素；
* 收获3：二叉树的遍历，使用函数指针作为参数，提高代码复用性。注意函数指针的使用！定义参数时不用写参数名，只写参数类型即可；
* 错误1：注意在翻转二叉树的时候应该选用先序或者后序遍历，而不是中序遍历，因为中序遍历会导致左右子树的交换，交换过后又进入右子树，导致再次交换，最终还是原来的树。
*/