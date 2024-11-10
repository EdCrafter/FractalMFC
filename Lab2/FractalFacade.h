#pragma once
// FractalFacade.h
#include <memory> // ��� std::unique_ptr
#include "IFractal.h"
#include "FractalFactory.h"
#include "FractalState.h"


class FractalFacade {
private:
	std::unique_ptr<IFractal> facadeFractal;
	CLab2View* pView;
	COLORREF color;
public:
	enum DecoratorType {
		None,
		Color,
		Blur
	};
	FractalFacade() = default; // ����������� �� ���������
    FractalFacade(const FractalFacade& other); // ����������� �����������
    FractalFacade(CLab2View* pView); // ����������� � ����������
	FractalFactory::FractalType GetType() ;
	void SetFractalType(FractalFactory::FractalType type);
    bool ZoomIn(double scale = 1);
    bool ZoomOut(double scale = 1);
    void Move(double dx, double dy,double scale, bool centered);
	void MoveOut(double dx, double dy, double scale, bool centered);
    void Draw(CDC* pDC);
	void Reset();
	void SetColor(COLORREF color);
	void SetFractalDecorator(DecoratorType decoratorType);
};
