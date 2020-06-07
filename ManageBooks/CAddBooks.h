#pragma once


// CAddBooks 대화 상자

class CAddBooks : public CDialogEx
{
	DECLARE_DYNAMIC(CAddBooks)

public:
	CAddBooks(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddBooks();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CString mvalBookTitle;
//	CString mvalBookKeyword;
//	CString mvalBookSummary;
//	CComboBox mvalBookPublishYear;
	CEdit mctrlBookTitle;
//	CEdit mctrlBookKeyword;
//	CEdit mctrlBookSummary;
//	CComboBox mctrlBookPublishedYear;
//	CString mvalBookPublishedYear;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();


	CString mvalPublishedYear;
	CString mvalPublishedMonth;
	CString mvalPublishedDay;
	CString mvalSummary;
//	CString mvalKeyword;
	CString mvalBookName;
	CString mvalKeyword;
	CComboBox mctrlPublishedMonth;
	CComboBox mctrlPublishedDay;
	afx_msg void OnCbnSelchangeMonth();
};
