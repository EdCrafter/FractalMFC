#include "pch.h"
#include "FractalFacade.h"


// Метод для установки типа фрактала
void FractalFacade::SetFractalType(FractalFactory::FractalType type, CLab2View* pView) {
    fractal = FractalFactory::CreateFractal(type, pView); // Используем fractal, как член класса
}

// Метод для увеличения масштаба
void FractalFacade::ZoomIn(double scale) {
    FractalState::GetInstance()->zoomFactor *= scale;
}

// Метод для уменьшения масштаба
void FractalFacade::ZoomOut(double scale) {
    FractalState::GetInstance()->zoomFactor /= scale;
}

// Метод для перемещения
void FractalFacade::Move(double dx, double dy) {
    FractalState* state = FractalState::GetInstance();
    state->centerX += dx;
    state->centerY += dy;
}

// Метод для отрисовки
void FractalFacade::Draw(CDC* pDC) {
    if (fractal) {
        fractal->Draw(pDC);
    }
}
