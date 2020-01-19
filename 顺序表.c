*************线性表顺序存储结构**************

*************获取顺序表第i个数据*************

typedef int Status;

Status GetElem(SqList L, int i, ElemType *e)
{
	if(L.length == 0 || i < 1 || i>L.length)
	{
		retur ERROR;
	}
	*e = L.data[i-1];
	
	return OK;
}

*************在L中第i个位置前插入数据元素e**************

Status ListInsert(SqList *L, int i, ElemType e)
{
	int k;
	
	if(L->length == MAXSIZE)
	{
		return ERROR;
	}
	
	if(i < 1 || i > L->length + 1)
	{
		return ERROR;
	}
	
	if(i <= L->length)
	{
		for(k = L->length - 1; k >= i - 1; k--)
		{
			L->data[k+1] = L->data[k];
		}
	}
	
	L->data[i-1] = e;
	L->length++;
	
	return OK;
}