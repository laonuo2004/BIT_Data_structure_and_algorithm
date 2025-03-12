#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

typedef struct AVLNode
{
	char data;
	int height;
	AVLNode *left;
	AVLNode *right;
}AVLNode, *AVLTree;

AVLTree initAVLTree(char ch)
{
	AVLTree tree = (AVLTree)malloc(sizeof(AVLNode));
	tree->data = ch;
	tree->height = 1;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

int getHeight(AVLTree tree)
{
	if (tree == NULL)
		return 0;
	return tree->height;
}

void rotateLL(AVLTree& tree)
{
	AVLTree temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
	tree = temp;
}

void rotateRR(AVLTree& tree)
{
	AVLTree temp = tree->right;
	tree->right = temp->left;
	temp->left = tree;
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
	tree = temp;
}

void rotateLR(AVLTree& tree)
{
	rotateRR(tree->left);
	rotateLL(tree);
}

void rotateRL(AVLTree& tree)
{
	rotateLL(tree->right);
	rotateRR(tree);
}

void insertAVLTree(AVLTree& tree, char ch)
{
	if (tree == NULL)
	{
		tree = (AVLTree)malloc(sizeof(AVLNode));
		tree->data = ch;
		tree->height = 1;
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (ch < tree->data)
	{
		insertAVLTree(tree->left, ch);
		tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
		if(getHeight(tree->left) - getHeight(tree->right) == 2)
			if(ch < tree->left->data)
				rotateLL(tree);
			else
				rotateLR(tree);
	}
	else if (ch > tree->data)
	{
		insertAVLTree(tree->right, ch);
		tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
		if(getHeight(tree->right) - getHeight(tree->left) == 2)
			if(ch > tree->right->data)
				rotateRR(tree);
			else
				rotateRL(tree);
	}
}

void printData(AVLTree tree)
{
	cout << tree->data;
}

void preOrderTraverse(AVLTree tree, void (*func)(AVLTree))
{
	if (tree == NULL)
		return;
	func(tree);
	preOrderTraverse(tree->left, func);
	preOrderTraverse(tree->right, func);
}

void inOrderTraverse(AVLTree tree, void (*func)(AVLTree))
{
	if (tree == NULL)
		return;
	inOrderTraverse(tree->left, func);
	func(tree);
	inOrderTraverse(tree->right, func);
}

void postOrderTraverse(AVLTree tree, void (*func)(AVLTree))
{
	if (tree == NULL)
		return;
	postOrderTraverse(tree->left, func);
	postOrderTraverse(tree->right, func);
	func(tree);
}

void inOrderPrint(AVLTree tree, int depth, stack<pair<char, int>>& s)
{
	if(tree == NULL)
		return;
	inOrderPrint(tree->left, depth + 1, s);
	s.push(make_pair(tree->data, depth));
	inOrderPrint(tree->right, depth + 1, s);
}

void PrintTree(AVLTree tree)
{
	stack<pair<char, int>> s;
	inOrderPrint(tree, 0, s);
	cout << "Tree:" << endl;
	while (!s.empty())
	{
		for (int i = 0; i < s.top().second; i++)
			cout << "    ";
		cout << s.top().first << endl;
		s.pop();
	}
}

int main()
{
	char ch;
	cin >> ch;
	AVLTree tree = initAVLTree(ch);
	while (scanf("%c", &ch), ch != '\n')
	{
		insertAVLTree(tree, ch);
		//PrintTree(tree);
	}

	cout << "Preorder: ";
	preOrderTraverse(tree, printData);
	cout << endl;
	cout << "Inorder: ";
	inOrderTraverse(tree, printData);
	cout << endl;
	cout << "Postorder: ";
	postOrderTraverse(tree, printData);
	cout << endl;

	PrintTree(tree);
	return 0;
}

/*
* 练习平衡二叉树的相关操作
* 1. 数据结构方面，注意有一个height域，用于记录当前节点的高度
* 2. 关于插入，注意插入后需要更新当前节点的高度，然后判断是否需要旋转
* 3. 旋转操作有四种，LL, RR, LR, RL，前两种注意并不涉及根节点，只需要修改tree指针即可，同时是从下往上修改指针指向的，否则会断(链表操作)；后两种是前两种的组合
* 
* 错误1：在判断高度时，应该使用getHeight函数，而不是直接访问height域，因为有可能为空指针
*/