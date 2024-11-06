#include <omp>

#include "pch.h"
#include "IFractal.h"
#include "Lab2View.h"
#include "Lab2Doc.h"


#define M_PI 3.14159265358979323846



void KochFractal::DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points)
{
	if (depth == 0) {
		// Если видим, добавляем конечные точки в массив
		
		if (pView->IsVisible(start) || pView->IsVisible(end)) {
			points.push_back(start);
			points.push_back(end);
			/*pDC->MoveTo(start);
			pDC->LineTo(end);*/
		}
	}
	else {
		CPoint p1((2 * start.x + end.x) / 3, (2 * start.y + end.y) / 3);
		CPoint p2((start.x + 2 * end.x) / 3, (start.y + 2 * end.y) / 3);

		double angle = atan2(end.y - start.y, end.x - start.x) + M_PI / 3;
		double length = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
		CPoint peak(p1.x + length * cos(angle), p1.y + length * sin(angle));
		DrawKochSnowflake(pDC, start, p1, depth - 1, points);
		DrawKochSnowflake(pDC, p1, peak, depth - 1, points);
		DrawKochSnowflake(pDC, peak, p2, depth - 1, points);
		DrawKochSnowflake(pDC, p2, end, depth - 1, points);
	}
	/*pDC->SelectObject(pOldPen);*/
}

void KochFractal::DrawSnowflakeAndFill(CDC* pDC, CPoint vertex1, CPoint vertex2, CPoint vertex3, int depth)
{
	std::vector<CPoint> points;
	points.reserve(7000);
	DrawKochSnowflake(pDC, vertex1, vertex2, depth, points);
	DrawKochSnowflake(pDC, vertex2, vertex3, depth, points);
	DrawKochSnowflake(pDC, vertex3, vertex1, depth, points);

	if (points.size() > 2) {
		CBrush brush(RGB(30, 150, 155));
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Polygon(points.data(), points.size());

		pDC->SelectObject(pOldBrush);
	}
}


KochFractal::KochFractal(CLab2View* pView) : IFractal(pView)

{
    CLab2Doc* pDoc = pView->GetDocument();
    if (pDoc) {
        CRect clientRect;
        pView->GetClientRect(&clientRect);
		state->centerX = clientRect.Width() / 2;
		state->centerY = clientRect.Height() / 2;
    }
}

int KochFractal::GetType() const
{
    return 0;
}

KochFractal::KochFractal(const KochFractal&)
{
	this->pView = pView;
	this->state = state;
}

std::unique_ptr<IFractal> KochFractal::Clone() const
{
	return std::make_unique<KochFractal>(*this);
}

void KochFractal::Draw(CDC* pDC)
{

    CRect rect;
    pView->GetClientRect(&rect);
    
    pDC->SetMapMode(MM_ISOTROPIC);
    pDC->SetWindowExt(6000 * 1. / state->zoomFactor, 6000 * 1. / state->zoomFactor);
    pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(state->centerX, state->centerY);

	CPoint vertex1(-2400, 1200);
	CPoint vertex2(2400, 1200);
	CPoint vertex3(0, -2400);
	int depth = 6;
	DrawSnowflakeAndFill(pDC, vertex1, vertex2, vertex3, depth);
}

void MandelbrotFractal::Draw(CDC* pDC)
{
    pDC->SetMapMode(MM_TEXT);
    pDC->SetWindowExt(1, 1);
    pDC->SetViewportExt(1, 1);

    CRect rect;
    pView->GetClientRect(&rect);
    const int maxIterations = 500; // Увеличьте количество итераций
	double scaleX = 4.0 / state->zoomFactor / rect.Width();
	double scaleY = 4.0 / state->zoomFactor / rect.Height();
	double minX = -2.0 + state->centerX * scaleX;
	double minY = -2.0 + state->centerY * scaleY;

    // Используем массив для хранения цветов
    std::vector<unsigned char> pixels(rect.Width() * rect.Height() * 4); // 4 байта на пиксель (RGBA)
#pragma omp parallel for
    for (int py = 0; py < rect.Height(); ++py) {
        for (int px = 0; px < rect.Width(); ++px) {
            double x0 = minX + px * scaleX;
            double y0 = minY + py * scaleY;
            double x = 0.0, y = 0.0;
            int iteration = 0;

            while (x * x + y * y <= 4 && iteration < maxIterations) {
                double xTemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xTemp;
                iteration++;
            }

            unsigned char* pixel = &pixels[(py * rect.Width() + px) * 4]; // 4 байта на пиксель
            if (iteration < maxIterations) {
                pixel[0] = (iteration % 256);     // Red
                pixel[1] = (iteration % 128);     // Green
                pixel[2] = (iteration % 64);      // Blue
                pixel[3] = 255;                   // Alpha
            }
            else {
                pixel[0] = 0;  // Red
                pixel[1] = 0;  // Green
                pixel[2] = 0;  // Blue
                pixel[3] = 255; // Alpha
            }
        }
    }

    // Отрисовка
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = rect.Width();
    bmi.bmiHeader.biHeight = -rect.Height(); // негативное значение для правильной ориентации
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    ::SetDIBitsToDevice(
        pDC->GetSafeHdc(),
        0, 0, rect.Width(), rect.Height(),
        0, 0, 0, rect.Height(),
        pixels.data(), &bmi, DIB_RGB_COLORS
    );
}

int MandelbrotFractal::GetType() const
{
    return 1;
}

std::unique_ptr<IFractal> MandelbrotFractal::Clone() const
{
	return std::make_unique<MandelbrotFractal>(*this);
}

IFractal::IFractal(const IFractal&)
{
	this->pView = pView;
	this->state = state;
}
