// LogViewDlg.h : ͷ�ļ�
//

#pragma once
#include "Log.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLogViewDlg �Ի���
class CLogViewDlg : public CDialog
{
// ����
public:
	CLogViewDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOGVIEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	AreanaLog log;
	UnitLog	cur;
	std::vector<std::wstring> tracer;
	bool find_name(std::wstring name);
	double cur_time;
	void Goto( double time );
// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CScrollBar m_time;
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CListBox m_buff;
	CListBox m_debuff;
	afx_msg void OnLbnSelchangeList1();
	CListCtrl m_unit;
	CStatic m_timeInfo;
	CComboBox m_type;
	CStatic m_info;
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_cast;
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	CStatic m_showRect;
};
