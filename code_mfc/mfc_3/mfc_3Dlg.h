
// mfc_3Dlg.h : 头文件
//

#pragma once


// Cmfc_3Dlg 对话框
class Cmfc_3Dlg : public CDialogEx
{
// 构造
public:
	Cmfc_3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnCbnSelchangeSizeCmb();
	afx_msg void OnBnClickedReviewBtn();
	HBRUSH OnCtlColor(CDC* pdc,CWnd* pWnd,UINT nCtlColor);
	CButton m_insert;
	CButton m_review;
	CComboBox m_fontsize;
	CFont font;
	CEdit m_content;
	CString m_font;
	afx_msg void OnClickedEditBtn();

	CBrush cbr;
	bool synClock;
};
