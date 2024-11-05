#include "pch.h"
#include "FractalFacade.h"


// ����� ��� ��������� ���� ��������
void FractalFacade::SetFractalType(FractalFactory::FractalType type, CLab2View* pView) {
    fractal = FractalFactory::CreateFractal(type, pView); // ���������� fractal, ��� ���� ������
}

// ����� ��� ���������� ��������
void FractalFacade::ZoomIn(double scale) {
    FractalState::GetInstance()->zoomFactor *= scale;
}

// ����� ��� ���������� ��������
void FractalFacade::ZoomOut(double scale) {
    FractalState::GetInstance()->zoomFactor /= scale;
}

// ����� ��� �����������
void FractalFacade::Move(double dx, double dy) {
    FractalState* state = FractalState::GetInstance();
    state->centerX += dx;
    state->centerY += dy;
}

// ����� ��� ���������
void FractalFacade::Draw(CDC* pDC) {
    if (fractal) {
        fractal->Draw(pDC);
    }
}
