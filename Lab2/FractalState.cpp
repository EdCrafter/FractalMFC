#include "pch.h"
#include "FractalState.h"

FractalState* FractalState::instance = nullptr;

FractalState* FractalState::GetInstance()
{
	if (instance == nullptr) {
		instance = new FractalState();
	}
	return instance;
}