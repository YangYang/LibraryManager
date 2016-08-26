#pragma once
#include "afxwin.h"
#include <string>
#include "TransformPlus.h"
#include <mysql.h>
#include "Book.h"
#include "List.h"
#include <ctime>

// InterfaceForUser 对话框

class InterfaceForUser : public CDialogEx
{
	DECLARE_DYNAMIC(InterfaceForUser)

public:
	InterfaceForUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InterfaceForUser();

// 对话框数据
	enum { IDD = IDD_INTERFACEFORUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString loginUser;//登陆者的账号
	CString loginUserType;//登陆者的种类
	CString edit_search;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();

	TransformPlus transformPlus;
	int select_type;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	int all_book_number;
	CListBox select_list_box;
	CString book_number;
	CButton control_search_button;
	afx_msg void OnEnChangeEdit1();
	CStatic control_book_number;
	afx_msg void OnLbnSelchangeList1();
	CString book_name;
	CString book_author;
	CString book_press;
	CString book_date;
	CString book_type;
	CString book_about;
	CStatic control_book_name;
	CStatic control_book_author;
	CStatic control_book_press;
	CStatic control_book_date;
	CStatic control_book_type;
	CStatic control_book_about;
	List<Book> list;//book 类的list对象
	Book *thisNode;//选中的书籍
	string TYPE;//显示的用户类型
	string name;//显示的用户姓名
	string username;//显示的用户名
	CString book_ISBN;
	CStatic control_book_ISBN;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void borrowBook(string ,string ,MYSQL );
	CStatic control_name;
	CStatic control_type;
	CStatic control_username;
	CString name_text;
	CString type_text;
	CString username_text;
	virtual BOOL OnInitDialog();
};
