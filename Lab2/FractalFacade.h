#pragma once
// FractalFacade.h
#include <memory> // ��� std::unique_ptr
#include "IFractal.h"
#include "FractalFactory.h"
#include "FractalState.h"

// ��������������� ���������� ������
class CLab2View;

class FractalFacade {
private:
    std::unique_ptr<IFractal> fractal;

public:
    FractalFacade() = default; // ���������� ��������� �����������

    void SetFractalType(FractalFactory::FractalType type, CLab2View* pView);
    void ZoomIn(double scale = 1);
    void ZoomOut(double scale = 1);
    void Move(double dx, double dy);
    void Draw(CDC* pDC);
};
