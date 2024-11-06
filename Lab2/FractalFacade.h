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

public:
	FractalFacade() = default; // ����������� �� ���������
    FractalFacade(const FractalFacade& other); // ����������� �����������
    FractalFacade(CLab2View* pView); // ����������� � ����������
	FractalFactory::FractalType GetType() ;
    void SetFractalType(FractalFactory::FractalType type);
    void ZoomIn(double scale = 1);
    void ZoomOut(double scale = 1);
    void Move(double dx, double dy,double scale);
    void Draw(CDC* pDC);
};
