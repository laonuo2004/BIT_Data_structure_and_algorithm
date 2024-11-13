#include <bits/stdc++.h>

using namespace std;

typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode* child, * sibling;
}BiTNode, * BiTree;

BiTree TRoot = NULL;

TElemType temp_root = '#';
vector<int> degree;

void PreOrderTraverse(BiTree T, void(*visit)(TElemType, int), int level)
{
	if (T->data != '#')
	{
		visit(T->data, level);
		PreOrderTraverse(T->child, visit, level + 1);
		PreOrderTraverse(T->sibling, visit, level);
	}
}

void Output(TElemType e, int level)
{
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << e << endl;
}

void DegreeCount(BiTree T)
{
	if (T->data != '#')
	{
		BiTree child = T->child;
		int degree_count = 0;
		while (child->data != '#')
		{
			degree_count++;
			child = child->sibling;
		}
		degree.push_back(degree_count);
		DegreeCount(T->child);
		DegreeCount(T->sibling);
	}
}

void CreateBiTree(BiTree& T, string generalList, int& index, TElemType root)
{
	while (index < generalList.size())
	{
		if (generalList[index] == ',')
			index++;
		else if (generalList[index] >= 'a' && generalList[index] <= 'z')
		{
			T->data = generalList[index];
			T->child = new BiTNode;
			T->sibling = new BiTNode;
			T->child->data = '#';
			T->sibling->data = '#';
			index++;
			CreateBiTree(T->child, generalList, index, T->data);
		}
		else if (generalList[index] == '(')
		{
			//while(T->data != '#') // ֻ�ý�����һ�������ɣ�����һֱ�������ʵ�ϣ�������while�������ѭ������d���ݻ���֮�������½���d
			if(T->data != '#')
				//T = T->sibling; // ���������⣬��������ת���ֵܽڵ㣬���������Ḳ��ԭ�е��ֵܽڵ㣬�������Ľṹ����
				CreateBiTree(T->sibling, generalList, index, root);
			if(generalList[index] != ')') // ���ݹ����в���������index
				index++;
		}
		else if (generalList[index] == ')')
		{
			while (temp_root == '#' || T->data != temp_root) // �����߼���һ��')'�����һ�������Ĵ�����������Ҫ���ݵ���һ�㣬��temp_rootΪ'#'(��һ�λ���)����û�е�����ڵ�ʱ����������
			{
				temp_root = root;
				return;
			}
			temp_root = '#';
			index++;
		}
	}
}

int main()
{
	string generalList;
	cin >> generalList;
	int index = 1;
	TRoot = new BiTNode;
	TRoot->data = '#';
	CreateBiTree(TRoot, generalList, index, '#');
	PreOrderTraverse(TRoot, Output, 0);
	DegreeCount(TRoot);
	if(degree.empty())
	{
		cout << "Degree of tree: 0" << endl;
		cout << "Number of nodes of degree 0: 0" << endl;
		return 0;
	}
	sort(degree.begin(), degree.end());
	cout << "Degree of tree: " << degree[degree.size() - 1] << endl;
	int everyDegree = 0, count = 0;
	for (int i = 0; i < degree.size(); ++i)
	{
		if (degree[i] != everyDegree)
		{
			cout << "Number of nodes of degree " << everyDegree << ": " << count << endl;
			for(int j = everyDegree + 1; j < degree[i]; j++)
				cout << "Number of nodes of degree " << j << ": 0" << endl;
			everyDegree = degree[i];
			count = 1;
		}
		else
			count++;
	}
	cout << "Number of nodes of degree " << everyDegree << ": " << count << endl;
	return 0;
}

/*
* ˼·����������������������Ĺ����������������ʹ�ú����ֵܱ�ʾ��ת��Ϊ�����������������ַ������и����ַ��Ĵ��������£�
* 1. ��ĸ����ʾ���Ľڵ㣬ֱ�Ӹ�ֵ�����ڵ��data����󣬴������ӽڵ���ֵܽڵ㣬��ʼ��Ϊ'#'�����ݹ����CreateBiTree�������뺢�ӣ�ע��root���ݵ�ǰdataֵ��
* 2. ',': ֱ��������
* 3. '(': ִ�е����ַ�֮ǰ���Ѿ�����ָ���Ĳ�Σ���ʱ�����ֵܽڵ㼴�ɣ�������Ҫע�⣬��ת���ֵܽڵ㲻��ֱ�Ӹ�ֵ����ǰ�ڵ㣬���ǵݹ����CreateBiTree��������Ϊ���������õĲ������������ָ�룬����ֱ�����ã�ͬʱע�ⲻ��while����Ϊ���Ա�ֻ֤��Ҫ����һ���ֵܽڵ㣬��while�ᵼ����ѭ����
* 4. ')': �ݹ������������Ҫ���ݣ����ݵ�ʱ����Ҫע������߼�����һ�λ��ݻ���û�е�����ڵ�ʱ���������ݣ�
*/