// wayviewDoc.h :  CwayviewDoc ��Ľӿ�
//


#pragma once

class CwayviewDoc : public CDocument
{
protected: // �������л�����
	CwayviewDoc();
	DECLARE_DYNCREATE(CwayviewDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CwayviewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

