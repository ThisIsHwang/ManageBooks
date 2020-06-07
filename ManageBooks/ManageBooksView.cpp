
// ManageBooksView.cpp: CManageBooksView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ManageBooks.h"
#endif

#include "ManageBooksDoc.h"
#include "ManageBooksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// CManageBooksView

IMPLEMENT_DYNCREATE(CManageBooksView, CFormView)

BEGIN_MESSAGE_MAP(CManageBooksView, CFormView)
	
	ON_BN_CLICKED(IDC_ADDBOOK, &CManageBooksView::OnBnClickedAddbook)
	ON_BN_CLICKED(IDC_SEARCH, &CManageBooksView::OnBnClickedSearch)
END_MESSAGE_MAP()

// CManageBooksView 생성/소멸

CManageBooksView::CManageBooksView() noexcept
	: CFormView(IDD_MANAGEBOOKS_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CManageBooksView::~CManageBooksView()
{
}

void CManageBooksView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mctrlList);
}

BOOL CManageBooksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CManageBooksView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CManageBooksDoc* p = GetDocument();
	CString s;
	static int initialized = 0;
	LV_COLUMN col;
	int temp = 0;
	WCHAR col_name[COLUMN_NUMBER][10] = { L"책 제목", L"키워드", L"책 개요", L"출판년도" };
	int width[COLUMN_NUMBER] = { 100, 200, 250, 100 };
	if (!initialized) {
		for (int i = 0; i < COLUMN_NUMBER; i++) {
			col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			col.fmt = LVCFMT_CENTER;
			col.pszText = col_name[i];
			col.cx = width[i];
			col.cchTextMax = width[i];
			mctrlList.InsertColumn(i, &col);
		}
		mctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		mctrlList.InsertItem(p->mBookCnt, p->mBook[p->mBookCnt].title);
	}
	initialized = 1;
	mctrlList.DeleteAllItems();

	for (int i = 0; i < p->mBookCnt; i++) {
		s = L"";
		mctrlList.InsertItem(i, p->mBook[i].title);
		for (int ii = 0; ii < 5; ii++)
		{
			CString c = p->mBook[i].keywords[ii];
			if (c == L"")
				continue;
			s = s + L"#" + p->mBook[i].keywords[ii] + L" ";
		}
		
		mctrlList.SetItemText(i, 1, s);
		mctrlList.SetItemText(i, 2, p->mBook[i].BookSummary);
		s = "";
		int Month = (p->mBook[i].PublishedMonthDay & 0x1E0) >> 5;
		int Day = (p->mBook[i].PublishedMonthDay & 0x1F );
		if (p->mBook[i].PublishedYear != 0) 
			s.Format(L"%d.", p->mBook[i].PublishedYear);
		if (Month != 0) {
			CString t;
			t.Format(L"%d", (p->mBook[i].PublishedMonthDay & 0x1E0) >> 5);
			s = s + t + L".";
		}
		if(Day != 0){
			CString t;
			t.Format(L"%d", p->mBook[i].PublishedMonthDay & 0x1F);
			s = s + t + L".";
		}
		mctrlList.SetItemText(i, 3, s);
	}
		
}


// CManageBooksView 진단

#ifdef _DEBUG
void CManageBooksView::AssertValid() const
{
	CFormView::AssertValid();
}

void CManageBooksView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CManageBooksDoc* CManageBooksView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CManageBooksDoc)));
	return (CManageBooksDoc*)m_pDocument;
}
#endif //_DEBUG


// CManageBooksView 메시지 처리기


void CManageBooksView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CManageBooksView::OnBnClickedAddbook()
{
	CAddBooks dg;
	CManageBooksDoc* p = GetDocument();
	CString s;
	if (dg.DoModal() == IDOK) {
		wcscpy_s(p->mBook[p->mBookCnt].title, dg.mvalBookName);
		wcscpy_s(p->mBook[p->mBookCnt].BookSummary, dg.mvalSummary);
		p->mBook[p->mBookCnt].PublishedYear = _ttoi(dg.mvalPublishedYear);
		p->mBook[p->mBookCnt].PublishedMonthDay = _ttoi(dg.mvalPublishedMonth) << 5 | _ttoi(dg.mvalPublishedDay);
		KeywordToTag(&dg, p);

		mctrlList.InsertItem(p->mBookCnt, p->mBook[p->mBookCnt].title);
		for (int i = 0; i < GetCharCount(dg.mvalKeyword, '#'); i++)
		{
			s = s + L"#" + p->mBook[p->mBookCnt].keywords[i] + L" ";
		}
		mctrlList.SetItemText(p->mBookCnt, 1, s);
		mctrlList.SetItemText(p->mBookCnt, 2, p->mBook[p->mBookCnt].BookSummary);
		if (dg.mvalPublishedYear != L"") {
			s = L"" + dg.mvalPublishedYear + L".";
		}
		if (dg.mvalPublishedMonth != L"") {
			s = s + dg.mvalPublishedMonth + L".";
		}
		if (dg.mvalPublishedDay != L"") {
			s = s + dg.mvalPublishedDay + L".";
		}
		mctrlList.SetItemText(p->mBookCnt, 3, s);
		p->mBookCnt++;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int GetCharCount(CString str, char var)
{
	int count = 0;
	for (int i = 0; i < str.GetLength(); i++)
		if (str[i] == var) count++;
	if (count > 5) return 5;
	return count;
}


void KeywordToTag(CAddBooks* dg, CManageBooksDoc* p){
		CString tempstr;
		int cnt = 0;
		for (int i = 0; i < GetCharCount(dg->mvalKeyword, '#')+1; i++)
		{
			AfxExtractSubString(tempstr, dg->mvalKeyword, i, '#');
			tempstr.Replace(_T(" "), NULL);
			if (tempstr != L"") {
				wcscpy_s(p->mBook[p->mBookCnt].keywords[cnt], tempstr);
				cnt++;
			}
		}
}


void CManageBooksView::OnBnClickedSearch()
{
	KeywordSearch dg;
	CString s;
	dg.DoModal();
}
