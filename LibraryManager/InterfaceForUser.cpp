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
	, book_name(_T(""))
	, book_author(_T(""))
	, book_press(_T(""))
	, book_date(_T(""))
	, book_type(_T(""))
	, book_about(_T(""))
	, book_ISBN(_T(""))
	, name_text(_T(""))
	, type_text(_T(""))
	, username_text(_T(""))
{
	thisNode=NULL;
	thisUserBookNode=NULL;
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
	DDX_Control(pDX, IDC_BOOKNUMBER, control_book_number);
	DDX_Text(pDX, IDC_BOOKNAMETEXT, book_name);
	DDX_Text(pDX, IDC_BOOKAUTHERTEXT, book_author);
	DDX_Text(pDX, IDC_BOOKPRESSTEXT, book_press);
	DDX_Text(pDX, IDC_BOOKDATETEXT, book_date);
	DDX_Text(pDX, IDC_BOOKTYPETEXT, book_type);
	DDX_Text(pDX, IDC_ABOUTBOOKTEXT, book_about);
	DDX_Control(pDX, IDC_BOOKNAMETEXT, control_book_name);
	DDX_Control(pDX, IDC_BOOKAUTHERTEXT, control_book_author);
	DDX_Control(pDX, IDC_BOOKPRESSTEXT, control_book_press);
	DDX_Control(pDX, IDC_BOOKDATETEXT, control_book_date);
	DDX_Control(pDX, IDC_BOOKTYPETEXT, control_book_type);
	DDX_Control(pDX, IDC_ABOUTBOOKTEXT, control_book_about);
	DDX_Text(pDX, IDC_BOOKISBNTEXT, book_ISBN);
	DDX_Control(pDX, IDC_BOOKISBNTEXT, control_book_ISBN);
	DDX_Control(pDX, IDC_USERNAME, control_name);
	DDX_Control(pDX, IDC_USERTYPE, control_type);
	DDX_Control(pDX, IDC_USERUSERNAME, control_username);
	DDX_Text(pDX, IDC_USERNAME, name_text);
	DDX_Text(pDX, IDC_USERTYPE, type_text);
	DDX_Text(pDX, IDC_USERUSERNAME, username_text);
	DDX_Control(pDX, IDC_EDIT1, control_edit_text);
	DDX_Control(pDX, IDC_LIST3, user_book_list);
}


BEGIN_MESSAGE_MAP(InterfaceForUser, CDialogEx)

	ON_BN_CLICKED(IDOK, &InterfaceForUser::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &InterfaceForUser::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &InterfaceForUser::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &InterfaceForUser::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &InterfaceForUser::OnBnClickedRadio4)
	ON_EN_CHANGE(IDC_EDIT1, &InterfaceForUser::OnEnChangeEdit1)
	ON_LBN_SELCHANGE(IDC_LIST1, &InterfaceForUser::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &InterfaceForUser::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &InterfaceForUser::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST3, &InterfaceForUser::OnLbnSelchangeList3)
	ON_BN_CLICKED(IDC_BUTTON3, &InterfaceForUser::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &InterfaceForUser::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &InterfaceForUser::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &InterfaceForUser::OnBnClickedButton6)
END_MESSAGE_MAP()


// InterfaceForUser 消息处理程序



