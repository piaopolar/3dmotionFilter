
// 3dmotionFilter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy3dmotionFilterApp:
// See 3dmotionFilter.cpp for the implementation of this class
//

class CMy3dmotionFilterApp : public CWinAppEx
{
public:
	CMy3dmotionFilterApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy3dmotionFilterApp theApp;