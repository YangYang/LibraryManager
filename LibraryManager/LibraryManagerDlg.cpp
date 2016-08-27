
// LibraryManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LibraryManager.h"
#include "LibraryManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLibraryManagerDlg 对话框




CLibraryManagerDlg::CLibraryManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLibraryManagerDlg::IDD, pParent)
	, edit_username(_T(""))
	, edit_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibraryManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, edit_username);
	DDX_Text(pDX, IDC_EDIT2, edit_password);
	DDX_Control(pDX, IDC_EDIT1, control_edit_username);
	DDX_Control(pDX, IDC_EDIT2, control_edit_password);
}

BEGIN_MESSAGE_MAP(CLibraryManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLibraryManagerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLibraryManagerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CLibraryManagerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLibraryManagerDlg 消息处理程序

BOOL CLibraryManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLibraryManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLibraryManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLibraryManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibraryManagerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(edit_username==""||edit_password=="")
	{
		AfxMessageBox(_T("用户名或密码不能为空！"));
		return ;
	}
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		return ;
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
	}
	CString sql_query;
	//如果是汉字，需要添加''		
	sql_query.Format(_T("select * from user where username = \'%s\';"),  edit_username);
	string sql_Query=transformPlus.toString(sql_query);
	const char  * sql=sql_Query.c_str();
	MYSQL_RES * result;
	MYSQL_ROW row;
	//返回0，成功！
	int res;
	res=mysql_query(&local_mysql,sql);
	//mysql_query返回值问题！！！！！！！！！！
	if(res==0)
	{
		//将结果保存至result
		result=mysql_store_result(&local_mysql);
		row=mysql_fetch_row(result);
		//将数据库中password 即row[2]保存至password
		if(!row)
		{
			AfxMessageBox(_T("账号输入错误！"));
			return ;
		}
		string password=row[2];
		string Password=transformPlus.toString(edit_password);
		string type=row[5];
		if(password!=Password)
		{
			AfxMessageBox(_T("密码输入错误！"));
			return ;
		}
		else
		{
			if(type=="0")
			{
				MessageBox(_T("admin"));
				return ;
			}
			else
			{
				//MessageBox(_T("user"));
				InterfaceForUser interfaceForUser;
				interfaceForUser.name=row[3];
				interfaceForUser.username=row[1];
				interfaceForUser.loginUser=edit_username;
				interfaceForUser.loginUserType=transformPlus.toCString(type);
				if(type=="1")
				{
					interfaceForUser.TYPE="本科生";
				}
				else if(type=="2")
				{
					interfaceForUser.TYPE="研究生";
				}
				else if(type=="3")
				{
					interfaceForUser.TYPE="博士生";
				}
				else if(type=="4")
				{
					interfaceForUser.TYPE="教师";
				}
				this->ShowWindow(SW_HIDE);
				interfaceForUser.DoModal();
				//this->ShowWindow(SW_SHOW);
				//control_edit_username.SetWindowText(_T(""));
				//control_edit_password.SetWindowText(_T(""));
				CLibraryManagerDlg main;
				main.DoModal();

				CDialogEx::OnOK();
				//OnBnClickedOk();
			}
		}
	}
	else
	{
		AfxMessageBox(_T("查无此人！"));
		return ;
	}
	CDialogEx::OnOK();
}


void CLibraryManagerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CLibraryManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	SignIn signIn;
	signIn.DoModal();
	this->ShowWindow(SW_SHOW);
	//MessageBox(_T("跳转至注册界面"));
}

MYSQL CLibraryManagerDlg::connectMySQL()
{
	MYSQL local_mysql;
	mysql_init(&local_mysql);
	if(!mysql_real_connect(&local_mysql,"127.0.0.1","root","","librarymanager",3306,NULL,0))
	{
		MessageBox(_T("error"));
		AfxMessageBox(_T("connect to databases failed!"));
		AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	}
	else
	{
		//AfxMessageBox(_T("connect to database success!"));
		mysql_query(&local_mysql,"set names'gb2312'");
		return local_mysql;
	}
}