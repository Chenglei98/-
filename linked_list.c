*************线性表链式存储结构************

*************获取链表第i个数据*************
-声明一个结点p指向链表第一个结点，初始化j从1开始
-当j<i时，就遍历链表，让P的指针向后移动，不断指向下一个结点j+1
-若到链表末尾p为空，则说明第i个元素不存在；否则查找成功，返回结点P的数据
 
typedef struct Node
{
	ElemType data;      //数据域
	struct Note* Next;  //指针域
}Node;
typedef struct Node* LinkList;

Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;
	
	p = L -> next;
	j = 1;
	
	while( p && j < i ) 
	{
		p = p -> next;
		++j;
	}
	if(!p || j > i)
	{
		return ERROR;
	}
	*e = p -> data;
	
	return OK;
}


*************单链表的插入*************
-s->next = p->next;
-p->next = s;

单链表第i个数据插入结点算法思路：
-声明一个结点p指向链表头结点，初始化j从1开始；
-当 j<i 时，遍历链表，让p的指针向后移动，指向下一个结点，j累加1；
-若到链表末尾p为空，则说明第i个元素不存在；
-否则查找成功，在系统中生成一个空结点s;
-将数据元素e赋值给s->data;
-单链表插入刚才两个标准语句（s->next = p->next;p->next = s;）
-返回成功；

Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p , s;
	p = *L;
	j = 1;
	
	while( p && j < i )    //用于寻找第i个结点
	{
		p = p->next;
		j++;
	}
	
	if( !p || j>i )
	{
		return ERROR;
	}
	
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	
	s->next = p->next;
	p->next = s;
	
	return Ok;
}


*************单链表的删除*************
假设元素A2的结点q，要实现结点q删除单链表的操作，其实就是将它的前继结点的指针绕过指向后继结点即可。
p->next = p->next->next;

单链表第i个数据删除结点算法思路：
-声明结点p指向链表头结点，初始化j从1开始；
-当 j<i 时，遍历链表，让p的指针向后移动，指向下一个结点，j累加1；
-若到链表末尾p为空，则说明第i个元素不存在；
-否则查找成功，将欲删除结点p->next赋值给q；
-单链表的删除标准语句p->next = q->next；
-将q结点中的数据赋值给e，作为返回；
-释放q结点；

Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p , q;
	p = *L;
	j = 1;
	
	while( p->next && j < i )    //用于寻找第i个结点
	{
		p = p->next;
		++j;
	}
	
	if( !(p->next) || j>i )
	{
		return ERROR;
	}
	
	q = p->next;
	p->next = q->next;
	
	*e = q->data;
	free(q);
	
	return Ok;
}



*************单链表的整表创建的算法思路*************
-声明一结点p和计数器变量i；
-初始化一空链表L；
-让L的头结点的指针指向NULL，即建立一个带头结点的单链表；
-循环实现后继结点的赋值和插入；

*************头插法*************
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	
	srand(time(0));      //初始化随机数种子
	
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	
	for( i=0; i<n; i++ )
	{
		p = (LinkList)malloc(sizeof(Node));    //生成新结点
		p->data = rand()%100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}


*************尾插法*************
void CreateListTail(LinkList *L, int n)
{
	LinkList p , r;
	int i;
	
	srand(time(0));      //初始化随机数种子
	
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	
	for( i=0; i<n; i++ )
	{
		p = (Node*)malloc(sizeof(Node));    //生成新结点
		p->data = rand()%100 + 1;
		r->next = p;
		r = p;     
	}
	r->next = NULL;
}


*************单链表的整表删除的算法思路*************
-声明结点p和q；
-将第一个结点赋值给P，下一个结点赋值给q;
-循环执行释放p和将q赋值给p的操作；

Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;
	
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	
	(*L)->next = NULL;
	
	return OK;
}


存储分配方式：
-顺序存储结构用一段连续的存储单元依次存储线性表的数据元素。
-单链表采用链式存储结构，用一组任意的存储单元存放线性表的元素。

时间性能：
-查找
*顺序存储结构O(1)
*单链表O(n)
-插入和删除
*顺序存储结构O(n)
*单链表O(1)
空间性能：
-顺序存储结构需要预分配存储空间
-单链表不需要分配存储空间


静态链表优缺点总结
*优点：在插入和删除操作时，只需要修改游标，不需要移动元素，从而改进了在
顺序存储结构中的插入和删除操作需要移动大量元素的缺点
*缺点：没有解决连续存储分配（数组）带来的表长难以确定的问题
失去了顺序存储结构随机存取的特性



**********腾讯面试题***********
题目：快速找到未知长度单链表的中间结点（判断单链表中是否有环也可以使用快慢指针）
思路：快慢指针原理：设置两个指针*search, *mid都指向单链表的头节点
其中*search的移动速度是*mid的2倍。当*search指向末尾结点的时候，
*mid正好就在中间了，这也是标尺的思想
快慢指针代码：

status GetMidNode(LinkList L, ElemType *e)
{
	LinkList search, mid;
	mid = search = L;
	
	while(search->next != NULL)
	{
		if(search->next->next != NULL)
		{
			search = search->next->next;
			mid = mid->next;
		}
		else
		{
			search = search->next;
		}
	}
	
	*e = mid->data;
	return OK;
}



*************双向链表*************

typedef struct DualNode
{
	ElemType data;
	struct DualNode *prior;    //前驱结点
	struct DualNode *next;     //后继结点
}DualNode, *DuLinkList;



**********双向循环链表实践**********
题目-要求实现用户输入一个数使得26个字母排列发生变化，例如用户输入3
     输出结果：DEFGHIJKLMNOPQRSTUVWXYZABC
	-同时需要支持负数，例如-3 结果XYZABCDEFGHIJKLMNOPQRSTUVW


#include <stdio.h>
#include <stdlib.h>

#define OK     1
#define ERROR  0

typedef char ElemType;
typedef int Status;

typedef struct DualNode
{
	ElemType data;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode, *DuLinkList;

Status InitList(DuLinkList *L)
{
	DualNode *p, *p;
	int i;
	
	*L = (DuLinkList)malloc(sizeof(DualNode));
	if( !(*L) )
		return ERROR;
	
	(*L)->next = (*L)->prior = NULL;
	p = (*L);
	
	for(i=0; i<26; i++)
	{
		q = (DualNode *)malloc(sizeof(DualNode));
		if(!q)
			return ERROR;
		q->data = 'A' + i;
		q->prior = p;
		q->next = p->next;
		p->next = q;
		p = q;
	}
	p->next = (*L)->next;
	(*L)->next->prior = p;

	return OK;
}

void Caesar(DuLinkList *L, int i)
{
	if( i > 0)
	{
		do
		{
			(*L) = (*L)->next;
		}while(--i);
	}
	
	if( i < 0 )
	{
		(*L) = (*L)->next->prior->prior;
		while(++i)
		{
			(*L) = (*L)->prior;
		}				
	}
}


int main(void)
{
	DuLinkList L;
	int i;

	InitList(&L);
	printf("请输入一个整数：");
	scanf("%d",&n);
	printf("\n");
	Caesar(&L, n);
	
	for( i=0; i<26; i++)
	{
		L = L->next;
		printf("%c", L->data);
	}
	
	return 0;
}













