/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int    coef, exp;
    struct node* next;
} NODE;

void multiplication(NODE*, NODE*, NODE*);
void input(NODE*);
void output(NODE*);

void input(NODE* head)
{
    int flag, sign, sum, x;
    char c;

    NODE* p = head;

    while ((c = getchar()) != '\n')
    {
        if (c == '<')
        {
            sum = 0;
            sign = 1;
            flag = 1;
        }
        else if (c == '-')
            sign = -1;
        else if (c >= '0' && c <= '9')
        {
            sum = sum * 10 + c - '0';
        }
        else if (c == ',')
        {
            if (flag == 1)
            {
                x = sign * sum;
                sum = 0;
                flag = 2;
                sign = 1;
            }
        }
        else if (c == '>')
        {
            p->next = (NODE*)malloc(sizeof(NODE));
            p->next->coef = x;
            p->next->exp = sign * sum;
            p = p->next;
            p->next = NULL;
            flag = 0;
        }
    }
}

void output(NODE* head)
{
    while (head->next != NULL)
    {
        head = head->next;
        printf("<%d,%d>,", head->coef, head->exp);
    }
    printf("\n");
}

int main()
{
    NODE* head1, * head2, * head3;

    head1 = (NODE*)malloc(sizeof(NODE));
    input(head1);

    head2 = (NODE*)malloc(sizeof(NODE));
    input(head2);

    head3 = (NODE*)malloc(sizeof(NODE));
    head3->next = NULL;
    multiplication(head1, head2, head3);

    output(head3);
    return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

NODE* calculate(NODE*, NODE*);
void insertNode(NODE*, NODE*);
void deleteNode(NODE*);
NODE* position = NULL;

void multiplication(NODE* head1, NODE* head2, NODE* head3)
{
    NODE* p = head1->next;
    while (p)
    {
        NODE* q = head2->next;
        position = head3;
        while (q)
        {
            NODE* temp = calculate(p, q);
            insertNode(temp, head3);
            q = q->next;
        }
        p = p->next;
    }
    if(!head3->next)
	{
        NODE* temp = (NODE*)malloc(sizeof(NODE));
        temp->coef = 0; temp->exp = 0; temp->next = NULL;
        head3->next = temp;
	}
}

NODE* calculate(NODE* p, NODE* q)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->coef = p->coef * q->coef;
	temp->exp = p->exp + q->exp;
	temp->next = NULL;
	return temp;
}

void insertNode(NODE* temp, NODE* head)
{
    if(!temp->coef) return;
    while (position->next)
    {
        if (position->next->exp > temp->exp)
        {
            temp->next = position->next;
            position->next = temp;
            return;
        }
        if (position->next->exp == temp->exp)
        {
            position->next->coef += temp->coef;
            if(!position->next->coef)
                deleteNode(position);
            return;
        }
        position = position->next;
    }
    position->next = temp;
    return;
}

void deleteNode(NODE* p)
{
	NODE* temp = p->next;
	p->next = temp->next;
	free(temp);
}

/*
* 收获1：while (p)与while (p != NULL)是等价的
* 注意1：原先insertNode的时候，位置总是从头开始遍历，时间复杂度O(n^2)，导致超时；仔细观察，会发现对于同一个p而言，q的exp是递增的，所以可以在上一次的基础上继续遍历，时间复杂度O(n)；
*/