#pragma once
class badGuyList
{
public:
	CString listPosition;
	CString username;
	CString name;
	CString rePosition()
	{
		return listPosition;
	}
	CString reUsername()
	{
		return username;
	}
	CString reName()
	{
		return name;
	}
	badGuyList(CString UserName,CString ListPosition,CString Name);
	~badGuyList(void);
	badGuyList *next;
};

