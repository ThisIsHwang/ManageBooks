// KeywordSearch.cpp: 구현 파일
//

#include "pch.h"
#include "ManageBooks.h"
#include "KeywordSearch.h"
#include "afxdialogex.h"
#include "ManageBooksDoc.h"
#include "ManageBooksView.h"
#include <afxrich.h>
#include <afxhtml.h>
#include "MainFrm.h"


// KeywordSearch 대화 상자

IMPLEMENT_DYNAMIC(KeywordSearch, CDialogEx)

KeywordSearch::KeywordSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, mvalKeywords(_T(""))
{

}

KeywordSearch::~KeywordSearch()
{
}

void KeywordSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mctrlList);
	DDX_Text(pDX, IDC_EDIT1, mvalKeywords);
}


BEGIN_MESSAGE_MAP(KeywordSearch, CDialogEx)
	ON_BN_CLICKED(IDOK, &KeywordSearch::OnBnClickedOk)
END_MESSAGE_MAP()


// KeywordSearch 메시지 처리기


BOOL KeywordSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString s;
	LV_COLUMN col;
	int temp = 0;
	WCHAR col_name[COLUMN_NUMBER][10] = { L"책 제목", L"키워드", L"책 개요", L"출판년도" };
	int width[COLUMN_NUMBER] = { 100, 200, 250, 100 };
		for (int i = 0; i < COLUMN_NUMBER; i++) {
			col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			col.fmt = LVCFMT_CENTER;
			col.pszText = col_name[i];
			col.cx = width[i];
			col.cchTextMax = width[i];
			mctrlList.InsertColumn(i, &col);
		}
		mctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
}

void SearchRecursive(int SearchedBookIndex[100], int* pSearchedBookCnt, CString SearchTags[], int recursiveCnt) {
	int tempCnt = *pSearchedBookCnt;
	if (recursiveCnt == 5 || SearchTags[recursiveCnt] == L"" ) return;
	*pSearchedBookCnt = 0;
	CManageBooksDoc* p = (CManageBooksDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	for (int i = 0; i < tempCnt; i++) 
		for (int ii = 0; ii < 5; ii++) 
			if (p->mBook[SearchedBookIndex[i]].keywords[ii] == SearchTags[recursiveCnt] && SearchTags[recursiveCnt] != L"") 
				SearchedBookIndex[(*pSearchedBookCnt)++] = SearchedBookIndex[i];
	
	recursiveCnt++;
	SearchRecursive(SearchedBookIndex, pSearchedBookCnt, SearchTags, recursiveCnt);
}

void KeywordSearch::OnBnClickedOk()
{
	UpdateData();
	CManageBooksDoc* p = (CManageBooksDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	CString s[5];
	CString s2;
	int SearchedBookIndex[100];
	for (int i = 0; i < p->mBookCnt; i++) {
		SearchedBookIndex[i] = i;
	}
	int SearchedBookCnt = p->mBookCnt;
	KeywordToTag(mvalKeywords, s);
	SearchRecursive(SearchedBookIndex, &SearchedBookCnt, s, 0);
	mctrlList.DeleteAllItems();
	for (int i = 0; i < SearchedBookCnt; i++) {
		s2 = L"";
		mctrlList.InsertItem(i, p->mBook[SearchedBookIndex[i]].title);
		for (int ii = 0; ii < 5; ii++)
		{
			CString c = p->mBook[SearchedBookIndex[i]].keywords[ii];
			if (c == L"")
				continue;
			s2 = s2 + L"#" + p->mBook[SearchedBookIndex[i]].keywords[ii] + L" ";
		}

		mctrlList.SetItemText(i, 1, s2);
		mctrlList.SetItemText(i, 2, p->mBook[SearchedBookIndex[i]].BookSummary);
		s2 = "";
		int a = (p->mBook[SearchedBookIndex[i]].PublishedMonthDay & 0x1E0) >> 5;
		int b = (p->mBook[SearchedBookIndex[i]].PublishedMonthDay & 0x1F);
		if (p->mBook[SearchedBookIndex[i]].PublishedYear != 0)
			s2.Format(L"%d.", p->mBook[SearchedBookIndex[i]].PublishedYear);
		if (a != 0) {
			CString t;
			t.Format(L"%d", (p->mBook[SearchedBookIndex[i]].PublishedMonthDay & 0x1E0) >> 5);
			s2 = s2 + t + L".";
		}
		if (b != 0) {
			CString t;
			t.Format(L"%d", p->mBook[SearchedBookIndex[i]].PublishedMonthDay & 0x1F);
			s2 = s2 + t + L".";
		}
		mctrlList.SetItemText(i, 3, s2);
	}
}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
void KeywordToTag(CString str, CString s[]) {
	CString tempstr;
	int cnt = 0;
	for (int i = 0; i < GetCharCount(str, '#') + 1; i++)
	{
		AfxExtractSubString(tempstr, str, i, '#');
		tempstr.Replace(_T(" "), NULL);
		if (tempstr != L"") {
			s[cnt]= tempstr;
			cnt++;
		}
	}
}

