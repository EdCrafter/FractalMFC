#pragma once
// Singleton pattern
class FractalState {
    static FractalState* instance;
public:
    double centerWX, centerWY, zoomFactor;
    int depth, maxDepth;

    static FractalState* GetInstance();
    
private:
	FractalState() : centerWX(0), centerWY(0), zoomFactor(1), depth(1), maxDepth(-1) {}
    FractalState(const FractalState&) = delete;
    FractalState& operator=(const FractalState&) = delete;
};
