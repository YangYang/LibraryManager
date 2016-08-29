#pragma once
class managerBook
{
public:
	CString bookName;
	CString bookISBN;
	CString listPosition;
	CString reBookName()
	{
		return bookName;
	}
	CString reBookISBN()
	{
		return bookISBN;
	}
	CString reListBookPosition()
	{
		return listPosition;
	}
	managerBook(CString,CString,CString);
	~managerBook(void);
	managerBook *next;
};

