#include "pch.h"
#include "FractalFacade.h"
#include "Lab2View.h"
#include "ColoredFractalDecorator.h"

FractalFacade::FractalFacade(const FractalFacade& other) {
	this->color = other.color;
	this->pView = other.pView;
	/*if (other.facadeFractal) {
		this->facadeFractal = std::move(other.facadeFractal->Clone());
	}
	else {
		this->facadeFractal = nullptr;
	}*/
}

FractalFacade::FractalFacade(CLab2View* pView) {
	this->color = RGB(0, 0, 0);
	this->pView = pView;
    facadeFractal = nullptr;
}

void FractalFacade::SetFractalType(FractalFactory::FractalType type) {
    facadeFractal = FractalFactory::CreateFractal(type, pView); 
}

FractalFactory::FractalType FractalFacade::GetType(){
	
	if (!facadeFractal) {
		return FractalFactory::FractalType::Invalid;
	}

    int type = facadeFractal->GetType();

    if (type == 0) {
        return FractalFactory::FractalType::Koch;
    }
    else if (type == 1) {
        return FractalFactory::FractalType::Mandelbrot;
    }
   
    return FractalFactory::FractalType::Invalid; // Обработка неизвестного типа
}



// Метод для увеличения масштаба
bool FractalFacade::ZoomIn(double scale) {
	if (scale < 1) {
		if (FractalState::GetInstance()->depth <= FractalState::GetInstance()->minDepth) {
			return false;
		}
		FractalState::GetInstance()->depth--;
	}
	if (FractalState::GetInstance()->depth && FractalState::GetInstance()->depth < FractalState::GetInstance()->maxDepth) {
		FractalState::GetInstance()->zoomFactor *= scale;
		if (scale > 1) {
			FractalState::GetInstance()->depth++;
		}
		return true;
	}
	return false;
}

void FractalFacade::SetColor(COLORREF color)
{
	this->color = color;
}

// Метод для уменьшения масштаба
bool FractalFacade::ZoomOut(double scale) {
	if (FractalState::GetInstance()->depth > FractalState::GetInstance()->minDepth) {
		FractalState::GetInstance()->zoomFactor /= scale;
		FractalState::GetInstance()->depth--;
	}
	return false;
}

// Метод для перемещения
void FractalFacade::Move(double dx, double dy,double scale=1,bool centered=false) {
    FractalState* state = FractalState::GetInstance();
    FractalFactory::FractalType type = this->GetType();
	CRect clientRect;
	pView->GetWindowDC()->GetClipBox(&clientRect);
	if (type==0) {
		if (centered) {
			dx = clientRect.Width() / 2;
			dy = clientRect.Height() / 2;
		}
		state->centerWX = (-dx + state->centerWX) * scale + clientRect.Width() / 2;
		state->centerWY = (-dy + state->centerWY) * scale + clientRect.Height() / 2;
		return;
	}
	else if (type==1) {
		if (centered) {
			dx = clientRect.Width() / 2;
			dy = clientRect.Height() / 2;
		}
		state->centerWX = (dx - clientRect.Width() / 2 + state->centerWX ) * scale;
		state->centerWY = ( - dy + clientRect.Height() / 2 + state->centerWY)* scale;
		return;
	}
    
    
}


void FractalFacade::Draw(CDC* pDC) {
    if (facadeFractal) {
        facadeFractal->Draw(pDC);
    }
	else {
		CFont font;
		font.CreatePointFont(400, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);
		CString text = L"FRACTALS";
		CSize textSize = pDC->GetTextExtent(text);
		CRect clientRect;
		GetClientRect(pDC->GetWindow()->GetSafeHwnd(),&clientRect);
		int x = (clientRect.Width() - textSize.cx) / 2;
		int y = (clientRect.Height() - textSize.cy) / 2;
		pDC->TextOutW(x, y, text);
		pDC->SelectObject(pOldFont);
	}
}

void FractalFacade::Reset()
{
	facadeFractal->Reset();
}

void FractalFacade::SetFractalDecorator(FractalFacade::DecoratorType decoratorType)
{
	if (decoratorType == DecoratorType::None) {
		return;
	}
	else if (decoratorType == DecoratorType::Color) {
		facadeFractal = std::make_unique<ColorDecorator>(std::move(facadeFractal), color);
	}
	else if (decoratorType == DecoratorType::Blur) {
		facadeFractal = std::make_unique<BlurDecorator>(std::move(facadeFractal));
	}
	//facadeFractal->Draw(pView->GetDC());
}

void FractalFacade::MoveOut(double dx, double dy, double scale,bool centered = false)
{
	FractalState* state = FractalState::GetInstance();
	FractalFactory::FractalType type = this->GetType();

	CRect clientRect;
	pView->GetWindowDC()->GetClipBox(&clientRect);
	CRect rect;
	pView->GetClientRect(&rect);
	if (type == 0) {
		if (centered) {
			dx = clientRect.Width() / 2 ;
			dy = clientRect.Height() / 2;
		}
		state->centerWX = (state->centerWX - clientRect.Width() / 2)/scale+dx;
		state->centerWY = (state->centerWY - clientRect.Height() / 2) / scale + dy;
		return;
	}
	else if (type == 1) {
		if (centered) {
			dx = clientRect.Width() / 2;
			dy = clientRect.Height() / 2;
			scale = 1 / scale;
		}
		state->centerWX = state->centerWX / scale - dx + clientRect.Width() / 2;
		state->centerWY = state->centerWY / scale + dy - clientRect.Height() / 2;
		return;
	}
}

