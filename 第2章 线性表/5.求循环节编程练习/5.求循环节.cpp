#define _CRT_SECURE_NO_WARNINGS

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int         data;
	struct node* next;
} NODE;

NODE* find(NODE*, int*);
void outputring(NODE*);
void change(int, int, NODE*);
void outputring(NODE* pring)
{
	NODE* p;
	p = pring;
	if (p == NULL)
		printf("NULL");
	else
		do {
			printf("%d", p->data);
			p = p->next;
		} while (p != pring);
	printf("\n");
	return;
}

int main()
{
	int n, m;
	NODE* head, * pring;

	scanf("%d%d", &n, &m);
	head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;

	change(n, m, head);
	pring = find(head, &n);
	printf("ring=%d\n", n);
	outputring(pring);

	return 0;
}

/* Here is waiting for you.
void change( int n, int m, NODE * head )
{
}

NODE * find( NODE * head, int * n )
{
}
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

typedef struct record
{
	int data;
	struct record* next;
	struct node* position;
} RECORD;

RECORD* logs = (RECORD*)malloc(sizeof(RECORD));

RECORD* check(RECORD* head, int n)
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
	logs->position = head;  logs->next = NULL;  logs->data = 0;
	NODE* rear = head;
	while (n)
	{
		if (check(logs, n) != NULL)
		{
			rear->next = check(logs, n)->next->position;
			check(logs, n)->next->data = -1;
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

NODE* find(NODE* head, int* n)
{
	*n = 0;
	RECORD* temp = logs;
	while (temp->next != NULL)
	{
		if (temp->next->data == -1)
		{
			*n = 1;
			NODE* p = temp->next->position, * q = p;
			while (q->next != p)
			{
				*n += 1;
				q = q->next;
			}
			return p;
		}
		temp = temp->next;
	}
	return NULL;
}