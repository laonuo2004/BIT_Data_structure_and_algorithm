#include <bits/stdc++.h>

using namespace std;

typedef char elemType;

typedef struct BinTreeNode
{
	elemType data;
	struct BinTreeNode *lchild, *rchild;
}BinTreeNode, *BinTree;

// �������Ĵ���
void createBinTree(BinTreeNode*& T, vector<elemType>& data, int& i) // �ݹ鴴����������ע�����ʹ���ַ�����+����i�ķ�ʽ��ȡȡ������Ԫ��
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

// �������İ�������
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

// �����������
void output(BinTreeNode* T)
{
	cout << T->data;
}

// �������ı�����ʹ�ú���ָ����Ϊ��������ߴ��븴���ԡ�ע�⺯��ָ���ʹ�ã��������ʱ����д��������ֻд�������ͼ��ɡ�
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

// ���������Ҷ�ӽ�����
int leaves = 0;

void leafCount(BinTreeNode* T)
{
	if(!T->lchild && !T->rchild)
		leaves++;
}

// ��ת������
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
* �ջ�1�����������������Ĳ����У�BinTreeNode*& T����ʾ�������ָ������ã������ں����ڲ���T���޸Ļ�Ӱ�쵽�ⲿ��T�����ֻ��BinTreeNode* T����ô��T���޸�ֻ���ں����ڲ���Ч����ʱ�����ʹ�÷���ֵ�����޸ĺ��T��
* �ջ�2��������������ʱ�򣬿���ʹ���ַ�����+����i�ķ�ʽ��ȡȡ������Ԫ�أ�
* �ջ�3���������ı�����ʹ�ú���ָ����Ϊ��������ߴ��븴���ԡ�ע�⺯��ָ���ʹ�ã��������ʱ����д��������ֻд�������ͼ��ɣ�
* ����1��ע���ڷ�ת��������ʱ��Ӧ��ѡ��������ߺ�������������������������Ϊ��������ᵼ�����������Ľ��������������ֽ����������������ٴν��������ջ���ԭ��������
*/