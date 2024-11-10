#include <omp>

#include "pch.h"
#include "IFractal.h"
#include "Lab2View.h"
#include "Lab2Doc.h"

#include <stack>
#include <tuple>


#define M_PI 3.14159265358979323846

void KochFractal::DrawKochSnowflakeIterative(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points) {
	std::stack<std::tuple<CPoint, CPoint, int>> stack;
	stack.push(std::make_tuple(start, end, depth));

	while (!stack.empty()) {
		auto [currentStart, currentEnd, currentDepth] = stack.top();
		stack.pop();

		if (currentDepth == 0) {
			points.push_back(currentStart);
			points.push_back(currentEnd);
		}
		else {
			CPoint p1((2 * currentStart.x + currentEnd.x) / 3, (2 * currentStart.y + currentEnd.y) / 3);
			CPoint p2((currentStart.x + 2 * currentEnd.x) / 3, (currentStart.y + 2 * currentEnd.y) / 3);

			double angle = atan2(currentEnd.y - currentStart.y, currentEnd.x - currentStart.x) + M_PI / 3;
			double length = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
			CPoint peak(p1.x + length * cos(angle), p1.y + length * sin(angle));

			stack.push(std::make_tuple(p2, currentEnd, currentDepth - 1));
			stack.push(std::make_tuple(peak, p2, currentDepth - 1));
			stack.push(std::make_tuple(p1, peak, currentDepth - 1));
			stack.push(std::make_tuple(currentStart, p1, currentDepth - 1));
		}
	}
}

void KochFractal::Reset()
{
	CRect rect;
	pView->GetClientRect(&rect);
	state->centerWX = rect.Width() / 2;
	state->centerWY = rect.Height() / 2;
	state->zoomFactor = 1;
	state->depth = 5;
}

