#pragma once
#include <mysql.h>
#include <string>
#include "TransformPlus.h"
#include "afxwin.h"

// SignIn 对话框

class SignIn : public CDialogEx
{
	DECLARE_DYNAMIC(SignIn)

public:
	SignIn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SignIn();

// 对话框数据
	enum { IDD = IDD_SIGNIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString new_username;
	CString new_password;
	CString confirm_password;
	CString new_name;
	CString new_type;
	CString new_unit;
	TransformPlus transformPlus;
	CString textCheck;
	afx_msg void OnEnChangeEdit3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit1();
	CString checkUsername;
	afx_msg void OnEnChangeEdit4();
	CString confirmPassword;
	CEdit ct_confirm_password;
};
