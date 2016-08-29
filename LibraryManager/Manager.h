#pragma once

#include "TransformPlus.h"
#include <string>
#include <mysql.h>
#include "List.h"
#include "Book.h"
#include "userBook.h"
#include "afxwin.h"
#include "appointmentUser.h"
#include "badGuyList.h"
#include "managerBook.h"
#include "managerUser.h"
#include <string>
#include "AboutUserBook.h"
#include "SignIn.h"
#include "BadGuys.h"

// Manager 对话框

class Manager : public CDialogEx
{
	DECLARE_DYNAMIC(Manager)

public:
	Manager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Manager();

// 对话框数据
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio6();
	int search_type;
	CEdit control_edit;
	int control_appointment;
	int control_book_to_user;
	int control_user_to_book;
	int control_weiyue;
	int control_calculate_book;
	int control_calculate_user;
	MYSQL local_mysql;
	void connectMysql();
	List<appointmentUser> appointmentList;
	appointmentUser * appThisNode;
	void insertAppointmentMessageToListBox();
	TransformPlus transformPlus;
	string temp;
	const char * sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	CListBox control_list_box;

	List<badGuyList> BadGuyList;
	badGuyList * bGThisNode;
	void insertBadGuyToListBox();
	List<managerBook> managerBookList;//统计书籍
	void insertAllBookToListBox();
	int allBooksNumber;
	List<managerUser> managerUserList;//统计读者
	managerUser * mUThisNode;	
	void insertAllUserToListBox();
	int allUsersNumber;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio7();
	CButton control_button2;
	CButton control_button3;
	virtual BOOL OnInitDialog();
	void insertUserToListBox();//查找用户用到的List
	CString edit_text;
	void insertUserHaveTheBookToListBox();//以书查人用到的List
	List<Book> userBookList;
	Book *uBThisNode;
	void insertUserBookListToListBox();//以人查书时用到的List
	CButton control_search_type;
	afx_msg void OnBnClickedButton3();
	void acceptBorrowBook();
	afx_msg void OnLbnSelchangeList1();
	int addMistake(CString username);
	int delAppointmentMessage(CString username,CString bookISBN);
	afx_msg void OnBnClickedButton2();
	int sendMessageToUser(CString ,CString );
};
