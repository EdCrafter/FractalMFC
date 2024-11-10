#pragma once
// Decorator pattern
#include "IFractal.h"

#include <memory>
//
//class ColorDecorator : public IFractal {
//private:
//    std::unique_ptr<IFractal> fractal;
//    COLORREF color;
//
//public:
//	ColorDecorator(std::unique_ptr<IFractal> fractal, COLORREF color = RGB(130, 150, 155))
//        :  color(color) {
//		this->fractal = std::move(fractal);
//    }
//
//    int GetType() const override {
//        return fractal->GetType();
//    }
//
//    std::unique_ptr<IFractal> Clone() const override {
//        return std::make_unique<ColorDecorator>(fractal->Clone(), color);
//    }
//
//    void Draw(CDC* pDC) override {
//		CString str;
//		str.Format(_T("Color2=%d"), color);
//		AfxMessageBox(str);
//		fractal->SetColor(color);
//        fractal->Draw(pDC);
//    }
//    void Reset() override {
//        fractal->Reset();
//    }
//};

class BlurDecorator : public IFractal {
private:
    std::unique_ptr<IFractal> fractal;

public:
    BlurDecorator(std::unique_ptr<IFractal> fractal)
        : fractal(std::move(fractal)) {}

    int GetType() const override {
        return fractal->GetType();
    }

    std::unique_ptr<IFractal> Clone() const override {
        return std::make_unique<BlurDecorator>(fractal->Clone());
    }

    void Draw(CDC* pDC) override { 
        pDC->SetGraphicsMode(GM_ADVANCED);
        fractal->Draw(pDC); 
    }
    void Reset() override {
        fractal->Reset();
    }
};