//搜索 button
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
	
	//图书信息list,被选中的Node 置空！
	select_list_box.ResetContent();
	thisNode=NULL;
	if(select_type==-1)
	{
		all_book_number=0;
		CString cstr=transformPlus.toCString(all_book_number);
		book_number=L"0";
		//UpdateData(FALSE);
		control_book_number.SetWindowText(L"0");
		AfxMessageBox(_T("请选择搜索方式！"));
		return ;
	}
	if(select_type==1)
	{
		UpdateData(TRUE);
		//每次搜索时都要清空链表
		list.clearList();
		sql_select.Format(_T("select * from book where bookName like \'%%%s%%\';"),  edit_search);
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
					string bookISBN=row[7];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.InsertString(-1,cstr);


					//将图书数据存入list
					if(judge>=0)
					{
						Book * newNode=new Book(bookISBN,judge);
						list.add(newNode);
						list.p->next=NULL;
					}
					else
					{
						AfxMessageBox(_T("Out of memory!"));
					}
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
				AfxMessageBox(_T("没有查到您想要的书"));
				control_book_number.SetWindowText(L"0");
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
			control_book_number.SetWindowText(L"0");
			return ;
		}
		return ;
	}
	else if(select_type==2)
	{
		UpdateData(TRUE);
		//每次搜索时都要清空链表
		list.clearList();
		sql_select.Format(_T("select * from book where ISBN = %s;"),  edit_search);
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
					string bookISBN=row[7];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.InsertString(-1,cstr);


					//将图书数据存入list
					if(judge>=0)
					{
						Book * newNode=new Book(bookISBN,judge);
						list.add(newNode);
						list.p->next=NULL;
					}
					else
					{
						AfxMessageBox(_T("Out of memory!"));
					}
				}
				else
				{
					AfxMessageBox(L"error");
					control_book_number.SetWindowText(L"0");
				}
			}
			all_book_number=select_list_box.GetCount();
			CString cstr=transformPlus.toCString(all_book_number);
			if (all_book_number==0)
			{
				book_number=L"";
				AfxMessageBox(_T("没有查到您想要的书"));
				control_book_number.SetWindowText(L"0");
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
			control_book_number.SetWindowText(L"0");
			return ;
		}
		return ;

	}
	else if(select_type==3)
	{
		UpdateData(TRUE);
		//每次搜索时都要清空链表
		list.clearList();
		sql_select.Format(_T("select * from book where type = \'%s\';"),  edit_search);
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
					string bookISBN=row[7];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.InsertString(-1,cstr);


					//将图书数据存入list
					if(judge>=0)
					{
						Book * newNode=new Book(bookISBN,judge);
						list.add(newNode);
						list.p->next=NULL;
					}
					else
					{
						AfxMessageBox(_T("Out of memory!"));
					}
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
				AfxMessageBox(_T("没有查到您想要的书"));
				control_book_number.SetWindowText(L"0");
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
			control_book_number.SetWindowText(L"0");
			return ;
		}
		return ;
	}
	else if(select_type==4)
	{
		//每次搜索时都要清空链表
		list.clearList();
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
					string bookISBN=row[7];
					CString cstr=transformPlus.toCString(bookName);
					int judge=select_list_box.InsertString(-1,cstr);


					//将图书数据存入list
					if(judge>=0)
					{
						Book * newNode=new Book(bookISBN,judge);
						list.add(newNode);
						list.p->next=NULL;
					}
					else
					{
						AfxMessageBox(_T("Out of memory!"));
					}
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
				AfxMessageBox(_T("没有查到您想要的书"));
				control_book_number.SetWindowText(L"0");
			}
			else if(all_book_number>0)
			{
				book_number.Format(_T("%s"),cstr);
				select_type=-1;
				//UpdateData(FALSE);
				control_book_number.SetWindowText(book_number);
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
			control_book_number.SetWindowText(L"0");
			return ;
		}
	}
	//CDialogEx::OnOK();
}

//书籍名
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

//ISBN button
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

//中图分类号button
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

//可借出书籍button
void InterfaceForUser::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
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

//点击 list box control
void InterfaceForUser::OnLbnSelchangeList1()
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


	CString cstrText;
	int selectedTextNumber;
	selectedTextNumber=select_list_box.GetCurSel();//获取当前选中列表项
	//MessageBox(transformPlus.toCString(selectedTextNumber));
	/*
	根据selectTextNumber 检索list 中对应的节点，查找对应的isbn 查找对应的书籍的所有信息
	*/
	Book *head=list.head;
	
	if(head==NULL)
	{
		AfxMessageBox(_T("error!"));
		return ;
	}
	else
	{
		while(head)
		{
			if(head->reListPosition()==selectedTextNumber)
			{
				thisNode=head;
				break;
			}
			head=head->next;
		}
	}
	CString sql_select;
	sql_select.Format(_T("select * from book where ISBN =\'%s\'"),transformPlus.toCString(thisNode->reISBN()));
	string sql_Select=transformPlus.toString(sql_select);
	const char  * sql=sql_Select.c_str();
	int res=mysql_query(&local_mysql,sql);
	MYSQL_RES * result;
	MYSQL_ROW row;
	if(res==0)
	{
		result=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(result);
		book_name=row[3];
		book_author=row[4];
		book_press=row[5];
		book_date=row[6];
		book_ISBN=row[7];
		book_type=row[2];
		book_about=row[10];
		control_book_name.SetWindowText(book_name);
		control_book_author.SetWindowText(book_author);
		control_book_press.SetWindowText(book_press);
		control_book_date.SetWindowText(book_date);
		control_book_ISBN.SetWindowText(book_ISBN);
		control_book_type.SetWindowText(book_type);
		control_book_about.SetWindowText(book_about);
		return ;
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return ;
	}
	/*
	select_list_box.GetText(selectedTextNumber,cstrText);//获取当前选中字符串 赋值给cstrText
	book_name=cstrText;
	control_book_name.SetWindowText(book_name);
	*/
}

