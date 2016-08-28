// AboutYourBookMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "AboutYourBookMessage.h"
#include "afxdialogex.h"


// AboutYourBookMessage 对话框

IMPLEMENT_DYNAMIC(AboutYourBookMessage, CDialogEx)

AboutYourBookMessage::AboutYourBookMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutYourBookMessage::IDD, pParent)
	, book_name(_T(""))
	, book_author(_T(""))
	, book_press(_T(""))
	, book_ISBN(_T(""))
	, book_type(_T(""))
	, book_date(_T(""))
	, return_book_time(_T(""))
{

}

AboutYourBookMessage::~AboutYourBookMessage()
{
}

void AboutYourBookMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOKNAMETEXT, book_name);
	DDX_Text(pDX, IDC_BOOKAUTHORTEXT, book_author);
	DDX_Text(pDX, IDC_BOOKPRESSTEXT, book_press);
	DDX_Text(pDX, IDC_BOOKISBNTEXT, book_ISBN);
	DDX_Text(pDX, IDC_BOOKTYPETEXT, book_type);
	DDX_Control(pDX, IDC_BOOKNAMETEXT, control_book_name);
	DDX_Control(pDX, IDC_BOOKAUTHORTEXT, control_book_author);
	DDX_Control(pDX, IDC_BOOKPRESSTEXT, control_book_press);
	DDX_Control(pDX, IDC_BOOKISBNTEXT, control_book_ISBN);
	DDX_Control(pDX, IDC_BOOKTYPETEXT, control_book_type);
	DDX_Text(pDX, IDC_BOOKDATETEXT, book_date);
	DDX_Control(pDX, IDC_BOOKDATETEXT, control_book_date);
	DDX_Control(pDX, IDC_RETIMETEXT, control_return_book_time);
	DDX_Text(pDX, IDC_RETIMETEXT, return_book_time);
}


BEGIN_MESSAGE_MAP(AboutYourBookMessage, CDialogEx)
	ON_BN_CLICKED(IDOK, &AboutYourBookMessage::OnBnClickedOk)
END_MESSAGE_MAP()


// AboutYourBookMessage 消息处理程序


void AboutYourBookMessage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL AboutYourBookMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		//AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	CString bookName;
	CString bookAuthor;
	CString bookPress;
	CString bookISBN;
	CString bookType;
	CString bookDate;
	CString reBookTime;
	CString sql_select;
	sql_select.Format(_T("select * from book where ISBN=\'%s\';"),transformPlus.toCString(list.head->reISBN()));
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row ;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			bookName=row[3];
			bookAuthor=row[4];
			bookPress=row[5];
			bookDate=row[6];
			bookISBN=row[7];
			bookType=row[2];
			control_book_name.SetWindowText(bookName);
			control_book_name.ShowWindow(TRUE);
			control_book_author.SetWindowText(bookAuthor);
			control_book_author.ShowWindow(TRUE);
			control_book_press.SetWindowText(bookPress);
			control_book_press.ShowWindow(TRUE);
			control_book_date.SetWindowText(bookDate);
			control_book_date.ShowWindow(TRUE);
			control_book_ISBN.SetWindowText(bookISBN);
			control_book_ISBN.ShowWindow(TRUE);
			control_book_type.SetWindowText(bookType);
			control_book_type.ShowWindow(TRUE);
			CString sql_query;
			sql_query.Format(_T("select * from user_book where username=\'%s\' and bookISBN=\'%s\';"),loginUser,transformPlus.toCString(list.head->reISBN()));
			temp=transformPlus.toString(sql_query);
			sql=temp.c_str();
			if(mysql_query(&local_mysql,sql)==0)
			{
				res=mysql_store_result(&local_mysql);
				row=mysql_fetch_row(res);
				reBookTime=row[3];
				long REBookTime=transformPlus.toLong(reBookTime);

				time_t t;
				struct tm *p;
				t=REBookTime+28800;//不加28800是格林尼治时间 中国在第八时区，需要加八小时
				p=gmtime(&t);
				char s[80];
				strftime(s, 80, "%Y-%m-%d %H:%M:%S", p);
				reBookTime=transformPlus.toCString(s);
				control_return_book_time.SetWindowText(reBookTime);
				control_return_book_time.ShowWindow(TRUE);
				return TRUE;
			}
			else
			{
				return FALSE;
			}
			return TRUE;
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
