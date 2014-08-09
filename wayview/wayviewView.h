// wayviewView.h : CwayviewView ��Ľӿ�
//


#pragma once


class CwayviewView : public CView
{
protected: // �������л�����
	CwayviewView();
	DECLARE_DYNCREATE(CwayviewView)

// ����
public:
	CwayviewDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CwayviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonZoomin();
	afx_msg void OnButtonZoomout();
	afx_msg void OnButtonMoveright();
	afx_msg void OnButtonMoveleft();
	afx_msg void OnButtonMoveup();
	afx_msg void OnButtonMovedown();
	afx_msg void OnGoto();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // wayviewView.cpp �ĵ��԰汾
inline CwayviewDoc* CwayviewView::GetDocument() const
   { return reinterpret_cast<CwayviewDoc*>(m_pDocument); }
#endif