//图书数量减一
int InterfaceForUser::reduceBookNumber(string bookISBN,MYSQL local_mysql)
{
	CString sql_select ;
	sql_select.Format(_T("select * from book where ISBN=\'%s\';"),transformPlus.toCString(bookISBN));
	string str=transformPlus.toString(sql_select);
	const char * sql=str.c_str();
	MYSQL_RES * res;
	MYSQL_ROW row;
	int RES=mysql_query(&local_mysql,sql);
	if(RES==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			string number=row[1];
			int Number=transformPlus.toInt(number);
			Number--;
			CString NUMBER=transformPlus.toCString((Number));
			CString sql_update;
			sql_update.Format(_T("update book set bookNum = \'%s\' where ISBN=\'%s\' ;"),NUMBER,transformPlus.toCString(bookISBN));
			string SQL=transformPlus.toString(sql_update);
			const char * SQL_update=SQL.c_str();
			int result=mysql_query(&local_mysql,SQL_update);
			if(result==0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		MessageBox(L"请求错误！");
		return 0;
	}
}

//user 图书数量减一
int InterfaceForUser::reduceUserBookNumber(string username,MYSQL local_mysql)
{
	CString sql_select;
	sql_select.Format(_T("select * from user where username=\'%s\';"),transformPlus.toCString(username));
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			int number =transformPlus.toInt(row[6]);
			number--;
			CString sql_update;

			sql_update.Format(_T("update user set bookNumber=\'%s\' where username= \'%s\';"),transformPlus.toCString(number),transformPlus.toCString(username));
			temp=transformPlus.toString(sql_update);
			sql=temp.c_str();
			if(mysql_query(&local_mysql,sql)==0)
			{
				return 1;
			}
			else
			{
				AfxMessageBox(_T("errorrrrrrr!"));
				return 0;
			}
		}
		else
		{
			AfxMessageBox(_T("error!!!!!!!!!!!!!!!"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("er!"));
		return 0;
	}
}

//图书数量加一
int InterfaceForUser::addBookNumber(string bookISBN,MYSQL local_mysql)
{
	CString sql_select ;
	sql_select.Format(_T("select * from book where ISBN=\'%s\';"),transformPlus.toCString(bookISBN));
	string str=transformPlus.toString(sql_select);
	const char * sql=str.c_str();
	MYSQL_RES * res;
	MYSQL_ROW row;
	int RES=mysql_query(&local_mysql,sql);
	if(RES==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			string number=row[1];
			int Number=transformPlus.toInt(number);
			Number++;
			CString NUMBER=transformPlus.toCString((Number));
			CString sql_update;
			sql_update.Format(_T("update book set bookNum = \'%s\' where ISBN=\'%s\' ;"),NUMBER,transformPlus.toCString(bookISBN));
			string SQL=transformPlus.toString(sql_update);
			const char * SQL_update=SQL.c_str();
			int result=mysql_query(&local_mysql,SQL_update);
			if(result==0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		MessageBox(L"请求错误！");
		return 0;
	}
}

//用户书籍数量加一
int InterfaceForUser::addUserBookNumber(CString username,MYSQL local_mysql)
{
	CString sql_select;
	sql_select.Format(_T("select * from user where username=\'%s\';"),username);
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(!row)
		{
			return 0;
		}
		string Number =transformPlus.toString(row[6]);
		int number=transformPlus.toInt(Number);
		number++;
		Number=transformPlus.toString(number);
		CString sql_update;
		sql_update.Format(_T("update user set bookNumber=\'%s\' where username=\'%s\' ;"),transformPlus.toCString(Number),username);
		temp=transformPlus.toString(sql_update);
		sql=temp.c_str();
		if(mysql_query(&local_mysql,sql)==0)
		{
			return 1;
		}
		else
		{
			AfxMessageBox(_T("errorrrr!"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("error1"));
		return 0;
	}
}

//借书
void InterfaceForUser::borrowBook(string userType,string userBookNumber,MYSQL local_mysql)
{
	string staticNumber;
	if(userType=="1")
	{
		staticNumber="4";
	}
	else if(userType=="2")
	{
		staticNumber="6";
	}
	else if(userType=="3")
	{
		staticNumber="10";
	}
	else if(userType=="4")
	{
		staticNumber="999999";
	}
	if(userBookNumber>=staticNumber)
	{
		MessageBox(L"借书量已达上限，请归还部分书籍后进行借阅！");
		return ;
	}
	else
	{
		//判断书籍数量
		MYSQL_ROW Row;
		MYSQL_ROW row;
		MYSQL_RES *result;
		CString sql_query;
		sql_query.Format(_T("select * from book where ISBN=%s ;"),transformPlus.toCString(thisNode->reISBN()));
		string sql_Query=transformPlus.toString(sql_query);
		const char  * SQL=sql_Query.c_str();
		int Res=mysql_query(&local_mysql,SQL);
		if(Res==0)
		{
			result=mysql_store_result(&local_mysql);
			Row=mysql_fetch_row(result);
			if(Row)
			{

				if(transformPlus.toInt(Row[1])>1)
				{	
					CString sql_query;
					sql_query.Format(_T("select * from user_book where username= \'%s\';"),loginUser);
					sql_Query=transformPlus.toString(sql_query);
					SQL=sql_Query.c_str();
					Res=mysql_query(&local_mysql,SQL);
					if(Res==0)
					{
						int judge=0;
						result=mysql_use_result(&local_mysql);
						while(row=mysql_fetch_row(result))
						{
							if(row)
							{
								if(transformPlus.toString(row[2])==thisNode->reISBN())
								{
									judge=1;
									break ;
								}
							}
						}
						if(judge==1)
						{
							MessageBox(L"您已借阅此图书，不可重复借阅！");
							return ;
						}
						else
						{
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
							//应还时间reTime
							time_t now_time=time(0);
							CString cstrNowTime;
							cstrNowTime.Format(_T("%d"),now_time);
							long time_long=transformPlus.toLong(cstrNowTime);
							time_long+=2592000;
							CString reTime;
							reTime=transformPlus.toCString(time_long);
							//插入
							CString sql_insert;
							sql_insert.Format(_T("insert into user_book values (\'\',\'%s\',\'%s\',\'%s\');"),loginUser,transformPlus.toCString(thisNode->reISBN()),reTime);
							string sql_Insert=transformPlus.toString(sql_insert);
							const char  * SQL_insert=sql_Insert.c_str();
							if(mysql_query(&local_mysql,SQL_insert)==0)
							{   
								int number=0;
								MYSQL_RES * Result;
								MYSQL_ROW ROW;
								CString sql_search;
								sql_search.Format(_T("select * from user_book where username = \'%s\';"),loginUser);
								string sql_Search=transformPlus.toString(sql_search);
								const char * search=sql_Search.c_str();
								if(mysql_query(&local_mysql,search)==0)
								{
									Result=mysql_store_result(&local_mysql);
									while(ROW=mysql_fetch_row(Result))
									{
										if(ROW)
										{
											number++;
										}
									}
								}
								else
								{
									AfxMessageBox(_T("error313131312!"));
									return ;
								}
								CString sql_update;
								sql_update.Format(_T("update user set bookNumber =\'%s\'  where username =\'%s\'; "),transformPlus.toCString(number),loginUser);
								string sql_Update=transformPlus.toString(sql_update);
								const char * update=sql_Update.c_str(); 
								if(mysql_query(&local_mysql,update)==0)
								{
									int reJudge=reduceBookNumber(thisNode->reISBN(),local_mysql);
									if(reJudge==1)
									{
										MessageBox(_T("借阅成功！"));  
										OnInitDialog();
										return ;
									}
									else
									{
										AfxMessageBox(_T("借阅失败！"));
										return ;
									}
								}
								else
								{
									AfxMessageBox(_T("借阅失败！"));
									return ;
								}
							}
							else
							{
								AfxMessageBox(_T("借阅失败！"));
								return ;
							}
							return ;
						}
					}
					else
					{
						AfxMessageBox(_T("error!!!!!!!!!!!"));
						return ;
					}

					return ;
				}
				else
				{	//书籍数量不足
					MessageBox(L"该书籍馆藏量不足！");
					return ;
				}
			}
			else
			{
				AfxMessageBox(_T("errrrrrror"));
				return ;
			}
		}
		else
		{
			AfxMessageBox(_T("query error!"));
			return ;
		}
	}
}

//借阅button
/*

0.判断该人可借书籍数量是否可借
2.判断书籍数量是否大于1
3.存入对应表单
4.已有书籍数量减一


*/

int InterfaceForUser::judgeUserInFineListOrNot()
{
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
	sql_query.Format(_T("select * from user_finetime;"));
	string temp=transformPlus.toString(sql_query);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		while(row=mysql_fetch_row(res))
		{
			if(transformPlus.toCString(row[1])==loginUser)
			{
				fineTime=transformPlus.toCString(row[2]);
				return 1;
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
void InterfaceForUser::OnBnClickedButton1()
{
	//选了书籍
	int judgeLoginUser=judgeUserInFineListOrNot();
	if(judgeLoginUser==1)
	{
		CString reBookTime;
		struct tm *p;
		time_t t;
		t=transformPlus.toLong(fineTime)+28800;
		p=gmtime(&t);
		char s[80];
		strftime(s, 80, "%Y-%m-%d %H:%M:%S", p);
		reBookTime=transformPlus.toCString(s);
		CString text;
		text.Format(_T("您处于惩罚期内，请于%s后来借书！"),reBookTime);
		AfxMessageBox(text);
		return ;
	}
	if(thisNode!=NULL)
	{
		//判断本人是否有这本书
		
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
		CString sql_select;

		//查询
		sql_select.Format(_T("select * from user where username = \'%s\'"),loginUser);
		string sql_Select=transformPlus.toString(sql_select);
		const char  * sql=sql_Select.c_str();
		int res=mysql_query(&local_mysql,sql);
		MYSQL_RES * result;
		MYSQL_ROW row;
		if(res==0)
		{
			result=mysql_store_result(&local_mysql);
			row=mysql_fetch_row(result);
			if(row)
			{
				
				string userType=row[5];
				string userBookNumber=row[6];
				//本科生
				if(userType=="1")
				{
					borrowBook(userType,userBookNumber,local_mysql);
				}
				//研究生
				else if(userType=="2")
				{
					borrowBook(userType,userBookNumber,local_mysql);
				}
				//博士生
				else if(userType=="3")
				{
					borrowBook(userType,userBookNumber,local_mysql);
				}
				//教师
				else if(userType=="4")
				{
					borrowBook(userType,userBookNumber,local_mysql);
				}
				else
				{
					AfxMessageBox(_T("error type!"));
					return ;
				}
			}
			else
			{
				AfxMessageBox(_T("error!"));
				return ;
			}
		}
		else
		{
			AfxMessageBox(_T("error!"));
			return ;
		}
	}
	//未选择书籍
	else
	{
		MessageBox(L"还未选择书籍！");
	}
	// TODO: 在此添加控件通知处理程序代码
}


//刷新button
void InterfaceForUser::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnInitDialog();
	select_list_box.ResetContent();
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	control_book_name.SetWindowText(_T(""));
	control_book_press.SetWindowText(_T(""));
	control_book_date.SetWindowText(_T(""));
	control_book_ISBN.SetWindowText(_T(""));
	control_book_type.SetWindowText(_T(""));
	control_book_about.SetWindowText(_T(""));
	control_book_number.SetWindowText(_T(""));
	control_book_author.SetWindowText(_T(""));
	thisNode=NULL;
	thisUserBookNode=NULL;
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO1);
	radio->SetCheck(0);
	radio=(CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(0);
	radio=(CButton*)GetDlgItem(IDC_RADIO3);
	radio->SetCheck(0);
	radio=(CButton*)GetDlgItem(IDC_RADIO4);
	radio->SetCheck(0);
	/*control_book_name.ShowWindow(SW_HIDE);
	control_book_author.ShowWindow(SW_HIDE);
	control_book_press.ShowWindow(SW_HIDE);
	control_book_date.ShowWindow(SW_HIDE);
	control_book_ISBN.ShowWindow(SW_HIDE);
	control_book_type.ShowWindow(SW_HIDE);
	control_book_about.ShowWindow(SW_HIDE);
	control_book_number.ShowWindow(SW_HIDE);*/
}

void InterfaceForUser::setUserBookMessage()
{
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
	sql_select.Format(_T("select * from user_book where username = \'%s\';"),loginUser);
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
			//查找书籍名字
			CString sql_book_name;
			sql_book_name.Format(_T("select * from book where ISBN=\'%s\';"),transformPlus.toCString(row[2]));
			string SQL=transformPlus.toString(sql_book_name);
			const char  * Sql=SQL.c_str();
			int Res=mysql_query(&local_mysql,Sql);
			MYSQL_RES * Result;
			MYSQL_ROW Row;
			if(Res==0)
			{
				Result=mysql_store_result(&local_mysql);
				Row=mysql_fetch_row(Result);
				CString cstr=transformPlus.toCString(Row[3]);
				int judge=user_book_list.InsertString(-1,cstr);
				if(judge>=0)
				{
					userBook * newNode=new userBook(row[2],judge,Row[3]);
					userBookList.add(newNode);
					userBookList.p->next=NULL;
				}
				else
				{
					AfxMessageBox(_T("Out of memory!"));
				}
			}
			else
			{
				AfxMessageBox(_T("error!!!!!!!"));
				return ;
			}
		}
	}
	else
	{
		return ;
	}
}

//删除登录用户的信息
int InterfaceForUser::delBlockMessage(CString usrename)
{
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		return 0;
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}

	CString sql_update;
	sql_update.Format(_T("update user set message= \'\' where usrename=\'%s\' ;"),transformPlus.toCString(username));
	MessageBox(sql_update);
	string temp=transformPlus.toString(sql_update);
	const char * sql=temp.c_str();
	if(mysql_query(&local_mysql,sql)==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//判断登录用户有没有信息
int InterfaceForUser::judgeMessage()
{
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		return 0;
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}

	CString sql_select;
	sql_select.Format(_T("select * from user where username = \'%s\';"),loginUser);
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			if(row[9])
			{
				MessageBox(transformPlus.toCString(row[9]));

				return 1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			AfxMessageBox(_T("error!"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return 0;
	}
}


//初始化dlg的最后一个虚函数
BOOL InterfaceForUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	user_book_list.ResetContent();
	// TODO:  在此添加额外的初始化
	//judgeMessage();
//	int judge=delBlockMessage(loginUser);

	control_type.SetWindowText(transformPlus.toCString(TYPE));
	control_type.ShowWindow(TRUE);
	control_name.SetWindowText(transformPlus.toCString(name));
	control_name.ShowWindow(TRUE);
	control_username.SetWindowText(transformPlus.toCString(username));
	control_username.ShowWindow(TRUE);
	GetDlgItem(IDC_PROFESSIONAL)->SetWindowText(loginUserProfessioanl);
	GetDlgItem(IDC_PROFESSIONAL)->ShowWindow(TRUE);
	setUserBookMessage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/*MYSQL InterfaceForUser::connectMySQL()
{
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
		return local_mysql;
	}
}
*/

//点击已借书籍
void InterfaceForUser::OnLbnSelchangeList3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstrText;
	int selectedTextNumber;
	selectedTextNumber=user_book_list.GetCurSel();

	CString selectedTextName;
	user_book_list.GetText(selectedTextNumber, selectedTextName);
	//MessageBox(selectedTextName);

	userBook *head=userBookList.head;
	//MessageBox(transformPlus.toCString(selectedTextNumber));
	if(head==NULL)
	{
		AfxMessageBox(_T("error!"));
		return ;
	}
	else
	{
		while(head)
		{
			if(transformPlus.toCString(head->reBookName())==selectedTextName)
			{
				thisUserBookNode=head;
				break;
			}
			head=head->next;
		}
	}
	//MessageBox(transformPlus.toCString(thisUserBookNode->reBookName()));
}

// 读者选中自己的书籍的详情
void InterfaceForUser::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
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
	if(thisUserBookNode==NULL)
	{
		MessageBox(L"您还未选择任何书籍！");
		return ;
	}
	else
	{
		
		AboutYourBookMessage aboutYourBookMessage;
		aboutYourBookMessage.loginUser=loginUser;
		aboutYourBookMessage.list.add(thisUserBookNode);
		aboutYourBookMessage.DoModal();
		return ;
	}
}

//注销
void InterfaceForUser::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

//判断时间
int InterfaceForUser::judgeTime(long reTime)
{
	time_t nowTime=time(0);
	CString cstrNowTime;
	cstrNowTime.Format(_T("%d"),nowTime);
	long now_time=transformPlus.toLong(cstrNowTime);
	if(now_time<reTime)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//mistake加一
int InterfaceForUser::addMistake(string username,MYSQL local_mysql)
{
	CString sql_select;
	sql_select.Format(_T("select * from user where username = \'%s\';"),transformPlus.toCString(username));
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
			int number =transformPlus.toInt(row[7]);
			number ++;
			CString sql_update;
			sql_update.Format(_T("update user set mistake = \'%s\' where username = \'%s\' ;"),transformPlus.toCString(number),transformPlus.toCString(username));
			temp=transformPlus.toString(sql_update);
			sql=temp.c_str();
			if(mysql_query(&local_mysql,sql)==0)
			{
				return 1;
			}
			else
			{
				AfxMessageBox(_T("error!"));
				return 0;
			}
		}
		else
		{
			AfxMessageBox(_T("error!"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("error;"));
		return 0;
	}
}


//删除书籍记录
int InterfaceForUser::delBookMessage(string bookISBN,MYSQL local_mysql)
{
	CString sql_del;
	sql_del.Format(_T("delete from user_book where bookISBN=\'%s\' ;"),transformPlus.toCString(thisUserBookNode->reISBN()));
	string temp=transformPlus.toString(sql_del);
	const char * sql=temp.c_str();
	if(mysql_query(&local_mysql,sql))
	{
		return 0;
	}
	{
		return 1;
	}
}

//将用户添加进fineuser 名单/////////////////////////////////////////////
int InterfaceForUser::addFineUser(CString username,MYSQL local_mysql)
{
	//判断该用户在不在表里
	CString sql_query;
	sql_query.Format(_T("select * from user_finetime where username = \'%s\' ;"),username);
	string temp=transformPlus.toString(sql_query);
	const char * sql = temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row[0]>"0")
		{
			return 1;//用户在表里
		}
		else
		{
			//用户不在表里
			time_t nowTime=time(0);
			CString cstrNowTime;
			cstrNowTime.Format(_T("%d"),nowTime);
			long now_time=transformPlus.toLong(cstrNowTime);
			long finetime=now_time+259200;
			CString sql_insert;
			sql_insert.Format(_T("insert into user_finetime (\'\' , \'%s\', \'%s\');"),username,transformPlus.toCString(finetime));
			temp=transformPlus.toString(sql_insert);
			sql=temp.c_str();
			if(mysql_query(&local_mysql,sql)==0)
			{
				return 1;
			}
			else
			{
				AfxMessageBox(_T("error!"));
				return 0;
			}
		}
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return 0;
	}
}


//judgeUser wrongtime
int InterfaceForUser::judgeUserWrongTime()
{
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

	CString sql_query;
	sql_query.Format(_T("select * from user where username=\'%s\';"),loginUser);
	string temp=transformPlus.toString(sql_query);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			int number=transformPlus.toInt(row[7]);
			if(number>=3)
			{
				
				return 1;
			}
		}
		else
		{
			AfxMessageBox(_T("error!"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("error"));
		return 0;
	}
}
int InterfaceForUser::addUserToFineUserTable()
{
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

	time_t now_time=time(0);
	CString cstrNowTime;
	cstrNowTime.Format(_T("%d"),now_time);
	long time_long=transformPlus.toLong(cstrNowTime);
	time_long+=604800;
	CString fTime;
	fTime=transformPlus.toCString(time_long);

	CString sql_query;
	sql_query.Format(_T("insert into user_finetime values (\'\',\'%s\',\'%s\');"),loginUser,fTime);
	string temp=transformPlus.toString(sql_query);
	const char * sql=temp.c_str();
	if(mysql_query(&local_mysql,sql)==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//还书
void InterfaceForUser::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(thisUserBookNode==NULL)
	{
		MessageBox(L"您还未选取任何书籍！");
		return ;
	}
	else
	{
		CString reTime;
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
		CString sql_select;
		sql_select.Format(_T("select * from user_book where bookISBN=\'%s\';"),transformPlus.toCString(thisUserBookNode->reISBN()));
		string temp = transformPlus.toString(sql_select);
		const char * sql=temp.c_str();
		int res=mysql_query(&local_mysql,sql);
		MYSQL_RES * result;
		MYSQL_ROW row;
		
		if(res==0)
		{
			result=mysql_store_result(&local_mysql);
			row=mysql_fetch_row(result);
			if(row)
			{
				reTime=row[3];
				long RETime=transformPlus.toLong(reTime);
				int judge=judgeTime(RETime);
				if(judge==0)
				{
					int JUDGEDEL=delBookMessage(thisUserBookNode->reISBN(),local_mysql);
					int JUDGEADD=addBookNumber(thisUserBookNode->reISBN(),local_mysql);
					int JUDGUSER=reduceUserBookNumber(transformPlus.toString(loginUser),local_mysql);
					if(JUDGEDEL==JUDGEADD&&JUDGUSER==JUDGEDEL)
					{
						MessageBox(L"还书成功！");
						//userBookList.del(thisUserBookNode);
						OnInitDialog();
						return ;
					}
					else
					{
						MessageBox(L"还书失败！");
						return ;
					}
				}
				else
				{
					int JUDGEDEL=delBookMessage(thisUserBookNode->reISBN(),local_mysql);
					int JUDGEADD=addBookNumber(thisUserBookNode->reISBN(),local_mysql);
					int JUDGUSER=reduceUserBookNumber(transformPlus.toString(loginUser),local_mysql);
					if(JUDGEDEL==JUDGEADD&&JUDGUSER==JUDGEDEL)
					{
						MessageBox(L"还书成功！");
						OnInitDialog();
					}
					int j=judgeUserWrongTime();
					if(j==1)
					{
						AfxMessageBox(_T("您违约超过三次，现已处于惩罚名单！"));
						return ;
					}


					int ADDMISTAKE=addMistake(transformPlus.toString(loginUser),local_mysql);
					if(ADDMISTAKE==1)
					{
						//判断用户的mistake 如果是三次 就addfinuser
						MessageBox(L"您的应还日期已过，犯错次数加一，如果犯错次数达到3次，则将禁止借书一周！");
						int i=judgeUserWrongTime();
						if(i==1)
						{
							AfxMessageBox(_T("您违约超过三次，现已将您加入惩罚名单！"));
							addUserToFineUserTable();
							return ;
						}
					}
					else
					{
						AfxMessageBox(_T("1332131321"));
						return ;
					}
				}
			}
			else
			{
				AfxMessageBox(_T("error!!!"));
				return ;
			}
		}
		else
		{
			AfxMessageBox(_T("error!"));
			return ;
		}
		return ;
	}
}

//判断书籍数量
int InterfaceForUser::judgeBookNumber(CString bookISBN,MYSQL local_mysql)
{
	CString sql_query;
	sql_query.Format(_T("select * from book where ISBN=\'%s\';"),bookISBN);
	string temp=transformPlus.toString(sql_query);
	const char * sql = temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			int number = transformPlus.toInt(row[1]);
			if(number >1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			AfxMessageBox(_T("errorrrrrrr"));
			return 0;
		}
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return 0 ;
	}
}

//预约的书籍存入预约表
int InterfaceForUser::addBookToAppointmentBookTable(CString username,CString bookISBN,MYSQL local_mysql)
{
	time_t nowTime=time(0);
	CString cstrNowTime;
	cstrNowTime.Format(_T("%d"),nowTime);
	long now_time=transformPlus.toLong(cstrNowTime);
	CString lastTime=transformPlus.toCString(now_time+259200);
	CString sql_insert;
	sql_insert.Format(_T("insert into appointment_book values (\'\',\'%s\',\'%s\',\'%s\');"),username,bookISBN,lastTime);
	string temp=transformPlus.toString(sql_insert);
	const char * sql=temp.c_str();
	MYSQL_RES * res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		return 1;
	}
	else
	{
		AfxMessageBox(_T("error!!!"));
		return 0;
	}
}

//判断这本书是否被预约 1被预约过 0 没有被预约过
int InterfaceForUser::judgeTheBookIsAppointment(CString username,CString bookISBN,MYSQL local_mysql)
{
	CString sql_select ;
	sql_select.Format(_T("select * from appointment_book where username=\'%s\';"),username);
	string temp=transformPlus.toString((sql_select));
	const char * sql=temp.c_str();
	MYSQL_RES *res ;
	MYSQL_ROW  row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		while(row=mysql_fetch_row(res))
		{
			if(row[2]==transformPlus.toString(bookISBN))
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return 0;
	}
}

//判断读者书籍数是否超额
int InterfaceForUser::checkUserBookNumber(CString username,MYSQL local_mysql)
{
	CString sql_select;
	sql_select.Format(_T("select * from user where username= \'%s\';"),username);
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES *res;
	MYSQL_ROW row;
	if(mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(res);
		if(row)
		{
			string userType=row[5];
			string userBookNumber=row[6];
			string staticNumber;
			if(userType=="1")
			{
				staticNumber="4";
			}
			else if(userType=="2")
			{
				staticNumber="6";
			}
			else if(userType=="3")
			{
				staticNumber="10";
			}
			else if(userType=="4")
			{
				staticNumber="999999";
			}
			if(userBookNumber>=staticNumber)
			{
				MessageBox(L"借书量已达上限，请归还部分书籍后进行借阅！");
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
//预约
void InterfaceForUser::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int judgeLoginUser=judgeUserInFineListOrNot();
	if(judgeLoginUser==1)
	{
		CString reBookTime;
		struct tm *p;
		time_t t;
		t=transformPlus.toLong(fineTime)+28800;
		p=gmtime(&t);
		char s[80];
		strftime(s, 80, "%Y-%m-%d %H:%M:%S", p);
		reBookTime=transformPlus.toCString(s);
		CString text;
		text.Format(_T("您处于惩罚期内，请于%s后来预约！"),reBookTime);
		AfxMessageBox(text);
		return ;
	}
	if(thisNode==NULL)
	{
		MessageBox(L"您还没有选取书籍！");
		return ;
	}
	//判断此人有没有借过这本书
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
	CString sql_select;
	sql_select.Format(_T("select * from user_book where username = \'%s\'"),loginUser);
	string temp=transformPlus.toString(sql_select);
	const char * sql=temp.c_str();
	MYSQL_RES * res;
	MYSQL_ROW row;
	if (mysql_query(&local_mysql,sql)==0)
	{
		res=mysql_store_result(&local_mysql);
		while(row=mysql_fetch_row(res))
		{
			if(row[3]==thisNode->reISBN())
			{
				MessageBox(L"您已借阅此书籍！");
				return ;
			}
		}
		if(judgeTheBookIsAppointment(loginUser,transformPlus.toCString(thisNode->reISBN()),local_mysql)==1)
		{
			//判断是否被预约
			AfxMessageBox(_T("您已预约这本书！"));
			return ;
		}
		//判断读者书籍数量
		int checkuserbook= checkUserBookNumber(loginUser,local_mysql);
		if(checkuserbook==0)
		{
			return ;
		}
		//判断书籍数量
		int judge=judgeBookNumber(transformPlus.toCString(thisNode->reISBN()),local_mysql);
		if(judge==1)
		{
			int judgeUserBook=addUserBookNumber(loginUser,local_mysql);
			int judugeBookNumber=reduceBookNumber(thisNode->reISBN(),local_mysql);
			int judgeAdd=addBookToAppointmentBookTable(loginUser,transformPlus.toCString(thisNode->reISBN()),local_mysql);
				if(judgeUserBook==judugeBookNumber&&1==judgeAdd)
			{
				MessageBox(L"预约成功！");
				return ;
			}
			else
			{
					AfxMessageBox(_T("预约失败！"));
				return ;
			}
		}
		else
		{
			AfxMessageBox(_T("此书籍馆藏量不足！"));
			return ;
		}
	}
	else
	{
		AfxMessageBox(_T("error!"));
		return ;
	}
//判断书籍数量，是否可以预约
}
