#pragma once
#include "TransformPlus.h"
#include <mysql.h>
#include "Book.h"
#include <cstring>

// AboutUserBook 对话框

class AboutUserBook : public CDialogEx
{
	DECLARE_DYNAMIC(AboutUserBook)

public:
	AboutUserBook(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutUserBook();
	Book * userBookMessage;
	TransformPlus transformPlus;
	CString ISBN;

// 对话框数据
	enum { IDD = IDD_ABOUTUSERBOOK };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
