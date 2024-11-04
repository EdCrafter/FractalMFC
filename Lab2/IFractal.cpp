#include "pch.h"
#include "IFractal.h"

#define M_PI 3.14159265358979323846


void KochFractal::DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points)
{
	if (depth == 0) {
		// ≈сли видим, добавл€ем конечные точки в массив
		
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


void KochFractal::Draw(CDC* pDC)
{
	CPoint vertex1(-2400, 1200);
	CPoint vertex2(2400, 1200);
	CPoint vertex3(0, -2400);
	int depth = 8;
	DrawSnowflakeAndFill(pDC, vertex1, vertex2, vertex3, depth);
}

void MandelbrotFractal::Draw(CDC* pDC)
{
	int y = 1;
}
