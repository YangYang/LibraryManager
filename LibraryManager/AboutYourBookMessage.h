#pragma once
#include "afxwin.h"
#include "TransformPlus.h"
#include "List.h"
#include "Book.h"
#include "userBook.h"
#include "mysql.h"
#include <string>

// AboutYourBookMessage 对话框

class AboutYourBookMessage : public CDialogEx
{
	DECLARE_DYNAMIC(AboutYourBookMessage)

public:
	AboutYourBookMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutYourBookMessage();

// 对话框数据
	enum { IDD = IDD_ABOUTYOURBOOKMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString book_name;
	CString book_author;
	CString book_press;
	CString book_ISBN;
	CString book_type;
	CStatic control_book_name;
	CStatic control_book_author;
	CStatic control_book_press;
	CStatic control_book_ISBN;
	CStatic control_book_type;
	List<userBook> list;
	TransformPlus transformPlus;
	virtual BOOL OnInitDialog();
	CString book_date;
	CStatic control_book_date;
	CStatic control_return_book_time;
	CString return_book_time;
	CString loginUser;//登陆者的账号
	afx_msg void OnStnClickedRetimetext();
};
