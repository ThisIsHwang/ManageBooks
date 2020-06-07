
// ManageBooksView.h: CManageBooksView 클래스의 인터페이스
//

#pragma once
#define COLUMN_NUMBER 4

class CManageBooksView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CManageBooksView() noexcept;
	DECLARE_DYNCREATE(CManageBooksView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MANAGEBOOKS_FORM };
#endif

// 특성입니다.
public:
	CManageBooksDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CManageBooksView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedAddbook();
	CListCtrl mctrlList;
	afx_msg void OnBnClickedSearch();
};
void KeywordToTag(CAddBooks* dg, CManageBooksDoc* p);
int GetCharCount(CString str, char var);
#ifndef _DEBUG  // ManageBooksView.cpp의 디버그 버전
inline CManageBooksDoc* CManageBooksView::GetDocument() const
   { return reinterpret_cast<CManageBooksDoc*>(m_pDocument); }
#endif

