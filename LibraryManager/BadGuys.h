#pragma once
#include "TransformPlus.h"
#include "badGuyList.h"
#include <string>
#include <mysql.h>


// BadGuys 对话框

class BadGuys : public CDialogEx
{
	DECLARE_DYNAMIC(BadGuys)

public:
	BadGuys(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BadGuys();
	CString username;
	TransformPlus transformPlus;
// 对话框数据
	enum { IDD = IDD_BADGUYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
