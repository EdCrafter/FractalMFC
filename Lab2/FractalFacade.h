#pragma once
// FractalFacade.h
#include <memory> // Для std::unique_ptr
#include "IFractal.h"
#include "FractalFactory.h"
#include "FractalState.h"

// Предварительное объявление класса
class CLab2View;

class FractalFacade {
private:
    std::unique_ptr<IFractal> fractal;

public:
    FractalFacade() = default; // Используем дефолтный конструктор

    void SetFractalType(FractalFactory::FractalType type, CLab2View* pView);
    void ZoomIn(double scale = 1);
    void ZoomOut(double scale = 1);
    void Move(double dx, double dy);
    void Draw(CDC* pDC);
};
