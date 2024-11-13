#define _CRT_SECURE_NO_WARNINGS

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int         data;
	struct node* next;
} NODE;

void output(NODE*, int);
void change(int, int, NODE*);

void output(NODE* head, int kk)
{
	int k = 0;

	printf("0.");
	while (head->next != NULL && k < kk)
	{
		printf("%d", head->next->data);
		head = head->next;
		k++;
	}
	printf("\n");
}

int main()
{
	int n, m, k;
	NODE* head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;
	change(n, m, head);
	output(head, k);
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

typedef struct record
{
	int data;
	struct record* next;
	struct node* position;
} RECORD;

RECORD* find(RECORD* head, int n)
{
	RECORD* temp = head;
	while (temp->next != NULL)
	{
		if (temp->next->data == n)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void change(int n, int m, NODE* head)
{
	//NODE* logs = (NODE*)malloc(sizeof(NODE) * m);
	//NODE* rear = head;
	//for (int i = 0; i < m; ++i)
	//{
	//	logs[i].next = NULL;
	//	logs[i].data = 0;
	//}
	//while (n)
	//{
	//	if (logs[n].next != NULL)
	//	{
	//		rear->next = logs[n].next;
	//		free(logs);
	//		return;
	//	}
	//	NODE* temp = (NODE*)malloc(sizeof(NODE));
	//	temp->data = n * 10 / m;
	//	temp->next = NULL;
	//	logs[n].next = temp;
	//	rear->next = temp;
	//	rear = temp;
	//	n = n * 10 % m;
	//}
	//free(logs);
	RECORD* logs = (RECORD*)malloc(sizeof(RECORD));
	logs->position = head;  logs->next = NULL;  logs->data = -1;
	NODE* rear = head;
	while (n)
	{
		if(find(logs, n) != NULL)
		{
			rear->next = find(logs, n)->next->position;
			free(logs);
			return;
		}
		RECORD* record = (RECORD*)malloc(sizeof(RECORD));
		NODE* temp = (NODE*)malloc(sizeof(NODE));
		record->next = NULL;  record->position = temp;  record->data = n;
		record->next = logs->next;  logs->next = record;
		temp->data = n * 10 / m;  temp->next = NULL;
		rear->next = temp; rear = temp;
		n = n * 10 % m;
	}
	return;
}

/*
* 收获1：小数与循环小数的链表表示法；
* 收获2：双指针法进行链表索引的记录；
* 注意1：原先第十个样例过不去，是因为m过大，导致logs数组过大，内存不足，然而实际空间利用率很低，因此改用链表；
* 注意2：除了使用链表以外，还有另一种改进方法，即根据m大小分类讨论。经过测试，发现第十个样例的m范围在5E8到1E9之间，当m小于5E8时，可以直接使用logs数组；当m大于5E8时，可以不进行循环节检查，直接开一个很大的链表记录各个小数位即可(比较取巧的方法，方便，但适用性不强，处理这个样例可以罢了)；
*/