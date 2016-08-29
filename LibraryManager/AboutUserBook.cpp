// AboutUserBook.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "AboutUserBook.h"
#include "afxdialogex.h"


// AboutUserBook 对话框

IMPLEMENT_DYNAMIC(AboutUserBook, CDialogEx)

AboutUserBook::AboutUserBook(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutUserBook::IDD, pParent)
{

}

AboutUserBook::~AboutUserBook()
{
}

void AboutUserBook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutUserBook, CDialogEx)
END_MESSAGE_MAP()


// AboutUserBook 消息处理程序


BOOL AboutUserBook::OnInitDialog()
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
	sql_query.Format(_T("select * from book where ISBN=\'%s\';"),ISBN);//transformPlus.toCString(userBookMessage->reISBN()));
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
			GetDlgItem(IDC_BOOKNAMETEXT)->SetWindowText(transformPlus.toCString(row[3]));
			GetDlgItem(IDC_BOOKNAMETEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKAUTHORTEXT)->SetWindowText(transformPlus.toCString(row[4]));
			GetDlgItem(IDC_BOOKAUTHORTEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKPRESSTEXT)->SetWindowText(transformPlus.toCString(row[5]));
			GetDlgItem(IDC_BOOKPRESSTEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKDATETEXT)->SetWindowText(transformPlus.toCString(row[6]));
			GetDlgItem(IDC_BOOKDATETEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKNUMBERTEXT)->SetWindowText(transformPlus.toCString(row[1]));
			GetDlgItem(IDC_BOOKNUMBERTEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKISBNTEXT)->SetWindowText(transformPlus.toCString(row[7]));
			GetDlgItem(IDC_BOOKISBNTEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKTYPETEXT)->SetWindowText(transformPlus.toCString(row[2]));
			GetDlgItem(IDC_BOOKTYPETEXT)->ShowWindow(TRUE);
			GetDlgItem(IDC_BOOKPRICETEXT)->SetWindowText(transformPlus.toCString(row[9]));
			GetDlgItem(IDC_BOOKPRICETEXT)->ShowWindow(TRUE);
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
