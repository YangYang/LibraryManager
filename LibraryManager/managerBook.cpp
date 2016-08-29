#include "StdAfx.h"
#include "managerBook.h"


managerBook::managerBook(CString BookName,CString BookISBN,CString BookPosition)
{
	bookName=BookName;
	bookISBN=BookISBN;
	listPosition=BookPosition;
}


managerBook::~managerBook(void)
{
}
