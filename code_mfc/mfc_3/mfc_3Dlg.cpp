
// mfc_3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_3.h"
#include "mfc_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cmfc_3Dlg �Ի���




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


// Cmfc_3Dlg ��Ϣ�������

BOOL Cmfc_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	synClock = false;
	m_content.EnableWindow(TRUE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
/*
void Cmfc_3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}*/


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmfc_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc_3Dlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
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




//����ѡ��������С���ñ��޸�ʱ���¼�����
void Cmfc_3Dlg::OnCbnSelchangeSizeCmb()
{
	UpdateData(TRUE);

	int start,end;
	//��ȡ�༭����ѡ�е�����
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
	
	if(selFontSize.Compare(_T("�����")) == 0){
		size = 80;	
	}
	else if(selFontSize.Compare(_T("���")) == 0){
		size = 50;
	}
	else if(selFontSize.Compare(_T("�к�")) == 0){
		size = 35;
	}
	else if(selFontSize.Compare(_T("С��")) == 0){
		size = 20;
	}
	else if(selFontSize.Compare(_T("��С��")) == 0){
		size = 10;
	}else{
		MessageBox(_T("ERROR"));
	}

	//��������ʹ�С
	//CFont font;
	LOGFONT lf ;
	(m_content.GetFont())->GetLogFont(&lf);
	lf.lfHeight = size;
	strcpy ((char*)(lf.lfFaceName),"����");

	font.Detach();
	font.CreateFontIndirectW(&lf);
	m_content.SetFont(&font);

	UpdateData(FALSE);
}


//���Ԥ����ť���¼�����
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


//����༭��ť���¼�����
void Cmfc_3Dlg::OnClickedEditBtn()
{
	synClock = false;
	
	m_content.EnableWindow(TRUE);
	m_fontsize.EnableWindow(TRUE);
}