void KochFractal::DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points)
{
	if (depth == 0) {
		// Если видим, добавляем конечные точки в массив
		
		//if (IsVisible(pDC, start) || IsVisible(pDC, end)) { // IsVisible - true always
			points.push_back(start);
			points.push_back(end);
		//}
		/*
		else {
			CRect clientRect;
			pView->GetClientRect(&clientRect);
			double cx, cy;
			if (end.x < 0 || end.y < 0) {
				cx = -clientRect.Width() / 2;
				cy = clientRect.Height() / 2;
			}
			else if (end.x < 0) {
				cx = -clientRect.Width() / 2;
				cy = -clientRect.Height() / 2;
			}
			else if (end.y < 0) {
				cx = clientRect.Width() / 2;
				cy = clientRect.Height() / 2;
			}
			else {
				cx = clientRect.Width() / 2;
				cy = -clientRect.Height() / 2;
			}
			CPoint p(cx, cy);
			if (points.size() > 0 && points.back() != p) {
				points.push_back(p);
			}
		}*/
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
}

void KochFractal::DrawSnowflakeAndFill(CDC* pDC, CPoint vertex1, CPoint vertex2, CPoint vertex3, int depth)
{
	std::vector<CPoint> points;
	points.reserve(7000);
	DrawKochSnowflake(pDC, vertex1, vertex2, depth, points);
	DrawKochSnowflake(pDC, vertex2, vertex3, depth, points);
	DrawKochSnowflake(pDC, vertex3, vertex1, depth, points);
	/*DrawKochSnowflakeIterative(pDC, vertex1, vertex2, depth, points);
	DrawKochSnowflakeIterative(pDC, vertex2, vertex3, depth, points);
	DrawKochSnowflakeIterative(pDC, vertex3, vertex1, depth, points);*/

	if (points.size() > 2) {
		CBrush brush(color);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Polygon(points.data(), points.size());

		pDC->SelectObject(pOldBrush);
	}
}


KochFractal::KochFractal(CLab2View* pView) : IFractal(pView)

{
	CRect rect;
	pView->GetClientRect(&rect);
	state->centerWX =  rect.Width() / 2;
	state->centerWY =  rect.Height() / 2;
	state->zoomFactor = 1;
	state->depth = 5;
	state->minDepth = 5;
	state->maxDepth = 9;
}

int KochFractal::GetType() const
{
    return 0;
}

KochFractal::KochFractal(const KochFractal&)
{
	//AfxMessageBox(L"Copy constructor");
	this->pView = pView;
	this->state = state;
}

std::unique_ptr<IFractal> KochFractal::Clone() const
{
	//AfxMessageBox(L"Clone");
	return std::make_unique<KochFractal>(*this);
}

void KochFractal::Draw(CDC* pDC)
{
	//AfxMessageBox(L"Draw");
    CRect rect;
    pView->GetClientRect(&rect);
    
	double sizeKoch = 3000 * state->depth* state->depth + 500;
    pDC->SetMapMode(MM_ISOTROPIC);
    pDC->SetWindowExt(sizeKoch *  1./state->zoomFactor, sizeKoch * 1. / state->zoomFactor);
    pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(state->centerWX, state->centerWY);
	double p1 = sizeKoch / 3.; 
	double p2 = sizeKoch  /  (3 * sqrt(3));

	CPoint vertex1(-p1, p2);
	CPoint vertex2(p1, p2);
	CPoint vertex3(0, -2*p2); 

	DrawSnowflakeAndFill(pDC, vertex1, vertex2, vertex3, state->depth);
	
}

bool KochFractal::IsVisible(CDC* pDC, CPoint a)
{
	return true;

	CRect clientRect;
	//pView->Get
	// Получаем размеры области отображения с учетом ViewportExt
	pDC->GetClipBox(&clientRect);
	CRect rect;
	pView->GetClientRect(&rect);

	if (clientRect.Width() == 0 || clientRect.Height() == 0) {
		AfxMessageBox(_T("Ошибка: размеры области отображения равны нулю"));
		return false;
	}
	
	double offsetX ;
	double offsetY ;

	if (state->zoomFactor == 1) {
		offsetX = 0;
		offsetY = 0;
	}
	else {
		offsetX = (rect.Width() /2. - state->centerWX ) * clientRect.Width() / rect.Width();
		offsetY = (rect.Height()/2. - state->centerWY) * clientRect.Height() / rect.Height();
	}
	
	CRect visibleRect;
	visibleRect.SetRect(
		1 * (offsetX-clientRect.Width() / 2  ), //  * state->zoomFactor  Левый край
		1.6 * (offsetY - clientRect.Height() / 2), // * state->zoomFactor   Верхний край
		1 * (offsetX + clientRect.Width() / 2), //  * state->zoomFactor  Правый край
		1.6 * (offsetY + clientRect.Height() / 2)  //  * state->zoomFactor  Нижний край
	);
	CPen pen(PS_SOLID, 15, RGB(35, 120, 120));
	pDC->SelectObject(&pen);
	pDC->MoveTo(visibleRect.left, visibleRect.top);
	pDC->LineTo(visibleRect.right, visibleRect.top);
	pDC->LineTo(visibleRect.right, visibleRect.bottom);
	pDC->LineTo(visibleRect.left, visibleRect.bottom);
	pDC->LineTo(visibleRect.left, visibleRect.top);
	pDC->SelectObject(pDC->GetCurrentPen());

	if (a.x >= visibleRect.left && a.x <= visibleRect.right && a.y <= visibleRect.top && a.y >= visibleRect.bottom) {
		return true;
	}
	return false;
}

void MandelbrotFractal::Draw(CDC* pDC)
{
	if (!pView) {
		AfxMessageBox(L"Error: pView is nullptr");
		return;
	}
	CRect rect;
	pView->GetClientRect(&rect);
	if (rect.Width() == 0 || rect.Height() == 0) {
		AfxMessageBox(L"Error: rect.Width() == 0 || rect.Height() == 0");
		return;
	}
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(1, 1);
	pDC->SetViewportExt(rect.Width(), rect.Height());
	pDC->SetViewportOrg(0,0);
	const int maxIterations = 500; // Number of iterations for Mandelbrot calculation
	double scaleX = 4.0 / state->zoomFactor / rect.Width();
	double scaleY = 4.0 / state->zoomFactor / rect.Height();

	double minX = -2.0 + (state->centerWX - rect.Width() / 2) * scaleX;
	double minY = -2.0 + (state->centerWY - rect.Height() / 2) * scaleY;

	// The rest of the Mandelbrot drawing code
	std::vector<unsigned char> pixels(rect.Width() * rect.Height() * 4); // RGBA array

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

			unsigned char* pixel = &pixels[(py * rect.Width() + px) * 4];
			if (iteration < maxIterations) {
				pixel[0] = (iteration % 256); // Red
				pixel[1] = (iteration % 128); // Green
				pixel[2] = (iteration % 64);  // Blue
				pixel[3] = 255;               // Alpha
			}
			else {
				pixel[0] = 0;   // Red
				pixel[1] = 0;   // Green
				pixel[2] = 0;   // Blue
				pixel[3] = 255; // Alpha
			}
		}
	}

	// Render the pixel data
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = rect.Width();
	bmi.bmiHeader.biHeight = rect.Height(); 
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

MandelbrotFractal::MandelbrotFractal(CLab2View* pView) : IFractal(pView)
{
	CRect rect;
	pView->GetClientRect(&rect);
	state->centerWX = rect.Width() / 2;
	state->centerWY = rect.Height() /2;
	
	state->zoomFactor = 1;
	state->depth = 5;
	state->maxDepth = 700;
}

void MandelbrotFractal::Reset()
{
	CRect rect;
	pView->GetClientRect(&rect);
	state->centerWX = rect.Width() / 2;
	state->centerWY = rect.Height() / 2;
	state->zoomFactor = 1;
	state->depth = 5;
}
