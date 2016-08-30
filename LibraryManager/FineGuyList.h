#pragma once
//±»³Í·£ÈË µÄ list
class FineGuyList
{
public:
	CString username;
	CString fineTime;
	CString listPosition;
	CString reUsername()
	{
		return username;
	}
	CString reFineTime()
	{
		return fineTime;
	}
	CString reListPosition()
	{
		return listPosition;
	}
	FineGuyList(CString,CString,CString);
	~FineGuyList(void);
	FineGuyList *next;
};

