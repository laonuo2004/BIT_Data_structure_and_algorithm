/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct node
{
    ElemType    data;
    struct node* next;
} NODE;
typedef NODE* LinkList;

void output(LinkList);
void change(int, int, NODE*);
LinkList createList(ElemType);
void inverse(LinkList);

LinkList createList(ElemType finish)	//finish：数据结束标记 
{
    ElemType x;
    NODE* newNode;
    LinkList first = new NODE;   // 建立头结点
    first->next = NULL;
    first->data = finish;
    cin >> x;	      			// 约定以finish结束连续输入
    while (x != finish)
    {
        newNode = new NODE;      // 建立新结点
        newNode->data = x;
        newNode->next = first->next; // ①
        first->next = newNode;       // ②
        cin >> x;
    }
    return first;
}

void output(LinkList head)
{
    cout << "List:";
    while (head->next != NULL)
    {
        cout << head->next->data << ",";
        head = head->next;
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    LinkList head;

    head = createList(-1);
    output(head);
    inverse(head);
    output(head);
    return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

void inverse(LinkList head)
{
    LinkList inversed = new NODE;
    inversed->next = NULL;
    inversed->data = head->data;
    LinkList p = head;
    while (p->next != NULL)
    {
        LinkList temp = new NODE;
        temp->data = p->next->data;
        temp->next = inversed->next;
        inversed->next = temp;
        p = p->next;
    }

    head->next = inversed->next;
}