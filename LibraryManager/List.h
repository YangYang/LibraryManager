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
};

