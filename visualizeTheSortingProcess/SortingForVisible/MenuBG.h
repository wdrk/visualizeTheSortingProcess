#pragma once


// CMenuBG ��ȭ �����Դϴ�.

UINT WorkerThread(LPVOID pParam);
#define MAXIMUM_LENGTH_OF_ARRAY	300
#define MAXIMUM_NUMBER_OF_MIXING 590

class CMenuBG : public CDialog
{
	DECLARE_DYNAMIC(CMenuBG)

public:
	CMenuBG(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMenuBG();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENUBG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedAuto();
	afx_msg void OnBnClickedManual();
	afx_msg void OnBnClickedReset();
	int i;
	int j;
	// ������ ���� ���� �ӽ� �����ϴ� �����Դϴ�.
	int nRand;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedClubmode();
	int u;
	int nTmp;
};
