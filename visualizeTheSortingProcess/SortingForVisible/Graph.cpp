// Graph.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SortingForVisible.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SortingForVisibleView.h"

// CGraph ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGraph, CDialog)

CGraph::CGraph(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GRAPH, pParent)
{

}

CGraph::~CGraph()
{
}

void CGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGraph, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGraph �޽��� ó�����Դϴ�.


void CGraph::OnPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
