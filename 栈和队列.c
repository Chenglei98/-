****************栈和队列****************

栈（Stack）是一个后进先出的线性表，它要求只在表尾进行删除和插入操作。

****************栈的顺序存储结构****************
typede struct
{
	ElemType *base;  //指向栈底指针
	ElemType *top;   //指向栈顶指针
	int stackSize;   //栈当前可使用最大容量
}sqStack;

*创建一个栈：
#define STACK_INIT_SIZE 100
initStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if( !s->base )
		exit(0);
	s->top = s->base;
	s->stackSize = STACK_INIT_SIZE;
}

*入栈操作：
#define SATCKINCREMENT 10

Push(sqStack *s, ElemType e)
{
	//如果栈满，追加空间
	if( s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(s->base, (s->stackSize + SATCKINCREMENT) * sizeof(ElemType));
		if( !s->base )
			exit(0);
		
		s-top = s->base + s->stackSize;  //设置栈顶
		s->stackSize = s->stackSize + SATCKINCREMENT;  //设置栈的最大容量
	}
	
	*(a->top) = e;
	s->top++;
}

*出栈操作：
Pop(sqStack *s, ElemType *e)
{
	if( s->top == s->base )
		return;
	*e = *--(s->top);
}

*清空一个栈：
ClearStack(sqStack *s)
{
	s->top = s->base;
}

*销毁一个栈：
DestroyStack(sqStack *s)
{
	int i, len;
	len = s->stackSize;
	for(i=0; i < len; i++)
	{
		free(s->base);
		s->base++;
	}
	s->base = s->top = NULL;
	s-stackSize = 0;
}

*计算栈的当前容量：
int StackLen(sqStack s)
{
	return(s.top - s.base);
}

************实例分析************
题目：利用栈的数据结构特点，将二进制转变为十进制数。
分析：用第n位去乘2^(n-1),然后相加

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

void InitStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!s->base)
		exit(0);
	s->top = s->base;
	s->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack *s, ElemType e)
{
	if( s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
		if(!s->base)
			exit(0);
	}
	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
	if(s->top == s->base)
		return;
	*e = *--(s->top);
}

int StackLen(sqStack s)
{
	return(s.top - s.base);
}

int main()
{
	ElemType c;
	sqStack s;
	int len, i, sum = 0;
	
	printf("请输入二进制数，输入#符号表示结束！\n");
	scanf("%c",&c);
	while( c != '#')
	{
		Push(&s, c);
		scanf("%c",&c);
	}
	
	getchar();  //清理键盘缓冲区（回车键的ASC码）
	
	len = StackLen(s);
	printf("栈的当前容量是：%d\n",len);
	
	for( i=0; i < len; i++ )
	{
		Pop(&s, &c);
		sum = sum + (c - 48) * pow(2, i);
	}
	
	printf("转换为十进制数是：%d\n",sum);
	
	return 0;
}





************栈的链式存储结构************

typedef struct StackNode
{
	ElemType data;   //存放栈的数据
	struct StackNode *next;
}StackNode, *LinkStackPtr;
typedef struct LinkStack
{
	LinkStackPtr top;   //top指针
	int count;          //栈元素计数器
}

*进栈操作：
Status Push(LinkStack *s, ElemType e)
{
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	p->data = e;
	p->next s->top;
	s->top = p;
	s->count++;
	return OK;
}


*出栈操作：
Status Pop(LinkStack *s, ElemType *e)
{
	LinkStackPtr p;
	if(StackEmpty(*s))  //判断是否为空栈
		return ERROR;
	*e = s->top->data;
	p = s->top;
	s->top = s->top->next;
	free(p);
	s->count--;
	return OK;	
}


****************队列****************
队列（queue）是只允许在一端进行插入操作，而在另一端进行删除操作的线性表。
队列是一种先进先出的线性表

队列的链式存储结构：

typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}QNode, *QueuePrt;
typedef struct
{
	QueuePrt front, rear;  //队头，尾指针
}LinkQueue；


创建一个队列：
initQueue(LinkQueue *q)
{
	q->front = q->rear = (QueuePrt)malloc(sizeof(QNode));
	if( !q->front )
		exit(0);
	q->front->next = NULL;
}

入队列操作：
InsertQueue(LinkQueue *q, ElemType e)
{
	QueuePrt p;
	p = (QueuePrt)malloc(sizeof(QNode));
	if( p == NULL )
		exit(0);
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}

出队列操作；
DeleteQueue(LinkQueue *q, ElemType *e)
{
	QueuePrt p;
	if( q->front == q->rear)
		return;
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	if( q->rear == p )
		q->rear = q->front;
	free(p);
}

销毁队列：
DestroyQueue(LinkQueue *q)
{
	while( q->front )
	{
		q->rear = q->front->next;
		free( q->front );
		q->front = q->rear;
	}
}



循环队列

*定义：
#define MAXSIZE 100
typedef struct
{
	ElemType *base;   //用于存放内存分配基地址
	int front;
	int rear;
}

初始化一个循环队列
initQueue(cycleQueue *q)
{
	q->base = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
	if( !q->base )
		exit(0);
	q->front = q->rear = 0;
}

入队列操作：
InsertQueue(cycleQueue *q, ElemType e)
{
	if((q->rear + 1) % MAXSIZE == q->front)
		return;
	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
}

出队列操作：
DeleteQueue(cycleQueue *q, ElemType *e)
{
	if(q->front == q->rear)
		return;
	*e = q->base[q->front];
	q->front = (q->front + 1) % MAXSIZE;
}
