// wayview.h : wayview Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CwayviewApp:
// �йش����ʵ�֣������ wayview.cpp
//

class CwayviewApp : public CWinApp
{
public:
	CwayviewApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CwayviewApp theApp;
