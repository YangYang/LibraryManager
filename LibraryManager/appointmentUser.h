#pragma once
//预约者信息的List
class appointmentUser
{
public:
	CString username;
	CString bookISBN;
	CString retime;
	CString listPosition;
	CString reListPosition()
	{
		return listPosition;
	}
	CString reUsername()
	{
		return username;
	}
	CString reISBN()
	{
		return bookISBN;
	}
	CString reTime()
	{
		return retime;
	}
	appointmentUser *next;
	appointmentUser(CString,CString,CString,CString);
	~appointmentUser(void);
};

