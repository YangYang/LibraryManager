#include "StdAfx.h"
#include "userBook.h"

userBook::userBook(string isbn,int listposition,string name)
{
	ISBN=isbn;
	listPosition=listposition;
	bookName=name;
}

userBook::userBook()
{
}

userBook::~userBook(void)
{
}

string userBook::reISBN()
{
	return ISBN;
}

int userBook::reListPosition()
{
	return listPosition;
}

string userBook::reBookName()
{
	return bookName;
}