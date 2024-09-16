// MenuBG.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SortingForVisible.h"
#include "MenuBG.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SortingForVisibleView.h"

// CMenuBG ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMenuBG, CDialog)

CMenuBG::CMenuBG(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MENUBG, pParent)
	, i(0)
	, j(0)
	, nRand(0)
	, u(0)
	, nTmp(0)
{
}

CMenuBG::~CMenuBG()
{
}

void CMenuBG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuBG, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_AUTO, &CMenuBG::OnBnClickedAuto)
	ON_BN_CLICKED(IDC_MANUAL, &CMenuBG::OnBnClickedManual)
	ON_BN_CLICKED(IDC_RESET, &CMenuBG::OnBnClickedReset)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLUBMODE, &CMenuBG::OnBnClickedClubmode)
END_MESSAGE_MAP()


// CMenuBG �޽��� ó�����Դϴ�.

// �޴� ��ư�� �ִ� Form�� �׸��ϴ�.
void CMenuBG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, RGB(255, 255, 255));
}

CCriticalSection g_cs;


// WorkerThread�� Critical Section Lock�� ����ϸ� ������ �����մϴ�.
UINT WorkerThread(LPVOID pParam)
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// �����Ϳ� �����ϴ� ���� Critical Section�� ����ؼ� Lock�� �̴ϴ�.
	g_cs.Lock();

	// ���� ���� �ε��� �������Դϴ�.
	int i = 0;
	int j = 0;

	// ���� ���� �ε��� �������Դϴ�.
	int nMinimum_Data_Index = 0;
	int k = 0;

	// ���� ��ȯ�Ҷ� �ӽ÷� ���� �����ϴ� �����Դϴ�.
	int nTmp = 0;

	for (i = MAXIMUM_LENGTH_OF_ARRAY; i > 0; --i)
	{
		// ���� ���� �����Դϴ�.
		for (j = 0; j < i; ++j)
		{
			if (pView->nRandomData[j] > pView->nRandomData[j + 1])
			{
				nTmp = pView->nRandomData[j];
				pView->nRandomData[j] = pView->nRandomData[j + 1];
				pView->nRandomData[j + 1] = nTmp;
			}
		}

		// ���� ���� �����Դϴ�.
		for (j = 0; j < MAXIMUM_LENGTH_OF_ARRAY; ++j)
		{
			nMinimum_Data_Index = j;
	
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// ���� �ּҰ��� �ִ� �ε����� ���մϴ�.
			for (k = nMinimum_Data_Index + 1; k < MAXIMUM_LENGTH_OF_ARRAY; ++k)
			{
				if (pView->nRandomData2[nMinimum_Data_Index] > pView->nRandomData2[k])
					nMinimum_Data_Index = k;
			}
	
			// i�� u�� ���� �ٸ��ٸ� i�� �ε����� �ִ� ������ ���� ���� �߰��ߴٴ� ���̹Ƿ�
			// i �ε����� u �ε����� ���� ��ȯ�մϴ�.
			if (nMinimum_Data_Index != j)
			{
				nTmp = pView->nRandomData2[nMinimum_Data_Index];
				pView->nRandomData2[nMinimum_Data_Index] = pView->nRandomData2[j];
				pView->nRandomData2[j] = nTmp;

				// break�� ���ָ� �� ��¦�� ���� ������ ���������ϴ�.
				break;
			}
		}
		pView->RedrawWindow();

		if (false == pView->bAutoFlag)
			break;

		Sleep(10);
	}

	// ���� �۾��� ��� ������ ������ �÷��׵��� ���� �ʱ�ȭ�մϴ�.
	pView->bAutoFlag = false;
	pView->bInitFlag = false;
	pView->ClubMode = false;

	// Lock�� �����մϴ�.
	g_cs.Unlock();


	return 0;
}

// 'Auto' ��ư�� Ŭ�������� ó���ϴ� �ڵ��Դϴ�.
void CMenuBG::OnBnClickedAuto()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	if (true == pView->bAutoFlag)
		return;


	if (false == pView->bInitFlag)
		OnBnClickedReset();

	else
	{
		pView->bAutoFlag = true;
		AfxBeginThread(WorkerThread, NULL);
	}
}


