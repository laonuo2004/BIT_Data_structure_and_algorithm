#define _CRT_SECURE_NO_WARNINGS

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
#define LIST_MAX_SIZE  100	//空间初始大小
#define OK 1
#define ERROR 0

typedef int ElemType;    	//元素的数据类型
typedef int Status;			//状态。函数返回值 
typedef struct {
	// 	ElemType elem[ LIST_MAX_SIZE ]; // 存储空间
	ElemType* elem; 	// 存储空间
	int  length;        // 当前元素个数
	int  listsize;		// 能够保存的最大元素数量 
} SqList;

// 以下为函数原型 
Status InitList(SqList&);
Status ListInsert(SqList&, int, ElemType);	//这是需要你编写的基本操作 
Status GetElem(SqList, int, ElemType&);	//这是需要你编写的基本操作 
int	   ListLength(SqList);		//这是需要你编写的基本操作
Status ListTraverse(SqList&, void (*)(ElemType));
void   ListUnion(SqList&, SqList);
void   out(ElemType);
int    equal(ElemType, ElemType);
Status LocateElem(SqList, ElemType, Status(*)(ElemType, ElemType));

// 以下为函数定义
Status InitList(SqList& L) 	// 建立一个空的线性表 L
{
	L.elem = (ElemType*)malloc(LIST_MAX_SIZE * sizeof(ElemType));
	//  if ( !L.elem )	exit(-1);	// 失败则终止程序 
	L.length = 0;   			// 空表长度为0
	L.listsize = LIST_MAX_SIZE;
	return OK;
}

Status ListTraverse(SqList& L, void (*visit)(ElemType))
{	// 依次对L的每个元素调用函数visit()。若visit()失败，则操作失败
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
{	//在L中查找与元素 e 满足compare() 的第 1 个元素
	//返回 L 中第 1 个与 e 满足关系compare( ) 的元素的位序
	int i = 1;
	ElemType* p;
	while (i <= L.length)  //
		if ((*compare)(e, L.elem[i - 1])) break;
		else  i++;
	if (i <= L.length)  return i;  // 找到 e，返回位序i
	else return 0;		//若没有找到，则返回0
}

void out(ElemType e)
{
	printf("%d,", e);
}

void ListUnion(SqList& La, SqList Lb) //求 A＝A∪B
{
	int La_len, Lb_len, i;
	ElemType e;

	La_len = ListLength(La);       // 求线性表的长度
	Lb_len = ListLength(Lb);
	for (i = 1; i <= Lb_len; i++) {
		GetElem(Lb, i, e);  // 取Lb中第i个数据元素赋给e
		if (!LocateElem(La, e, equal))
			ListInsert(La, ++La_len, e);	// La中不存在和 e 相同的数据元素，则插入
	}
}

int main()
{
	SqList La, Lb;
	int n, i;
	ElemType e;

	InitList(La);
	InitList(Lb);
	scanf("%d", &n);		//读入集合A 
	for (i = 0; i < n; i++)
	{
		scanf("%d", &e);
		ListInsert(La, i + 1, e);
	}
	scanf("%d", &n);		//读入集合B 
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
{  	//在顺序线性表L中第 i (1≤i≤L.length+1)个位置之前插入元素e,

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
{  	//在顺序线性表L中第 i (1≤i≤L.length+1)个位置之前插入元素e,
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
* 收获1：typedef int ElemType, Status:这样定义的好处是，如果以后ElemType/Status的类型需要改变，只需要改变typedef的定义即可，不需要改变所有的int定义;
* 收获2：结构体的定义：typedef struct { ElemType* elem; int length; int listsize; } SqList;；为什么不直接malloc?因为这体现了面向对象的思想，将数据与操作封装在一起，这样可以提高代码的复用性与灵活性；
* 收获3：函数指针的使用：函数指针的定义：void (*visit)(ElemType)、Status (*compare)(ElemType, ElemType)；函数指针的调用：(*visit)(e)、(*compare)(e, L.elem[i - 1])；可以提高代码的复用性与灵活性；
* 收获4：函数的编写：首先就要记得排除异常情况！例如范围不对、空间不够等等；
*/