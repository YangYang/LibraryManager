#include "StdAfx.h"
#include "Book.h"

Book::Book(string isbn,string listposition)
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

string Book::reListPosition()
{
	return listPosition;
}