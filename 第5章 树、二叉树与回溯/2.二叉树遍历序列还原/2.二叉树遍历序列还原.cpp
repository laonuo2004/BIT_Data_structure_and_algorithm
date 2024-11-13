#include <bits/stdc++.h>

using namespace std;

typedef char elemType;

typedef struct BinTreeNode
{
	elemType data;
	struct BinTreeNode *lchild, *rchild;
}BinTreeNode, *BinTree;

// �������Ĵ��������Բ���ȫ�ֱ�����Ҳ�����ַ������зָ����ʹ���ַ���+�����ķ�ʽȷ�����������ķ�Χ
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
	createBinTree(T->lchild, inSequence, postSequence, inStart, rootIndex - 1, postStart, postStart + leftLength - 1); // ע�������ϵ���������ĳ��ȿ����ɸ��ڵ���������������е�λ��ȷ��������������ȷ������������е����������ķ�Χ
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
* �ջ�1����׼��ʹ����������+�������й����������ķ�����������ʹ��ȫ�ֱ�������Ϊȫ�ֱ�����ʹ�ú����������룬�����ڶ��̱߳�̣�ͬʱҲ������ַ������зָ��Ϊ�ָ��ַ���������ʱ�临�Ӷȡ���õķ�����ʹ���ַ���+�����ķ�ʽȷ�����������ķ�Χ��
* �ջ�2����ȷ�����������ķ�Χʱ���������õ�����ϵ�����������ĳ��ȿ����ɸ��ڵ���������������е�λ��ȷ��������������ȷ������������е����������ķ�Χ��
* �ջ�3���������Ĳ�α�����ʹ�ö���ʵ�֣�ÿ��ȡ������Ԫ�أ����ʸ�Ԫ�أ�Ȼ�������Һ�����ӡ���ʵ���ǹ������������
*/