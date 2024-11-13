#include <iostream>
using namespace std;

typedef struct ListNode
{
	int number;
	struct ListNode* next;
}node, * pnode;

pnode createList(int n)
{
	pnode head = new node;
	head->number = 1;
	head->next = NULL;
	pnode last = head;
	for (int i = 2; i <= n; ++i)
	{
		pnode current = new node;
		current->number = i;
		current->next = NULL;
		last->next = current;
		last = current;
	}
	last->next = head;
	return last;
}

void deleteNode(pnode& current)
{
	pnode temp = current->next;
	current->next = temp->next;
	delete temp;
}

int main()
{
	int n, k, m;
	char ch;
	cin >> n >> ch >> k >> ch >> m;
	if (n < 1 || k < 1 || m < 1)
		cout << "n,m,k must bigger than 0." << endl;
	else if (k > n)
		cout << "k should not bigger than n." << endl;
	else
	{
		pnode current = createList(n);
		for(int i = 1; i < k; ++i)
			current = current->next;
		for (int i = 1; i < n; ++i)
		{
			for(int j = 1; j < m; ++j)
				current = current->next;
			cout << current->next->number << (i % 10 ? " " : "\n");
			deleteNode(current);
		}
		cout << current->number << endl;
	}
	return 0;
}

/*
* 思路：约瑟夫环问题，使用循环链表解决即可。
* 收获1：如何快速地构建循环链表？递推建表，最后将尾结点的next指向头结点即可，注意返回值为last而非head，主要是为了方便删除操作。
*/