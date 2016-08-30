#pragma once
#include "TransformPlus.h"
#include "FineGuyList.h"
#include <mysql.h>


// FineGuyMessage 对话框
// 被惩罚人的 DLG
class FineGuyMessage : public CDialogEx
{
	DECLARE_DYNAMIC(FineGuyMessage)

public:
	FineGuyMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FineGuyMessage();
	FineGuyList *theGuy;
	TransformPlus transformPlus;
// 对话框数据
	enum { IDD = IDD_FINEGUYMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
