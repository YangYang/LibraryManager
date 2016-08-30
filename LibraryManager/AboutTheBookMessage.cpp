// AboutTheBookMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "AboutTheBookMessage.h"
#include "afxdialogex.h"


// AboutTheBookMessage 对话框

IMPLEMENT_DYNAMIC(AboutTheBookMessage, CDialogEx)

AboutTheBookMessage::AboutTheBookMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutTheBookMessage::IDD, pParent)
{

}

AboutTheBookMessage::~AboutTheBookMessage()
{
}

void AboutTheBookMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutTheBookMessage, CDialogEx)
END_MESSAGE_MAP()


// AboutTheBookMessage 消息处理程序


BOOL AboutTheBookMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	CString sql_query;
	sql_query.Format(_T("select * from book where ISBN=\'%s\';"),theBookNode->reBookISBN());
	string temp=transformPlus.toString(sql_query);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		GetDlgItem(IDC_BOOKNAME)->SetWindowText(transformPlus.toCString(row[3]));
		GetDlgItem(IDC_BOOKNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKAUTHOR)->SetWindowText(transformPlus.toCString(row[4]));
		GetDlgItem(IDC_BOOKAUTHOR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKPRESS)->SetWindowText(transformPlus.toCString(row[5]));
		GetDlgItem(IDC_BOOKPRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKDATE)->SetWindowText(transformPlus.toCString(row[6]));
		GetDlgItem(IDC_BOOKDATE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BOOKPRICE)->SetWindowText(transformPlus.toCString(row[9]));
		GetDlgItem(IDC_BOOKPRICE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKNUMBER)->SetWindowText(transformPlus.toCString(row[1]));
		GetDlgItem(IDC_BOOKNUMBER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKTYPE)->SetWindowText(transformPlus.toCString(row[2]));
		GetDlgItem(IDC_BOOKTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BOOKISBN)->SetWindowText(transformPlus.toCString(row[7]));
		GetDlgItem(IDC_BOOKISBN)->ShowWindow(SW_SHOW);

	}
	else
	{
		return FALSE;
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
