#pragma once
#include "afxdialogex.h"

#define IMG_WIDTH		800
#define IMG_HEIGHT		600
#define BTN_WIDTH		50
#define BTN_HEIGHT		25
#define COLOR_BLACK		0
#define COLOR_GRAY		150
#define COLOR_RED		RGB(0xff, 0x00, 0x00)
#define COLOR_YELLOW	RGB(0xff, 0xff, 0x00)
// CDlgCircle 대화 상자

class CDlgCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCircle)

public:
	CDlgCircle(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgCircle();
	void SetDiameter(int n);
	int m_nDiameter;				// 입력받은 원의 지름
	int m_nRadius;					// 원의 반지름
	int m_nSttX;					// 시작점x좌표
	int m_nSttY;					// 시작점y좌표
	int m_nGravityCenterX;			// 무게중심 x좌표
	int m_nGravityCenterY;			// 무게중심 y좌표
	void drawCircle();
	CImage m_Image;



	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgCircle };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void InitImage();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void drawData(CDC* pDC);
};
