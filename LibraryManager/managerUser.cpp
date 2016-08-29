#include "StdAfx.h"
#include "managerUser.h"


managerUser::managerUser(CString UserName,CString Name,CString ListPosition)
{
	username=UserName;
	name=Name;
	listPosition=ListPosition;
}

managerUser::managerUser(CString UserName ,CString ListPosition)
{
	username=UserName;
	name="";
	listPosition=ListPosition;
}

managerUser::~managerUser(void)
{
}
