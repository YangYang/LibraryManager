#pragma once
#include "TransformPlus.h"
#include <string>
#include <mysql.h>
#include "managerBook.h"


// AboutTheBookMessage 对话框
// 管理员查看书籍信息DLG

class AboutTheBookMessage : public CDialogEx
{
	DECLARE_DYNAMIC(AboutTheBookMessage)

public:
	AboutTheBookMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutTheBookMessage();
	managerBook * theBookNode;
	TransformPlus transformPlus;
// 对话框数据
	enum { IDD = IDD_ABOUTTHEBOOKMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
