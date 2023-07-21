// CDlgCircle.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CDlgCircle.h"


// CDlgCircle 대화 상자

IMPLEMENT_DYNAMIC(CDlgCircle, CDialogEx)

CDlgCircle::CDlgCircle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgCircle, pParent)
{

}

CDlgCircle::~CDlgCircle()
{
}

void CDlgCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCircle, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CDlgCircle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitImage();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgCircle::InitImage()
{
	int nBpp = 8;
	m_Image.Create(IMG_WIDTH, -IMG_HEIGHT, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, COLOR_GRAY, IMG_WIDTH * IMG_HEIGHT);
}


void CDlgCircle::SetDiameter(int n)
{
	m_nDiameter = n;
}

void CDlgCircle::drawCircle()
{
	m_nRadius = m_nDiameter / 2;
	m_nSttX = rand() % (IMG_WIDTH - m_nDiameter);
	m_nSttY = rand() % (IMG_HEIGHT - m_nDiameter);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	int nPitch = m_Image.GetPitch();

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, COLOR_GRAY, IMG_WIDTH * IMG_HEIGHT);

	int nCenterX = m_nSttX + m_nRadius;
	int nCenterY = m_nSttY + m_nRadius;

	for (int j = m_nSttY; j < m_nSttY + m_nDiameter; j++) {			// 무게중심을 구하기 & 원 안의영역을 검정색으로 칠함
		for (int i = m_nSttX; i < m_nSttX + m_nDiameter; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, m_nRadius))
			{
				fm[j * nPitch + i] = COLOR_BLACK;
				nSumX += i;
				nSumY += j;
				nCount++;
			}

		}
	}

	if (nCount == 0) {									// 너무 작은숫자를 입력 받았을 시 예외처리
		AfxMessageBox(_T("Input value is too low."));
		return;
	}


	m_nGravityCenterX = nSumX / nCount;
	m_nGravityCenterY = nSumY / nCount;

	Invalidate();

}

void CDlgCircle::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;				// 원 둘레를 그리는 펜
	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush;			// 원 안쪽 영역을 투명하게 그림
	brush.CreateStockObject(NULL_BRUSH);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	rect.SetRect(m_nSttX, m_nSttY, m_nSttX + m_nDiameter, m_nSttY + m_nDiameter);
	pDC->Ellipse(rect);


	pDC->SelectObject(pOldBrush);

	CPen center_pen;		// 무게중심 그리는 펜
	center_pen.CreatePen(PS_SOLID, 1, COLOR_RED);
	pDC->SelectObject(&center_pen);
	pDC->MoveTo(m_nGravityCenterX - 5, m_nGravityCenterY);
	pDC->LineTo(m_nGravityCenterX + 5, m_nGravityCenterY);
	pDC->MoveTo(m_nGravityCenterX, m_nGravityCenterY - 5);
	pDC->LineTo(m_nGravityCenterX, m_nGravityCenterY + 5);

	pDC->SelectObject(pOldPen);


}

void CDlgCircle::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
	drawData(&dc);


}

bool CDlgCircle::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	int bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) { // In Circle
		bRet = true;
	}
	else
		bRet = false;

	return bRet;
}