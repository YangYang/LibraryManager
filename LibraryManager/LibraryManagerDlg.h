
// LibraryManagerDlg.h : 头文件
//

#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "TransformPlus.h"
#include "binary_log_types.h"
#include "SignIn.h"
#include "InterfaceForUser.h"
#include "afxwin.h"
#include "Manager.h"

// CLibraryManagerDlg 对话框
class CLibraryManagerDlg : public CDialogEx
{
// 构造
public:
	CLibraryManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LIBRARYMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	TransformPlus transformPlus;
	afx_msg void OnBnClickedOk();
	CString edit_username;
	CString edit_password;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	MYSQL connectMySQL();
	CEdit control_edit_username;
	CEdit control_edit_password;
};
