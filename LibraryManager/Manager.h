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
	void insertAppointmentMessageToListBox();
	TransformPlus transformPlus;
	string temp;
	const char * sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	CListBox control_list_box;

	List<badGuyList> BadGuyList;
	void insertBadGuyToListBox();
	List<managerBook> managerBookList;
	void insertAllBookToListBox();
	int allBooksNumber;
	List<managerUser> managerUserList;
	void insertAllUserToListBox();
	int allUsersNumber;
	afx_msg void OnBnClickedOk();
};
