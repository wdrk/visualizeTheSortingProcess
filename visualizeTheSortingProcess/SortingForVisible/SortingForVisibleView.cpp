
// SortingForVisibleView.cpp : CSortingForVisibleView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "SortingForVisible.h"
#endif

#include "SortingForVisibleDoc.h"
#include "SortingForVisibleView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortingForVisibleView

IMPLEMENT_DYNCREATE(CSortingForVisibleView, CView)

BEGIN_MESSAGE_MAP(CSortingForVisibleView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSortingForVisibleView ����/�Ҹ�

CSortingForVisibleView::CSortingForVisibleView()
	: i(0)
	, j(0)
	, nRand(0)
	, nInitFlag(FALSE)
	, i2(0)
	, ColorR(0)
	, ColorG(0)
	, ColorB(0)
	, ColorR2(0)
	, ColorG2(0)
	, ColorB2(0)
	, ClubMode(false)
	, k(0)
{
}

CSortingForVisibleView::~CSortingForVisibleView()
{
}

BOOL CSortingForVisibleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSortingForVisibleView �׸���

void CSortingForVisibleView::OnDraw(CDC* /*pDC*/)
{
	CSortingForVisibleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CSortingForVisibleView �μ�

BOOL CSortingForVisibleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSortingForVisibleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSortingForVisibleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CSortingForVisibleView ����

#ifdef _DEBUG
void CSortingForVisibleView::AssertValid() const
{
	CView::AssertValid();
}

void CSortingForVisibleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortingForVisibleDoc* CSortingForVisibleView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortingForVisibleDoc)));
	return (CSortingForVisibleDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortingForVisibleView �޽��� ó����


void CSortingForVisibleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_wndMenu.MoveWindow(20, 695, 310, cy);
}


int CSortingForVisibleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_wndMenu.Create(IDD_MENUBG, this);
	m_wndMenu.ShowWindow(SW_SHOW);

	return 0;
}



void CSortingForVisibleView::OnPaint()
{
	/*-------------------------------------------------------------------------------------------
	#	������		������
	#	����ȯ��		Visual Basic 2017   
					Visual C++	 2017
	#	���߽���		2018.12.21.
	#	1 ���Ϸ�		2019.01.05. PM 2:17
	#	�����Ϸ�		2019.11.22. AM 12:11
	#	����			MFC�� ���� ���İ� ���� ������ �ð�ȭ �� ���α׷��Դϴ�.
					UI Thread�� ���� Thread�� �и��Ͽ����Ƿ� ���� ���߿� â�� �巡���ؼ� ��������
					���� ������ ������ �ʽ��ϴ�.
	--------------------------------------------------------------------------------------------*/

	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	
	// ȭ�鿡 �Ⱥ��̴� Memory DC ����
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	
	// bmp�� ���� rect�� �����մϴ�.
	CRect rect;
	GetClientRect(&rect);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldbmp = (CBitmap*)memdc.SelectObject(bmp);

	memdc.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	// y ������ǥ�� ���������� �ø��� ���� �����Դϴ�.
	int j = 0;

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	if (true == ClubMode)
	{
		// nRandomData[]�� ������ �׸�� �׸��ϴ�.
		for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
		{
			// ȭ�� ���ʿ� �׷����� �׸��� �ڵ��Դϴ�.
			memdc.FillSolidRect(0, j,
				nRandomData[i] * (5 / 2), 5 / 2,
				RGB(ColorR, ColorG, ColorB));

			// ȭ�� �����ʿ� �׷����� �׸��� �ڵ��Դϴ�.
			memdc.FillSolidRect(840, j,
				nRandomData2[i] * (5 / 2), 5 / 2,
				RGB(ColorR2, ColorG2, ColorB2));
			j += (5 / 2);

			ColorR = rand() % 255 + 1;
			ColorG = rand() % 255 + 1;
			ColorB = rand() % 255 + 1;

			ColorR2 = rand() % 255 + 1;
			ColorG2 = rand() % 255 + 1;
			ColorB2 = rand() % 255 + 1;
		}
	}
	else
	{
		// nRandomData[]�� ������ �׸�� �׸��ϴ�.
		for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
		{
			// ȭ�� ���ʿ� �׷����� �׸��� �ڵ��Դϴ�.
			memdc.FillSolidRect( 0, j, 
			nRandomData[i] * (5 / 2), 5 / 2,
			RGB(ColorR, ColorG, ColorB));

			// ȭ�� �����ʿ� �׷����� �׸��� �ڵ��Դϴ�.
			memdc.FillSolidRect( 840, j, 
			nRandomData2[i] * (5 / 2), 5 / 2,
			RGB(ColorR2, ColorG2, ColorB2));
			j += (5 / 2);
		}
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

	memdc.DeleteDC();
}


BOOL CSortingForVisibleView::OnEraseBkgnd(CDC* pDC)
{
	
	// return�� FALSE�� �ϴ� TRUE�� �ϴ� ����� ����,
	// ���� ���۸��� �����ϱ� ���ؼ� OnEraseBkgnd()�� �۵����� �ʵ���
	// �⺻ return �ڵ�� �ּ�ó���մϴ�.
	// return CView::OnEraseBkgnd(pDC);

	return FALSE;
}
