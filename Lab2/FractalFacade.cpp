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
bool FractalFacade::ZoomIn(double scale) {
	if (FractalState::GetInstance()->depth && FractalState::GetInstance()->depth < FractalState::GetInstance()->maxDepth) {
		FractalState::GetInstance()->zoomFactor *= scale;
		FractalState::GetInstance()->depth++;
		return true;
	}
	return false;
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
void FractalFacade::Move(double dx, double dy,double scale=1) {
    FractalState* state = FractalState::GetInstance();
    FractalFactory::FractalType type = this->GetType();
	if (type==0) {
        CRect clientRect;
		pView->GetWindowDC()->GetClipBox(&clientRect);	
		state->centerWX = (-dx + state->centerWX) * scale + clientRect.Width() / 2;
		state->centerWY = (-dy + state->centerWY) * scale + clientRect.Height() / 2;
		return;
	}
	else if (type==1) {
		CRect clientRect;
		pView->GetWindowDC()->GetClipBox(&clientRect);
		state->centerWX = (dx - clientRect.Width() / 2 + state->centerWX ) * scale;
		state->centerWY = ( - dy + clientRect.Height() / 2 + state->centerWY)* scale;
		return;
	}
    
    
}


// Метод для отрисовки
void FractalFacade::Draw(CDC* pDC) {
    if (facadeFractal) {
        facadeFractal->Draw(pDC);
    }
}

void FractalFacade::MoveOut(double dx, double dy, double scale)
{
	FractalState* state = FractalState::GetInstance();
	FractalFactory::FractalType type = this->GetType();
	if (type == 0) {
		CRect clientRect;
		pView->GetWindowDC()->GetClipBox(&clientRect);
		state->centerWX = (state->centerWX - clientRect.Width() / 2)/scale+dx;
		state->centerWY = (state->centerWY - clientRect.Height() / 2) / scale + dy;
		return;
	}
	else if (type == 1) {
		CRect clientRect;
		pView->GetWindowDC()->GetClipBox(&clientRect);
		state->centerWX = state->centerWX / scale - dx + clientRect.Width() / 2;
		state->centerWY = state->centerWY / scale + dy - clientRect.Height() / 2;
		return;
	}
}
