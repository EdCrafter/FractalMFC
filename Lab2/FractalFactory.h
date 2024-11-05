#pragma once
// Factory pattern
#include <memory>


#include "IFractal.h"

class CLab2View;

class FractalFactory {
public:
    enum FractalType {
        Koch,
        Mandelbrot
    };

    static std::unique_ptr<IFractal> CreateFractal(FractalType type,CLab2View* pView);
};

