#pragma once
// Strategy pattern

#include <vector>

// Предварительное объявление CLab2View
class CLab2View;

class IFractal {
protected:
    CLab2View* pView;
public:
    IFractal() = default;
    explicit IFractal(CLab2View* pView) : pView(pView) {}

    // Удаляем копирование и перемещение
    IFractal(const IFractal&) = delete;
    IFractal& operator=(const IFractal&) = delete;
    IFractal(IFractal&&) noexcept = delete;
    IFractal& operator=(IFractal&&) noexcept = delete;

    virtual void Draw(CDC* pDC) = 0;
    virtual ~IFractal() = default;
};

class KochFractal : public IFractal {
public:
    KochFractal() = default;
    explicit KochFractal(CLab2View* pView) : IFractal(pView) {}
    void Draw(CDC* pDC) override;
    void DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points);
    void DrawSnowflakeAndFill(CDC* pDC, CPoint vertex1, CPoint vertex2, CPoint vertex3, int depth);
};

class MandelbrotFractal : public IFractal {
public:
    MandelbrotFractal() = default;
    explicit MandelbrotFractal(CLab2View* pView) : IFractal(pView) {}
    void Draw(CDC* pDC) override;
};
