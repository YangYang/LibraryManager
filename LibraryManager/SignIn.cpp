// SignIn.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "SignIn.h"
#include "afxdialogex.h"


// SignIn 对话框

IMPLEMENT_DYNAMIC(SignIn, CDialogEx)

SignIn::SignIn(CWnd* pParent /*=NULL*/)
	: CDialogEx(SignIn::IDD, pParent)
	, new_username(_T(""))
	, new_password(_T(""))
	, confirm_password(_T(""))
	, new_name(_T(""))
	, new_type(_T(""))
	, new_unit(_T(""))
	, textCheck(_T(""))
	, checkUsername(_T(""))
	, confirmPassword(_T(""))
{

}

SignIn::~SignIn()
{
}

void SignIn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, new_username);
	DDX_Text(pDX, IDC_EDIT3, new_password);
	DDX_Text(pDX, IDC_EDIT4, new_name);
	DDX_Text(pDX, IDC_EDIT4, confirm_password);
	DDX_Text(pDX, IDC_EDIT2, new_name);
	DDX_CBString(pDX, IDC_COMBO2, new_type);
	DDX_Text(pDX, IDC_EDIT5, new_unit);
	DDX_Text(pDX, IDC_CHECK, textCheck);
	DDX_Text(pDX, IDC_CHECKUSERNAME, checkUsername);
	DDX_Text(pDX, IDC_CONFIRMPASS, confirmPassword);
	DDX_Control(pDX, IDC_EDIT4, ct_confirm_password);
}


BEGIN_MESSAGE_MAP(SignIn, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &SignIn::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &SignIn::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT3, &SignIn::OnEnChangeEdit3)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &SignIn::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT4, &SignIn::OnEnChangeEdit4)
END_MESSAGE_MAP()


// SignIn 消息处理程序


void SignIn::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void SignIn::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(new_password!=confirm_password)
	{
		AfxMessageBox(_T("两次输入的密码不一致！"));
		return ;
	}
	UpdateData(FALSE);
	//连接数据库
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
	UpdateData(TRUE);
	CString sql_insert;
	CString type;
	if (new_type==L"本科生")
	{
		type='1';
	} 
	else if(new_type==L"研究生")
	{
		type='2';
	}
	else if(new_type==L"博士生")
	{
		type='3';
	}
	else if(new_type==L"教师")
	{
		type='4';
	}
	sql_insert.Format(_T("insert into user values (\'\', \'%s\', \'%s\', \'%s\' , \'%s\' , \'%s\' );"), new_username,new_password,new_name,new_unit,type);
	string sql_Insert=transformPlus.toString(sql_insert);
	const char  * sql=sql_Insert.c_str();
	if(mysql_query(&local_mysql,sql)==0)
	{   
		MessageBox(_T("注册成功！"));   
	}else{
		AfxMessageBox(_T("注册失败！"));
	}
	CDialogEx::OnOK();
}

void SignIn::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//连接mysql
	UpdateData(TRUE);
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

	//查询
	MYSQL_RES * result;
	MYSQL_ROW  row;
	CString sql_query;
	sql_query.Format(_T("select * from user where username=\'%s\';"),new_username);
	string sql_Query=transformPlus.toString(sql_query);
	const char  * sql=sql_Query.c_str();
	int res=mysql_query(&local_mysql,sql);
	if(res==0)
	{
		result=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(result);
		if(row)
		{
			checkUsername = L"此用户已存在";
			GetDlgItem(IDOK)->EnableWindow(FALSE);
			UpdateData(FALSE);
			return ;
		}
		else
		{
			checkUsername = L"";
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			UpdateData(FALSE);
			return ;
		}
	}
	else
	{
		checkUsername = L"";
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		UpdateData(FALSE);
		return ;
	}
	
}


void SignIn::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (new_password.GetLength() < 6)
	{
		textCheck = L"密码必须大于6位";
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
	else{
		textCheck = L"";
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


HBRUSH SignIn::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(pWnd->GetDlgCtrlID() == IDC_CHECK || pWnd->GetDlgCtrlID() == IDC_CHECKUSERNAME)
	{
		pDC->SetTextColor(RGB(255,0,0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void SignIn::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	if (new_password != confirm_password)
	{
		confirmPassword = "两次输入密码不一致";
	}
	else{
		confirmPassword = "";
	}
	UpdateData(FALSE);*/
}