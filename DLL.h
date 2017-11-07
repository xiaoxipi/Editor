#pragma once

#include<iostream>
using namespace std;

template<class ElemType>
class DblNode
{
public:
	ElemType data;
	DblNode<ElemType>*back;
	DblNode<ElemType>*next;

	DblNode();
	DblNode(ElemType item, DblNode<ElemType>*linkBack = NULL, DblNode<ElemType>*linkNext = NULL);
};
template<class ElemType>
DblNode<ElemType>::DblNode()
{
	back=next = NULL;
}
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType>*linkBack, DblNode<ElemType>*linkNext)
{
	data = item;
	back = linkBack;
	next = linkNext;
}



template<class ElemType>
class DblLinkList
{
protected:
	mutable int curPosition;
	mutable DblNode<ElemType>*curPtr;
	int count;
	DblNode<ElemType>*head;

	DblNode<ElemType>* GetElemPtr(int position) const;

public:
	DblLinkList();
	virtual~DblLinkList();
	int Length()const;
	bool Empty()const;
	void Clear();
	void Traverse(void(*visit)(const ElemType&))const;
	bool GetElem(int position, ElemType&e)const ;
	bool SetElem(int position, const ElemType&e);
	bool Delete(int position, ElemType&e);
	bool Insert(int position, const ElemType&e);
	DblLinkList(const DblLinkList<ElemType>&copy);
	DblLinkList<ElemType>&operator=(const DblLinkList<ElemType>&copy);
};

template<class ElemType>
DblLinkList<ElemType>& DblLinkList<ElemType>::operator=(const DblLinkList<ElemType>&copy)
{
	if (&copy != this)
	{
		Clear();
		if (!copy.Empty())
		{
			DblNode<ElemType>* tmpPtr = copy.head;
			for (int i = 1; i <= copy.Length(); i++)
			{
				tmpPtr = tmpPtr->next;
				Insert(Length() + 1, tmpPtr->data);
			}
		}
	}
	return *this;
}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType>&copy)
{
	if (&copy != this)
	{
		curPtr=head = new DblNode<ElemType>;
		count = 0;
		if (copy.Empty())
			return;
		else
		{
			DblNode<ElemType>* tmpPtr = copy.head;
			for (int i = 1; i <= copy.Length(); i++)
			{
				tmpPtr = tmpPtr->next;
				Insert(Length() + 1, tmpPtr->data);
			}
		}
	}
}

template<class ElemType>
void DblLinkList<ElemType>::Traverse(void(*visit)(const ElemType&))const
{
	DblNode<ElemType>*tmpPtr = head;
	for (int i = 1; i <= Length(); i++)
	{
		tmpPtr = tmpPtr->next;
		visit(tmpPtr->data);
		//cout << endl;
	}
}

template<class ElemType>
bool DblLinkList<ElemType>::GetElem(int position, ElemType&e)const
{
	if (position<1 || position>Length())
		return false;
	else
	{
		DblNode<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(position);
		e = tmpPtr->data;
		return true;
	}
}

template<class ElemType>
bool DblLinkList<ElemType>::SetElem(int position,const ElemType&e)
{
	if (position<1 || position>Length())
		return false;
	else
	{
		DblNode<ElemType>*tmpPtr = GetElemPtr(position);
		tmpPtr->data = e;
		return true;
	}
}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList()
{
	curPtr = head = new DblNode<ElemType>;
    count = curPosition = 0;
}

template<class ElemType>
bool DblLinkList<ElemType>::Empty() const 
{
	return count == 0;
}


template<class ElemType>
DblNode<ElemType>* DblLinkList<ElemType>::GetElemPtr(int position)const
{
	if (curPosition<position)
	{
		for (; curPosition<position; curPosition++)
		{
			curPtr = curPtr->next;
		}
	}
	else if (curPosition>position)
	{
		for (; curPosition>position; curPosition--)
		{
			curPtr = curPtr->back;
		}
	}
	return curPtr;
}

template<class ElemType>
int DblLinkList<ElemType>::Length()const
{
	return count;
}

template<class ElemType>
bool DblLinkList<ElemType>::Delete(int position, ElemType&e)
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);//!
		tmpPtr = tmpPtr->next;
		tmpPtr->back->next = tmpPtr->next;
		if(tmpPtr->next!=NULL)
			tmpPtr->next->back = tmpPtr->back;

		//tmpPtr->next->back = tmpPtr->back;
		e = tmpPtr->data;
		if (position == Length())
		{
			curPosition = 0;
			curPtr = head;
		}
		else
		{
			curPosition = position-1;//!
			curPtr = tmpPtr->back;
		}
		count--;
		delete tmpPtr;
		return true;
	}
}

template<class ElemType>
void DblLinkList<ElemType>::Clear()
{
	ElemType e;
	curPosition = 0;
	curPtr = head;
	int len = Length();
	for (int i = 1; i <= len; i++)
	{
		Delete(1, e);
	}
}

template<class ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	Clear();
	delete head;
	head = curPtr = NULL;
}

template <class ElemType>
bool DblLinkList<ElemType>::Insert(int position, const ElemType&e)
{
	if (position<1 || position>Length() + 1)
	{
		return false;
	}
	else
	{
		DblNode<ElemType>*tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);
		nextPtr = tmpPtr->next;
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);

		//nextPtr = tmpPtr->next;
		//newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);
		tmpPtr->next = newPtr;
		if(nextPtr!=NULL)
			nextPtr->back = newPtr;
		curPosition = position;
		curPtr = newPtr;
		count++;
		return true;
	}
}
