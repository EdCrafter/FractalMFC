#include "pch.h"
#include "FractalFacade.h"
#include "Lab2View.h"

// Метод для установки типа фрактала
FractalFacade::FractalFacade(const FractalFacade& other) {
	this->pView = other.pView;
	if (other.facadeFractal) {
		this->facadeFractal = other.facadeFractal->Clone();
	}
	else {
		this->facadeFractal = nullptr;
	}
}

FractalFacade::FractalFacade(CLab2View* pView) {
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
void FractalFacade::ZoomIn(double scale) {
    FractalState::GetInstance()->zoomFactor *= scale;
}

// Метод для уменьшения масштаба
void FractalFacade::ZoomOut(double scale) {
    FractalState::GetInstance()->zoomFactor /= scale;
}

// Метод для перемещения
void FractalFacade::Move(double dx, double dy,double scale=1) {
    FractalState* state = FractalState::GetInstance();
    FractalFactory::FractalType type = this->GetType();
	if (type==0) {
        CRect clientRect;
        pView->GetClientRect(&clientRect);
        state->centerX = (-dx + state->centerX) * scale + clientRect.Width() / 2;
        state->centerY = (-dy + state->centerY) * scale + clientRect.Height() / 2;
		return;
	}
	else if (type==1) {
		state->centerX += dx;
		state->centerY += dy;
		return;
	}
    
    
}

// Метод для отрисовки
void FractalFacade::Draw(CDC* pDC) {
    if (facadeFractal) {
        facadeFractal->Draw(pDC);
    }
}
