#pragma once
// Decorator pattern
#include "IFractal.h"

#include <memory>

class ColoredFractalDecorator : public IFractal {
private:
    std::unique_ptr<IFractal> fractal;
    COLORREF color;

public:
    ColoredFractalDecorator(std::unique_ptr<IFractal> f, COLORREF c)
        : fractal(std::move(f)), color(c) {}

    void Draw(CDC* pDC) override {
        CBrush brush(color);
        pDC->SelectObject(&brush);
        fractal->Draw(pDC);
        pDC->SelectStockObject(NULL_BRUSH);
    }
};
