#pragma once
//Ä£°åÁ´±íÀà
template <class T> 
class List
{
private:


	T * h;
	int  length;
public:
	T * head;
	T * p;
	List(void)
	{
		length=0;
		head=NULL;
	}
	~List(void)
	{
	}
	int getLength()
	{
		return length;
	}
	void clearList()
	{
		length=0;
		head=NULL;
	}
	T * get(int number)
	{
		if(number>length)
		{
			return new T;
		}
		T * tempPoint;
		tempPoint=head;
		for(int i=0;i<number;i++)
		{
			tempPoint=tempPoint->next;
		}
		return tempPoint;
	}
	void add(T *t)
	{
		if (head == NULL)
		{
			head = t;
			p  = head;
			length++;
		}
		else
		{
			p -> next = t;
			p = p-> next;
			length++;
		}
	}
	void del(T *t)
	{
		if(head==t)
		{
			T *q=head;
			head=head->next;
			delete q;
			return ;
		}
		else
		{
			T *s=head;
			T *q=head->next;
			while(q)
			{
				if(q==t)
				{
					s->next=p->next;
					delete p;
					return ;
				}
				s=s->next;
				q=q->next;
			}
		}
	}
};

