
// mfc_3Dlg.h : ͷ�ļ�
//

#pragma once


// Cmfc_3Dlg �Ի���
class Cmfc_3Dlg : public CDialogEx
{
// ����
public:
	Cmfc_3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
