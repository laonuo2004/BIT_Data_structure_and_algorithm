#include <bits/stdc++.h>

using namespace std;

typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree initBinarySortTree(int data)
{
	BiTree tree = (BiTree)malloc(sizeof(BiTNode));
	tree->data = data;
	tree->lchild = NULL;
	tree->rchild = NULL;
	return tree;
}

void insertBinarySortTree(BiTree& tree, int data)
{
	if(tree == NULL)
	{
		tree = (BiTree)malloc(sizeof(BiTNode));
		tree->data = data;
		tree->lchild = NULL;
		tree->rchild = NULL;
	}
	else if(data < tree->data)
		insertBinarySortTree(tree->lchild, data);
	else if(data > tree->data)
		insertBinarySortTree(tree->rchild, data);
}

void inOrderPrint(BiTree tree, int depth, queue<int>& q)
{
	if(tree == NULL)
		return;
	inOrderPrint(tree->lchild, depth + 1, q);
	for(int i = 0; i < depth; i++)
		cout << "    ";
	cout << tree->data << endl;
	q.push(tree->data);
	inOrderPrint(tree->rchild, depth + 1, q);
}

int main()
{
	int data;
	cin >> data;
	BiTree tree = initBinarySortTree(data);
	while(cin >> data, data)
		insertBinarySortTree(tree, data);
	queue<int> q;
	inOrderPrint(tree, 0, q);
	cout << endl;
	while(!q.empty())
	{
		cout << " " << q.front();
		q.pop();
	}
	cout << endl;
	return 0;
}