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
			//while(T->data != '#') // 只用建立下一个树即可，不用一直到最后。事实上，这里用while会出现死循环：从d回溯回来之后又重新进入d
			if(T->data != '#')
				//T = T->sibling; // 这里有问题，本意是跳转到兄弟节点，但是这样会覆盖原有的兄弟节点，导致树的结构错误
				CreateBiTree(T->sibling, generalList, index, root);
			if(generalList[index] != ')') // 回溯过程中不增加索引index
				index++;
		}
		else if (generalList[index] == ')')
		{
			while (temp_root == '#' || T->data != temp_root) // 回溯逻辑：一个')'会结束一个子树的创建，所以需要回溯到上一层，当temp_root为'#'(第一次回溯)或者没有到达根节点时，继续回溯
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
* 思路：本题核心在于如何用输入的广义表构建树。树可以使用孩子兄弟表示法转换为二叉树。关于输入字符串当中各种字符的处理方法如下：
* 1. 字母：表示树的节点，直接赋值给树节点的data域。随后，创建孩子节点和兄弟节点，初始化为'#'，并递归调用CreateBiTree函数进入孩子，注意root传递当前data值；
* 2. ',': 直接跳过；
* 3. '(': 执行到该字符之前，已经到了指定的层次，此时创建兄弟节点即可，但是需要注意，跳转到兄弟节点不是直接赋值给当前节点，而是递归调用CreateBiTree函数，因为我们这里用的不是类似链表的指针，而是直接引用；同时注意不用while，因为可以保证只需要创建一个兄弟节点，用while会导致死循环；
* 4. ')': 递归结束条件，需要回溯，回溯的时候需要注意回溯逻辑：第一次回溯或者没有到达根节点时，继续回溯；
*/