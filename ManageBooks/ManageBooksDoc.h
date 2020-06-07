
// ManageBooksDoc.h: CManageBooksDoc 클래스의 인터페이스
//

#include <vector>
#include <winnt.h>
#pragma once
typedef struct {
	WCHAR title[51];
	WCHAR keywords[5][21];
	WCHAR BookSummary[201];
	int PublishedYear;
	WCHAR PublishedMonthDay;
}Book;

class CManageBooksDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CManageBooksDoc() noexcept;
	DECLARE_DYNCREATE(CManageBooksDoc)
	
// 특성입니다.
public:	
	//std::vector<Book> mBook;
	Book mBook[100];
	int mBookCnt;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CManageBooksDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
