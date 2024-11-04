#pragma once
// Strategy pattern
#include "Lab2View.h"

#include <vector>

class IFractal {
protected:
    CLab2View* pView;
public:

	IFractal() = default;
	IFractal(CLab2View* pView) : pView(pView) {}
	IFractal(const IFractal&& other) noexcept : pView(other.pView) {}
	IFractal& operator=(const IFractal&& other) noexcept {
        if (this != &other) {
			pView = other.pView;
        }
    }
    virtual void Draw(CDC* pDC) = 0;
    virtual ~IFractal() = default;

};

class KochFractal : public IFractal {
public:
    void Draw(CDC* pDC) override;
    void DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points);
    void DrawSnowflakeAndFill(CDC* pDC, CPoint vertex1, CPoint vertex2, CPoint vertex3, int depth);
};

class MandelbrotFractal : public IFractal {
public:
    void Draw(CDC* pDC) override;
};
