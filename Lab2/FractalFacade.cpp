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
	//AfxMessageBox(L"ZoomIn");
	if (FractalState::GetInstance()->depth && FractalState::GetInstance()->depth < FractalState::GetInstance()->maxDepth) {
		FractalState::GetInstance()->zoomFactor *= scale;
		FractalState::GetInstance()->depth++;
	}
}

// Метод для уменьшения масштаба
void FractalFacade::ZoomOut(double scale) {
	if (FractalState::GetInstance()->depth >= 2) {
		FractalState::GetInstance()->zoomFactor *= 1 / scale;
		FractalState::GetInstance()->depth--;
	}
}

// Метод для перемещения
void FractalFacade::Move(double dx, double dy,double scale=1) {
    FractalState* state = FractalState::GetInstance();
    FractalFactory::FractalType type = this->GetType();
	if (type==0) {
        CRect clientRect;
		pView->GetWindowDC()->GetClipBox(&clientRect);
        
		if (FractalState::GetInstance()->depth >= FractalState::GetInstance()->maxDepth) {
			state->centerWX = -dx + state->centerWX + clientRect.Width() / 2;
			state->centerWY = -dy + state->centerWY + clientRect.Height() / 2;
		}
		else {
			state->centerWX = (-dx + state->centerWX) * scale + clientRect.Width() / 2;
			state->centerWY = (-dy + state->centerWY) * scale + clientRect.Height() / 2;
		}
		return;
	}
	else if (type==1) {
		CString str;
		str.Format(L"dx=%f, dy=%f , scale=%f , cX=%f, cY=%f", dx, dy, scale, state->centerWX, state->centerWY);
		AfxMessageBox(str);
		state->centerWX = -dx;// +state->centerWX;
		state->centerWY = -dy;// +state->centerWY;
		return;
	}
    
    
}

// Метод для отрисовки
void FractalFacade::Draw(CDC* pDC) {
    if (facadeFractal) {
        facadeFractal->Draw(pDC);
    }
}
