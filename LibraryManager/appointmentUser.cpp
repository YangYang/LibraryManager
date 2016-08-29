#include "StdAfx.h"
#include "appointmentUser.h"


appointmentUser::appointmentUser(CString userName,CString ISBN,CString RETime,CString ListPosition)
{
	username=userName;
	bookISBN=ISBN;
	retime=RETime;
	listPosition=ListPosition;
}


appointmentUser::~appointmentUser(void)
{
}
