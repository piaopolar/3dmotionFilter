
	 // 3dmotionFilterDlg.h : header file
#pragma once
#include "afxwin.h"

#include <vector>

// ============================================================================
//    CMy3dmotionFilterDlg dialog
// ============================================================================
class CMy3dmotionFilterDlg : public CDialog
{
// ----------------------------------------------------------------------------
//    Construction
// ----------------------------------------------------------------------------
public:
	CMy3dmotionFilterDlg(CWnd *pParent = NULL);			// standard constructor

	// Dialog Data
	enum { IDD = IDD_MY3DMOTIONFILTER_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support

// ----------------------------------------------------------------------------
//    Implementation
// ----------------------------------------------------------------------------
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_lstMountType;
	CListBox m_lstWeaponType;
	CListBox m_lstLook;
	CListBox m_lstMotion;
	std::vector<int> m_vecMountFilter;
	std::vector<int> m_vecWeaponFilter;
	std::vector<int> m_vecLookFilter;
	std::vector<int> m_vecMotionFilter;
	CEdit m_edtLog;
	afx_msg void OnBnClickedButton2();
	void LoadIni2Lst(void);
};
