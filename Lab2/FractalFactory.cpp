#include "pch.h"
#include "FractalFactory.h"

std::unique_ptr<IFractal> FractalFactory::CreateFractal(FractalType type, CLab2View* pView)
{
    switch (type) {
    case Koch: return std::make_unique<KochFractal>(pView);
    case Mandelbrot: return std::make_unique<MandelbrotFractal>(pView);
    default: return std::unique_ptr<IFractal>(nullptr);
    }
}
