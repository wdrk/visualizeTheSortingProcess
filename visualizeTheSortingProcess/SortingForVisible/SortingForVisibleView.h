
// SortingForVisibleView.h : CSortingForVisibleView Ŭ������ �������̽�
//

#pragma once
#include "MenuBG.h"
#include "Graph.h"


class CSortingForVisibleDoc;

class CSortingForVisibleView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSortingForVisibleView();
	DECLARE_DYNCREATE(CSortingForVisibleView)

// Ư���Դϴ�.
public:
	CSortingForVisibleDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSortingForVisibleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

	CMenuBG		m_wndMenu;
	CGraph		m_wndGraph;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// nRandomData �迭�� �ε��� �����Դϴ�.
	int i;
	// nRandomData �迭�� ������ ���� ������ ����ϴ� �����Դϴ�.
	int j;
	int nRandomData[300] = { 0 };
	// ������ ���� �����ϴ� for ������ ����ϴ� �ӽ� ����� �����Դϴ�.
	int nRand;
	afx_msg void OnPaint();
	// ���α׷��� ó�� �����Ҷ��� 0, ��ư�� �ѹ��̶� �۵���Ų�ٸ� 1�� ���� �����մϴ�.
	int nInitFlag;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// nRandomData2[]�� ���� �ε����� ��Ÿ���µ� ���� �����Դϴ�.
	int i2;
	int nRandomData2[300] = { 0 };
	bool CheckArray[100] = { false };
	bool CheckArray2[100] = { false };
	// RGB �÷��߿� R ���� �����Դϴ�.
	int ColorR;
	// RGB �� �߿� G ���� �����Դϴ�.
	int ColorG;
	// RGB �� �߿� B ���� �����Դϴ�.
	int ColorB;
	// ȭ�� �����ʿ� ǥ���ϴ� �׷����� RGB�� �����Դϴ�.
	int ColorR2;
	int ColorG2;
	int ColorB2;
	// Club Mode ��ư���� OnPaint()�� ������ ���� �˷��ִ� ���Դϴ�.
	bool ClubMode;
	// Auto ��ư�� ������ ������ �����ϰ� �ִ� ���������� ��Ÿ���ϴ�.
	bool bAutoFlag = false;
	// ���α׷��� ó�� �����Ҷ��� FALSE, �� �Ŀ��� TRUE�� ��Ÿ���ϴ�.
	bool bInitFlag = false;
	int k;
};

#ifndef _DEBUG  // SortingForVisibleView.cpp�� ����� ����
inline CSortingForVisibleDoc* CSortingForVisibleView::GetDocument() const
   { return reinterpret_cast<CSortingForVisibleDoc*>(m_pDocument); }
#endif

