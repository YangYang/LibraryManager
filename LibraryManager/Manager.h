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
#include "FineGuyList.h"
#include "FineGuyMessage.h"
#include "AboutTheBookMessage.h"

// Manager 对话框
//管理员界面DLG

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
	//control 变量
	int control_appointment;
	int control_book_to_user;
	int control_user_to_book;
	int control_weiyue;
	int control_calculate_book;
	int control_calculate_user;
	// 连接mysql 数据、函数
	MYSQL local_mysql;
	void connectMysql();
	string temp;
	const char * sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	//选取某条信息所需要的List 和对应类型的指针
	//预约用户
	List<appointmentUser> appointmentList;
	appointmentUser * appThisNode;
	//违约用户
	List<badGuyList> BadGuyList;
	badGuyList * bGThisNode;
	//统计书籍
	List<managerBook> managerBookList;
	managerBook * mBThisNode;
	//统计读者
	List<managerUser> managerUserList;
	managerUser * mUThisNode;	
	//被惩罚用户
	List<FineGuyList> FineGuiesList;
	FineGuyList *fGThisNode;
	//点击 用户List 
	List<Book> userBookList;
	Book *uBThisNode;

	TransformPlus transformPlus;//万能转换类
	
	CListBox control_list_box;
	void insertAppointmentMessageToListBox();
	void insertBadGuyToListBox();
	void insertAllBookToListBox();
	int allBooksNumber;
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
	void insertUserBookListToListBox();//以人查书时用到的List
	CButton control_search_type;
	afx_msg void OnBnClickedButton3();
	void acceptBorrowBook();
	afx_msg void OnLbnSelchangeList1();
	int addMistake(CString username);
	int delAppointmentMessage(CString username,CString bookISBN);
	afx_msg void OnBnClickedButton2();
	int sendMessageToUser(CString ,CString );
	void insertFineGuiesListToListBox();
	CListBox control_fine_list_box;
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	int delBook(CString book_ISBN);
	int delUser(CString username);
	afx_msg void OnLbnDblclkList1();
};
