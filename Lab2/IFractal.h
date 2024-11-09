#pragma once
// Strategy pattern
#include <vector>
#include <memory>

#include "FractalState.h"

class CLab2View;
class CDoc;

class IFractal {
protected:
    CLab2View* pView;
	FractalState* state = FractalState::GetInstance();
public:
    IFractal() = default;
    explicit IFractal(CLab2View* pView) : pView(pView) {}

    IFractal(const IFractal&);
    IFractal& operator=(const IFractal&) = delete;
    IFractal(IFractal&&) noexcept = delete;
    IFractal& operator=(IFractal&&) noexcept = delete;
    virtual int GetType() const = 0;
	virtual std::unique_ptr<IFractal> Clone() const = 0; // prototype pattern
    virtual void Draw(CDC* pDC) = 0;
    virtual ~IFractal() = default;
    virtual void Reset() = 0;
};

class KochFractal : public IFractal {
public:
    KochFractal() = default;
    KochFractal(const KochFractal&);
    explicit KochFractal(CLab2View* pView);
    int GetType() const override;
	std::unique_ptr<IFractal> Clone() const override;
    void Draw(CDC* pDC) override;
    void DrawKochSnowflake(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points);
    void DrawSnowflakeAndFill(CDC* pDC, CPoint vertex1, CPoint vertex2, CPoint vertex3, int depth);
    bool IsVisible(CDC* pDC,CPoint p);
    void DrawKochSnowflakeIterative(CDC* pDC, CPoint start, CPoint end, int depth, std::vector<CPoint>& points);
	void Reset() override;
};

class MandelbrotFractal : public IFractal {

public:
    MandelbrotFractal() = default;
    explicit MandelbrotFractal(CLab2View* pView);
	std::unique_ptr<IFractal> Clone() const override;
    void Draw(CDC* pDC) override;
    int GetType() const override;
	void Reset() override;
};
