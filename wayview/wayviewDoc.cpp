// wayviewDoc.cpp :  CwayviewDoc ���ʵ��
//

#include "stdafx.h"
#include "wayview.h"

#include "wayviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwayviewDoc

IMPLEMENT_DYNCREATE(CwayviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CwayviewDoc, CDocument)
END_MESSAGE_MAP()


// CwayviewDoc ����/����

CwayviewDoc::CwayviewDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CwayviewDoc::~CwayviewDoc()
{
}

BOOL CwayviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CwayviewDoc ���л�

void CwayviewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CwayviewDoc ���

#ifdef _DEBUG
void CwayviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CwayviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CwayviewDoc ����
