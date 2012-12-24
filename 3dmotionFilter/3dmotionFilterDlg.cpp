
	 // 3dmotionFilterDlg.cpp : implementation file
#include "stdafx.h"

#include <algorithm>
#include "../BaseCode/BaseFunc.h"

#include "3dmotionFilter.h"
#include "3dmotionFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
namespace
{

// ============================================================================
// ==============================================================================
void LoadFile2List(const char *pszFile, std::vector<int> &rVecFilter, CListBox &rLst)
{
	rLst.ResetContent();

	//~~~~~~~~~~~~~~~~~~~~
	char szLine[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~

	_snprintf(szLine, sizeof(szLine), "未指定%s文件", pszFile);
	rLst.AddString(szLine);
	rLst.AddString("默认不使用此类型过滤");

	if (NULL == pszFile) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *pFile = fopen(pszFile, "r");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFile) {
		return;
	}

	rLst.ResetContent();
	while (fgets(szLine, sizeof(szLine), pFile)) {

		//~~~~~~~~~
		int nTmp = 0;
		//~~~~~~~~~

		if (1 == sscanf(szLine, "%d", &nTmp)) {
			rVecFilter.push_back(nTmp);
		}
	}

	fclose(pFile);

	for (std::vector<int>::const_iterator it(rVecFilter.begin()); it != rVecFilter.end(); ++it) {
		_snprintf(szLine, sizeof(szLine), "%d", *it);
		rLst.AddString(szLine);
	}
}
}
// ============================================================================
//    CAboutDlg dialog used for App About
// ============================================================================
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support

// ----------------------------------------------------------------------------
//    Implementation
// ----------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP()
};

// ============================================================================
// ==============================================================================

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

// ============================================================================
// ==============================================================================
void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ============================================================================
//    CMy3dmotionFilterDlg dialog
// ============================================================================
CMy3dmotionFilterDlg::CMy3dmotionFilterDlg(CWnd *pParent /* NULL */ ) : CDialog(CMy3dmotionFilterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// ============================================================================
// ==============================================================================
void CMy3dmotionFilterDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstMountType);
	DDX_Control(pDX, IDC_LIST2, m_lstWeaponType);
	DDX_Control(pDX, IDC_EDIT1, m_edtLog);
}

BEGIN_MESSAGE_MAP(CMy3dmotionFilterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMy3dmotionFilterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3dmotionFilterDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

// ============================================================================
//    CMy3dmotionFilterDlg message handlers
// ============================================================================
BOOL CMy3dmotionFilterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu. IDM_ABOUTBOX must be in the
	// system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMenu *pSysMenu = GetSystemMenu(FALSE);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pSysMenu != NULL) {

		//~~~~~~~~~~~~~~~~~
		BOOL bNameValid;
		CString strAboutMenu;
		//~~~~~~~~~~~~~~~~~

		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon

	SetLogEdit(&m_edtLog);

	LogInfoIn("Load Filter Files");
	LoadFile2List("mountFilter.ini", m_vecMountFilter, m_lstMountType);
	LoadFile2List("weaponFilter.ini", m_vecWeaponFilter, m_lstWeaponType);

	// TODO: Add extra initialization here
	return TRUE;				// return TRUE unless you set the focus to a control
}

// ============================================================================
// ==============================================================================
void CMy3dmotionFilterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {

		//~~~~~~~~~~~~~~~
		CAboutDlg dlgAbout;
		//~~~~~~~~~~~~~~~

		dlgAbout.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ============================================================================
//    If you add a minimize button to your dialog, you will need the code below
//    to draw the icon. For MFC applications using the document/view model, this
//    is automatically done for you by the framework.
// ============================================================================
void CMy3dmotionFilterDlg::OnPaint()
{
	if (IsIconic()) {

		//~~~~~~~~~~~~~~
		CPaintDC dc(this);	// device context for painting
		//~~~~~~~~~~~~~~

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM> (dc.GetSafeHdc()), 0);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		GetClientRect(&rect);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// ============================================================================
//    The system calls this function to obtain the cursor to display while the
//    user drags the minimized window.
// ============================================================================
HCURSOR CMy3dmotionFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ============================================================================
// ==============================================================================
void CMy3dmotionFilterDlg::OnBnClickedButton1()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const char *FILE_IN = "3dmotion.ini";
	FILE *pFileIn = fopen(FILE_IN, "r");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFileIn) {
		LogInfoIn("open %s failed", FILE_IN);
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const char *FILE_OUT = "+3dmotion.ini";
	FILE *pFileOut = fopen(FILE_OUT, "w");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFileOut) {
		LogInfoIn("create %s failed", FILE_OUT);
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~
	int nLinesPerReport = 10000;
	int nSubCount = 0;
	int nReportTime = 0;
	int nData = 0;
	int nFiltered = 0;
	char szLine[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~~~

	while (fgets(szLine, sizeof(szLine), pFileIn)) {
		++nSubCount;
		if (nSubCount == nLinesPerReport) {
			nSubCount = 0;
			++nReportTime;
			LogInfoIn("	Process %d Lines  Data %d  Filtered %d", nReportTime * nLinesPerReport, nData, nFiltered);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		char *pPos = strstr(szLine, "=");
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (NULL == pPos) {
			continue;
		}

		*pPos = 0;

		//~~~~~~~~~~~
		__int64 i64Key;
		//~~~~~~~~~~~

		if (1 != sscanf(szLine, "%I64d", &i64Key)) {
			continue;
		}

		*pPos = '=';

		++nData;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int nWeaponType = i64Key / 10000 % 1000;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (!m_vecWeaponFilter.empty()) {
			if (std::find(m_vecWeaponFilter.begin(), m_vecWeaponFilter.end(), nWeaponType) != m_vecWeaponFilter.end()) {
				++nFiltered;
				fprintf(pFileOut, "%s", szLine);
				continue;
			}
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int nMountType = i64Key / 10000000000;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (!m_vecMountFilter.empty()) {
			if (std::find(m_vecMountFilter.begin(), m_vecMountFilter.end(), nWeaponType) != m_vecMountFilter.end()) {
				++nFiltered;
				fprintf(pFileOut, "%s", szLine);
				continue;
			}
		}
	}

	fclose(pFileIn);
	fclose(pFileOut);

	LogInfoIn("Process End. %d Lines  Data %d  Filtered %d", nReportTime * nLinesPerReport + nSubCount, nData, nFiltered);
}

// ============================================================================
// ==============================================================================
void CMy3dmotionFilterDlg::OnBnClickedButton2()
{
	LogInfoIn("Reload Filter Files");
	LoadFile2List("mountFilter.ini", m_vecMountFilter, m_lstMountType);
	LoadFile2List("weaponFilter.ini", m_vecWeaponFilter, m_lstWeaponType);
}
