#pragma once
// Decorator pattern
#include "IFractal.h"

#include <memory>

enum class DecoratorType {
	Color = -100,
	Blur
};

class ColorDecorator : public IFractal {
private:
    std::unique_ptr<IFractal> fractal;
    COLORREF color;

public:
	ColorDecorator(std::unique_ptr<IFractal> fractal, COLORREF color = RGB(130, 150, 155))
		: color(color)
    {
        if (fractal != nullptr && fractal->GetType() == (int)DecoratorType::Color) {
            this->fractal = std::move(static_cast<ColorDecorator*>(fractal.get())->fractal);
        }
        else {
            this->fractal = std::move(fractal);
        }
    }

    int GetType() const override {
        return -100;
    }

    /*std::unique_ptr<IFractal> Clone() const override {
		CString str;
		str.Format(_T("Clone ColorDecorator , color=%d"), color);

		AfxMessageBox(str);
        return std::make_unique<ColorDecorator>(fractal->Clone(), color);
    }*/

    void Draw(CDC* pDC) override {
		fractal->SetColor(color);
        fractal->Draw(pDC);
    }
    void Reset() override {
        fractal->Reset();
    }
};

class BlurDecorator : public IFractal {
private:
    std::unique_ptr<IFractal> fractal;

public:
    BlurDecorator(std::unique_ptr<IFractal> fractal)
        : fractal(std::move(fractal)) {}

    int GetType() const override {
        return -99;
    }

    /*std::unique_ptr<IFractal> Clone() const override {
        return std::make_unique<BlurDecorator>(fractal->Clone());
    }*/

    void Draw(CDC* pDC) override { 
        pDC->SetGraphicsMode(GM_ADVANCED);
        fractal->Draw(pDC); 
    }
    void Reset() override {
        fractal->Reset();
    }
};