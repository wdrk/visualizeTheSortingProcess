
// SortingForVisible.h : SortingForVisible ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSortingForVisibleApp:
// �� Ŭ������ ������ ���ؼ��� SortingForVisible.cpp�� �����Ͻʽÿ�.
//

class CSortingForVisibleApp : public CWinApp
{
public:
	CSortingForVisibleApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSortingForVisibleApp theApp;
