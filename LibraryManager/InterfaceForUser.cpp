// InterfaceForUser.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "InterfaceForUser.h"
#include "afxdialogex.h"


// InterfaceForUser 对话框

IMPLEMENT_DYNAMIC(InterfaceForUser, CDialogEx)

InterfaceForUser::InterfaceForUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(InterfaceForUser::IDD, pParent)
	, edit_search(_T(""))


	, select_type(-1)

	, book_number(_T(""))
{

}

InterfaceForUser::~InterfaceForUser()
{
}

void InterfaceForUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, edit_search);
	DDX_Radio(pDX, IDC_RADIO1, select_type);

	DDX_Control(pDX, IDC_LIST1, select_list_box);
	DDX_Text(pDX, IDC_BOOKNUMBER, book_number);
	DDX_Control(pDX, IDOK, control_search_button);
}


BEGIN_MESSAGE_MAP(InterfaceForUser, CDialogEx)

	ON_BN_CLICKED(IDOK, &InterfaceForUser::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &InterfaceForUser::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &InterfaceForUser::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &InterfaceForUser::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &InterfaceForUser::OnBnClickedRadio4)
	ON_EN_CHANGE(IDC_EDIT1, &InterfaceForUser::OnEnChangeEdit1)
END_MESSAGE_MAP()


// InterfaceForUser 消息处理程序




void InterfaceForUser::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL local_mysql;
	
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		return ;
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	CString sql_select;
	
	//图书信息list 置空！
	select_list_box.ResetContent();
	if(select_type==-1)
	{
		all_book_number=0;
		CString cstr=transformPlus.toCString(all_book_number);
		book_number=L"0";
		UpdateData(FALSE);
		AfxMessageBox(_T("请选择搜索方式！"));
		return ;
	}
	if(select_type==1)
	{
		//UpdateData(TRUE);
		sql_select.Format(_T("select * from book where bookName like \'%s\';"),  edit_search);
		string sql_Select=transformPlus.toString(sql_select);
		const char  * sql=sql_Select.c_str();
		int res=mysql_query(&local_mysql,sql);
		MYSQL_RES * result;
		MYSQL_ROW row;
		if(res==0)
		{
			result=mysql_store_result(&local_mysql);
			while(row=mysql_fetch_row(result))
			{
				if(row)
				{
					string bookName=row[3];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.AddString(cstr);
				}
				else
				{
					AfxMessageBox(L"error");
				}
			}
			all_book_number=select_list_box.GetCount();
			CString cstr=transformPlus.toCString(all_book_number);
			if (all_book_number==0)
			{
				book_number=L"";
				//UpdateData(FALSE);
			}
			else if(all_book_number>0)
			{
				book_number.Format(_T("%s"),cstr);
				select_type=-1;
				UpdateData(FALSE);
				return ;
			}
			else
			{
				book_number=L"";
				return ;
			}
		}
		else
		{
			AfxMessageBox(_T("未查询到结果！"));
			return ;
		}
		return ;
	}
	else if(select_type==2)
	{


	}
	else if(select_type==3)
	{

	}
	else if(select_type==4)
	{
		sql_select=("select * from book where bookNum>1;");
		string sql_Select=transformPlus.toString(sql_select);
		const char  * sql=sql_Select.c_str();
		int res=mysql_query(&local_mysql,sql);
		MYSQL_RES * result;
		MYSQL_ROW row;
		if(res==0)
		{
			result=mysql_store_result(&local_mysql);
			while(row=mysql_fetch_row(result))
			{
				if(row)
				{
					/*
					数据库中书名编码为utf8
					在此处汉字可以完美显示
					AddString(LPCTSTR);Unicode编码
					CString 也是Unicode编码
					*/
					string bookName=row[3];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.AddString(cstr);
				}
				else
				{
					AfxMessageBox(L"error");
				}
			}
			all_book_number=select_list_box.GetCount();
			CString cstr=transformPlus.toCString(all_book_number);
			
			if (all_book_number==0)
			{
				book_number=L"0";
			}
			else if(all_book_number>0)
			{
				book_number.Format(_T("%s"),cstr);
				select_type=-1;
				UpdateData(FALSE);
				return ;
			}
			else
			{
				book_number=L"";
				UpdateData(FALSE);
				return ;
			}
			
		}
		else
		{
			AfxMessageBox(_T("未查询到结果！"));
			return ;
		}
	}
	//CDialogEx::OnOK();
}


void InterfaceForUser::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(edit_search=="")
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=1;//书籍名
		control_search_button.EnableWindow(FALSE);
		//UpdateData(FALSE);
		return ;
	}
	else
	{
		control_search_button.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=1;//书籍名0
		//UpdateData(FALSE);
		return ;
	}
}


void InterfaceForUser::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(edit_search=="")
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=2;//书籍名
		control_search_button.EnableWindow(FALSE);
	}
	else
	{
		control_search_button.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=2;//书籍名
		return ;
	}
}


void InterfaceForUser::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(edit_search=="")
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=3;//书籍名
		control_search_button.EnableWindow(FALSE);
	}
	else
	{
		control_search_button.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		select_type=3;//书籍名
		return ;
	}
}


void InterfaceForUser::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	select_type=4;//可借查询
	return ;
}





void InterfaceForUser::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//UpdateData(FALSE);
	if (select_type==-1)
	{
		control_search_button.EnableWindow(FALSE);
		return ;
	}
	else
	{
		control_search_button.EnableWindow(TRUE);
	}
	//UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
}
