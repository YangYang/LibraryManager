// FineGuyMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "FineGuyMessage.h"
#include "afxdialogex.h"


// FineGuyMessage 对话框

IMPLEMENT_DYNAMIC(FineGuyMessage, CDialogEx)

FineGuyMessage::FineGuyMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(FineGuyMessage::IDD, pParent)
{

}

FineGuyMessage::~FineGuyMessage()
{
}

void FineGuyMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FineGuyMessage, CDialogEx)
END_MESSAGE_MAP()


// FineGuyMessage 消息处理程序


BOOL FineGuyMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	CString sql_query;
	sql_query.Format(_T("select * from user where username=\'%s\';"),theGuy->reUsername());
	string temp=transformPlus.toString(sql_query);
	const char * sql=temp.c_str();
	MYSQL_RES	*res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			GetDlgItem(IDC_USERNAME)->SetWindowText(transformPlus.toCString(row[1]));
			GetDlgItem(IDC_USERNAME)->ShowWindow(TRUE);
			GetDlgItem(IDC_NAME)->SetWindowText(transformPlus.toCString(row[3]));
			GetDlgItem(IDC_NAME)->ShowWindow(TRUE);
			GetDlgItem(IDC_CLASS)->SetWindowText(transformPlus.toCString(row[4]));
			GetDlgItem(IDC_CLASS)->ShowWindow(TRUE);
			CString TYPE;
			if(transformPlus.toString(row[5])=="1")
			{
				TYPE="本科生";
			}
			else if(transformPlus.toString(row[5])=="2")
			{
				TYPE="研究生";
			}
			else if(transformPlus.toString(row[5])=="3")
			{
				TYPE="博士生";
			}
			else if(transformPlus.toString(row[5])=="4")
			{
				TYPE="教师";
			}
			GetDlgItem(IDC_TYPE)->SetWindowText(TYPE);
			GetDlgItem(IDC_TYPE)->ShowWindow(TRUE);
			CString haveBooks;
			haveBooks.Format(_T("%s%s"),transformPlus.toCString(row[6]),transformPlus.toCString("本"));
			GetDlgItem(IDC_HAVEBOOKS)->SetWindowText(haveBooks);
			GetDlgItem(IDC_HAVEBOOKS)->ShowWindow(TRUE);


			CString wrongTimes;
			time_t t;
			struct tm *p;
			t=transformPlus.toLong(theGuy->reFineTime())+28800;//不加28800是格林尼治时间 中国在第八时区，需要加八小时
			p=gmtime(&t);
			char s[80];
			strftime(s, 80, "%Y-%m-%d %H:%M:%S", p);
			wrongTimes=transformPlus.toCString(s);

			GetDlgItem(IDC_WRONGTIMES)->SetWindowText(wrongTimes);
			GetDlgItem(IDC_WRONGTIMES)->ShowWindow(TRUE);

		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
