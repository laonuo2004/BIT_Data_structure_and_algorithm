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
* �ջ�1��С����ѭ��С���������ʾ����
* �ջ�2��˫ָ�뷨�������������ļ�¼��
* ע��1��ԭ�ȵ�ʮ����������ȥ������Ϊm���󣬵���logs��������ڴ治�㣬Ȼ��ʵ�ʿռ������ʺܵͣ���˸�������
* ע��2������ʹ���������⣬������һ�ָĽ�������������m��С�������ۡ��������ԣ����ֵ�ʮ��������m��Χ��5E8��1E9֮�䣬��mС��5E8ʱ������ֱ��ʹ��logs���飻��m����5E8ʱ�����Բ�����ѭ���ڼ�飬ֱ�ӿ�һ���ܴ�������¼����С��λ����(�Ƚ�ȡ�ɵķ��������㣬�������Բ�ǿ����������������԰���)��
*/