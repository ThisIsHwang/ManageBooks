#pragma once
#include <winnt.h>
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

class KeywordSearch : public CDialogEx
{
	DECLARE_DYNAMIC(KeywordSearch)

public:
	KeywordSearch(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~KeywordSearch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	CListCtrl mctrlList;
	afx_msg void OnBnClickedOk();
	CString mvalKeywords;
};



void KeywordToTag(CString str, CString s[]);
