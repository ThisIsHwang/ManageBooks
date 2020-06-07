// CAddBooks.cpp: 구현 파일
//

#include "pch.h"
#include "ManageBooks.h"
#include "CAddBooks.h"
#include "afxdialogex.h"


// CAddBooks 대화 상자

IMPLEMENT_DYNAMIC(CAddBooks, CDialogEx)

CAddBooks::CAddBooks(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, mvalPublishedYear(_T(""))
	, mvalPublishedMonth(_T(""))
	, mvalPublishedDay(_T(""))
	, mvalSummary(_T(""))
	, mvalKeyword(_T(""))
	, mvalBookName(_T(""))
	
{
	
}

CAddBooks::~CAddBooks()
{
}

void CAddBooks::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOKNAME, mctrlBookTitle);
	DDX_Text(pDX, IDC_YEAR, mvalPublishedYear);
	DDV_MaxChars(pDX, mvalPublishedYear, 4);
	DDX_Text(pDX, IDC_MONTH, mvalPublishedMonth);
	DDV_MaxChars(pDX, mvalPublishedMonth, 2);
	DDX_Text(pDX, IDC_DAY, mvalPublishedDay);
	DDV_MaxChars(pDX, mvalPublishedDay, 2);
	DDX_Text(pDX, IDC_BOOKSUM, mvalSummary);
	DDV_MaxChars(pDX, mvalSummary, 200);
	DDX_Text(pDX, IDC_BOOKNAME, mvalBookName);
	DDV_MaxChars(pDX, mvalBookName, 50);
	DDX_Text(pDX, IDC_KEYWORD, mvalKeyword);
	DDV_MaxChars(pDX, mvalKeyword, 100);
	DDX_Control(pDX, IDC_MONTH, mctrlPublishedMonth);
	DDX_Control(pDX, IDC_DAY, mctrlPublishedDay);
}


BEGIN_MESSAGE_MAP(CAddBooks, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddBooks::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_MONTH, &CAddBooks::OnCbnSelchangeMonth)
END_MESSAGE_MAP()


// CAddBooks 메시지 처리기


BOOL CAddBooks::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString s;
	for (int i = 0; i < 12; i++) {
		s.Format(L"%d", i + 1);
		mctrlPublishedMonth.AddString(s);
	}
	for (int i = 0; i < 31; i++) {
		s.Format(L"%d", i + 1);
		mctrlPublishedDay.AddString(s);
	}
	//윤달 체크 기능 추가
	//시스템 시간 받아오기 기능 추가
	//디폴트로 두기
	// TO1O:  여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddBooks::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	if (mvalBookName.Trim() == L"") {
		MessageBox(L"제목을 입력하세요.");
		return;
	}
	else if (mvalKeyword.Trim()[0] != L'#') {
		MessageBox(L"키워드를 #키워드 형식으로 입력하세요.");
		return;
	}
	else if (mvalSummary.Trim() == L"") {
		MessageBox(L"책 개요를 입력하세요.");
		return;
	}
	else if (mvalPublishedYear.Trim() == L"" && mvalPublishedDay.Trim() == L"" && mvalPublishedMonth.Trim() == L"") {
		MessageBox(L"출판년도를 입력하세요.");
		return;
	}
	if (mvalPublishedDay.Trim() > L"31" || _ttoi(mvalPublishedMonth.Trim()) > 12) {
		MessageBox(L"출판년도를 확인하세요.");
		return;
	}
	CDialogEx::OnOK();
}


void CAddBooks::OnCbnSelchangeMonth()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
