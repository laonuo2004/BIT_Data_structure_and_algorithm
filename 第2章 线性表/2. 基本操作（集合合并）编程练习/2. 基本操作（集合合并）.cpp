#define _CRT_SECURE_NO_WARNINGS

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
#define LIST_MAX_SIZE  100	//�ռ��ʼ��С
#define OK 1
#define ERROR 0

typedef int ElemType;    	//Ԫ�ص���������
typedef int Status;			//״̬����������ֵ 
typedef struct {
	// 	ElemType elem[ LIST_MAX_SIZE ]; // �洢�ռ�
	ElemType* elem; 	// �洢�ռ�
	int  length;        // ��ǰԪ�ظ���
	int  listsize;		// �ܹ���������Ԫ������ 
} SqList;

// ����Ϊ����ԭ�� 
Status InitList(SqList&);
Status ListInsert(SqList&, int, ElemType);	//������Ҫ���д�Ļ������� 
Status GetElem(SqList, int, ElemType&);	//������Ҫ���д�Ļ������� 
int	   ListLength(SqList);		//������Ҫ���д�Ļ�������
Status ListTraverse(SqList&, void (*)(ElemType));
void   ListUnion(SqList&, SqList);
void   out(ElemType);
int    equal(ElemType, ElemType);
Status LocateElem(SqList, ElemType, Status(*)(ElemType, ElemType));

// ����Ϊ��������
Status InitList(SqList& L) 	// ����һ���յ����Ա� L
{
	L.elem = (ElemType*)malloc(LIST_MAX_SIZE * sizeof(ElemType));
	//  if ( !L.elem )	exit(-1);	// ʧ������ֹ���� 
	L.length = 0;   			// �ձ���Ϊ0
	L.listsize = LIST_MAX_SIZE;
	return OK;
}

Status ListTraverse(SqList& L, void (*visit)(ElemType))
{	// ���ζ�L��ÿ��Ԫ�ص��ú���visit()����visit()ʧ�ܣ������ʧ��
	int i, L_len = ListLength(L);
	ElemType e;

	for (i = 1; i <= L_len; i++) {
		GetElem(L, i, e);
		(*visit)(e);
	}
	return OK;
}

int equal(ElemType x, ElemType y)
{
	return x == y;
}

Status LocateElem(SqList L, ElemType e,
	Status(*compare)(ElemType, ElemType))
{	//��L�в�����Ԫ�� e ����compare() �ĵ� 1 ��Ԫ��
	//���� L �е� 1 ���� e �����ϵcompare( ) ��Ԫ�ص�λ��
	int i = 1;
	ElemType* p;
	while (i <= L.length)  //
		if ((*compare)(e, L.elem[i - 1])) break;
		else  i++;
	if (i <= L.length)  return i;  // �ҵ� e������λ��i
	else return 0;		//��û���ҵ����򷵻�0
}

void out(ElemType e)
{
	printf("%d,", e);
}

void ListUnion(SqList& La, SqList Lb) //�� A��A��B
{
	int La_len, Lb_len, i;
	ElemType e;

	La_len = ListLength(La);       // �����Ա�ĳ���
	Lb_len = ListLength(Lb);
	for (i = 1; i <= Lb_len; i++) {
		GetElem(Lb, i, e);  // ȡLb�е�i������Ԫ�ظ���e
		if (!LocateElem(La, e, equal))
			ListInsert(La, ++La_len, e);	// La�в����ں� e ��ͬ������Ԫ�أ������
	}
}

int main()
{
	SqList La, Lb;
	int n, i;
	ElemType e;

	InitList(La);
	InitList(Lb);
	scanf("%d", &n);		//���뼯��A 
	for (i = 0; i < n; i++)
	{
		scanf("%d", &e);
		ListInsert(La, i + 1, e);
	}
	scanf("%d", &n);		//���뼯��B 
	for (i = 0; i < n; i++)
	{
		scanf("%d", &e);
		ListInsert(Lb, i + 1, e);
	}
	printf("Output La:");
	ListTraverse(La, out);
	printf("\nOutput Lb:");
	ListTraverse(Lb, out);
	ListUnion(La, Lb);
	printf("\nResult La:");
	ListTraverse(La, out);
	printf("\n");
	return OK;
}

/****************
Status ListInsert( SqList &L, int i, ElemType e )
{  	//��˳�����Ա�L�е� i (1��i��L.length+1)��λ��֮ǰ����Ԫ��e,

	Here is wating for you.

}

Status GetElem(SqList L, int i, ElemType &e)
{

	Here is wating for you.

}

int ListLength(SqList L)
{

	Here is wating for you.

}
*********************/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

Status ListInsert(SqList& L, int i, ElemType e)
{  	//��˳�����Ա�L�е� i (1��i��L.length+1)��λ��֮ǰ����Ԫ��e,
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length >= L.listsize) return ERROR;
	ElemType* q = &(L.elem[i - 1]);
	for(ElemType* p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}

Status GetElem(SqList L, int i, ElemType& e)
{
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}

int ListLength(SqList L)
{
	return L.length;
}

/*
* �ջ�1��typedef int ElemType, Status:��������ĺô��ǣ�����Ժ�ElemType/Status��������Ҫ�ı䣬ֻ��Ҫ�ı�typedef�Ķ��弴�ɣ�����Ҫ�ı����е�int����;
* �ջ�2���ṹ��Ķ��壺typedef struct { ElemType* elem; int length; int listsize; } SqList;��Ϊʲô��ֱ��malloc?��Ϊ����������������˼�룬�������������װ��һ������������ߴ���ĸ�����������ԣ�
* �ջ�3������ָ���ʹ�ã�����ָ��Ķ��壺void (*visit)(ElemType)��Status (*compare)(ElemType, ElemType)������ָ��ĵ��ã�(*visit)(e)��(*compare)(e, L.elem[i - 1])��������ߴ���ĸ�����������ԣ�
* �ջ�4�������ı�д�����Ⱦ�Ҫ�ǵ��ų��쳣��������緶Χ���ԡ��ռ䲻���ȵȣ�
*/