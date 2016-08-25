#pragma once
#include "afxwin.h"
#include <string>
#include "TransformPlus.h"
#include <mysql.h>

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
};
