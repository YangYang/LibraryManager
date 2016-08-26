#include "StdAfx.h"
#include "Book.h"

Book::Book(string isbn,int listposition)
{
	ISBN=isbn;
	listPosition=listposition;
}

Book::Book()
{
}

Book::~Book(void)
{
}

string Book::reISBN()
{
	return ISBN;
}

int Book::reListPosition()
{
	return listPosition;
}