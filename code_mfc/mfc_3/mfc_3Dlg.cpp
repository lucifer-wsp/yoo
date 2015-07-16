
// mfc_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_3.h"
#include "mfc_3Dlg.h"
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


// Cmfc_3Dlg 对话框




Cmfc_3Dlg::Cmfc_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_content = _T("");
	m_font = _T("");
}

void Cmfc_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_insert);
	DDX_Control(pDX, IDC_BUTTON2, m_review);
	DDX_Control(pDX, IDC_COMBO1, m_fontsize);
	DDX_Control(pDX, IDC_EDIT4, m_content);
	DDX_Text(pDX, IDC_EDIT4, m_font);
}

BEGIN_MESSAGE_MAP(Cmfc_3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT4, &Cmfc_3Dlg::OnEnChangeEdit4)
//	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc_3Dlg::OnBnClickedInsertBtn)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cmfc_3Dlg::OnCbnSelchangeSizeCmb)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmfc_3Dlg::OnBnClickedReviewBtn)
	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc_3Dlg::OnClickedEditBtn)
END_MESSAGE_MAP()


// Cmfc_3Dlg 消息处理程序

BOOL Cmfc_3Dlg::OnInitDialog()
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

	synClock = false;
	m_content.EnableWindow(TRUE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void Cmfc_3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
/*
void Cmfc_3Dlg::OnPaint()
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
}*/


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cmfc_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc_3Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
}


HBRUSH Cmfc_3Dlg::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);

	MessageBox(_T(""+(pWnd->GetDlgCtrlID())));

	if((pWnd->GetDlgCtrlID()) == IDC_EDIT4){
		pDC->SetBkMode(TRANSPARENT);
		return cbr;
	}

	return hbr;
}




//当复选框的字体大小设置被修改时的事件处理
void Cmfc_3Dlg::OnCbnSelchangeSizeCmb()
{
	UpdateData(TRUE);

	int start,end;
	//获取编辑框中选中的文字
	m_content.GetSel(start,end);

	CString str;
	m_content.GetWindowTextW(str);
	if(!str.IsEmpty()){
		str = str.Right(str.GetLength() - start);
		str.Truncate(end - start);
	}

	//MessageBox(str);

	int index = m_fontsize.GetCurSel();
	CString selFontSize;
	int size = 20;
	m_fontsize.GetLBText(index,selFontSize);
	
	if(selFontSize.Compare(_T("超大号")) == 0){
		size = 80;	
	}
	else if(selFontSize.Compare(_T("大号")) == 0){
		size = 50;
	}
	else if(selFontSize.Compare(_T("中号")) == 0){
		size = 35;
	}
	else if(selFontSize.Compare(_T("小号")) == 0){
		size = 20;
	}
	else if(selFontSize.Compare(_T("超小号")) == 0){
		size = 10;
	}else{
		MessageBox(_T("ERROR"));
	}

	//设置字体和大小
	//CFont font;
	LOGFONT lf ;
	(m_content.GetFont())->GetLogFont(&lf);
	lf.lfHeight = size;
	strcpy ((char*)(lf.lfFaceName),"宋体");

	font.Detach();
	font.CreateFontIndirectW(&lf);
	m_content.SetFont(&font);

	UpdateData(FALSE);
}


//点击预览按钮的事件处理
void Cmfc_3Dlg::OnBnClickedReviewBtn()
{
	synClock = true;

	cbr.Detach();
	cbr.CreateSolidBrush(RGB(255,0,0));


	m_content.ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	m_content.Invalidate();
	m_content.EnableWindow(FALSE);
	m_fontsize.EnableWindow(FALSE);
}


//点击编辑按钮的事件处理
void Cmfc_3Dlg::OnClickedEditBtn()
{
	synClock = false;
	
	m_content.EnableWindow(TRUE);
	m_fontsize.EnableWindow(TRUE);
}