// 'Manual' ��ư�� Ŭ�������� ó���ϴ� �ڵ��Դϴ�.
void CMenuBG::OnBnClickedManual()
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (true == pView->bAutoFlag)
		return;

	//else if (false == pView->bInitFlag)
		//return;

	else
		AfxBeginThread(WorkerThread, NULL);
}


// 'Reset' ��ư�� Ŭ�������� ó���ϴ� �ڵ��Դϴ�.
void CMenuBG::OnBnClickedReset()
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// Auto�� ���� �۾����϶��� �۵����� �ʵ��� �մϴ�.
	if (true == pView->bAutoFlag)
		return;

	srand((unsigned)time(NULL));

	// Auto ��ư�� ������ �۵��������� Ȯ���ϴ� �÷��׸� �ʱ�ȭ�մϴ�.
	pView->bAutoFlag = false;

	// �����͸� �ڼ��� ���������� Ȯ���ϴ� �÷��׸� true�� �����մϴ�.
	// ó�� ���α׷��� �����ؼ� �ƹ� �����͵� �������� �ʿ��� �÷����Դϴ�.
	pView->bInitFlag = true;
	i = 0;
	j = 0;

	// �����͸� ���� ������ ���� ���ϰ� �ϴ� �ڵ��Դϴ�.
	pView->ColorR = rand() % 255 + 1;
	pView->ColorG = rand() % 255 + 1;
	pView->ColorB = rand() % 255 + 1;

	pView->ColorR2 = rand() % 255 + 1;
	pView->ColorG2 = rand() % 255 + 1;
	pView->ColorB2 = rand() % 255 + 1;

	// ���� �������� ���� �迭�� ����� ���� ���� �迭�� ���ʴ�� ���� ä��ϴ�.
	for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
	{
		pView->nRandomData[i] = i + 1;
	}

	// x�� y�� �迭�� �ε��� ������ ���� �������Դϴ�.
	int x = 0;
	int y = 0;

	// �迭�� ���� ������ ���� ���� �� ������ŭ ���� ������ �ݺ��մϴ�.
	for (i = 0; i < MAXIMUM_NUMBER_OF_MIXING; ++i)
	{
		// x�� y�� �ִ� �迭���� �̳��� ���� �������� �����ϰ�,
		x = rand() % MAXIMUM_LENGTH_OF_ARRAY;
		y = rand() % MAXIMUM_LENGTH_OF_ARRAY;

		// x�� y�� ���� ���� �ƴϸ� �ش� ���� �ε����� �Ͽ� �� �ε����� ���� �����մϴ�.
		if (x != y)
		{
			int nTmp = pView->nRandomData[x];
			pView->nRandomData[x] = pView->nRandomData[y];
			pView->nRandomData[y] = nTmp;
		}
	}

	// nRandomData2 �迭�� ���� ������ �����ϰ� �����մϴ�.
	for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
	{
		pView->nRandomData2[i] = i + 1;
	}

	for (i = 0; i < MAXIMUM_NUMBER_OF_MIXING; ++i)
	{
		x = rand() % MAXIMUM_LENGTH_OF_ARRAY;
		y = rand() % MAXIMUM_LENGTH_OF_ARRAY;

		if (x != y)
		{
			int nTmp = pView->nRandomData2[x];
			pView->nRandomData2[x] = pView->nRandomData2[y];
			pView->nRandomData2[y] = nTmp;
		}
	}

	// ��� �۾��� ��ġ�� �����츦 ���� �׸��ϴ�.
	pView->RedrawWindow();
}

BOOL CMenuBG::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return TRUE;
}

void CMenuBG::OnBnClickedClubmode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	if (false == pView->bInitFlag)
		OnBnClickedReset();

	else if (true == pView->bAutoFlag)
		return;

	else
	{
		pView->ClubMode = true;
		OnBnClickedAuto();
	}
}
