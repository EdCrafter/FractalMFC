#pragma once
// Factory pattern
#include <memory>
#include "IFractal.h"

class FractalFactory {
public:
    enum FractalType {
        Koch,
        Mandelbrot
    };

    static std::unique_ptr<IFractal> CreateFractal(FractalType type) {
        switch (type) {
        case Koch: return std::make_unique<KochFractal>();
        case Mandelbrot: return std::make_unique<MandelbrotFractal>();
        default: return nullptr;
        }
    }
};

