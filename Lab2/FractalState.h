#pragma once
// Singleton pattern
class FractalState {
    static FractalState* instance;
public:
    double centerX, centerY, zoomFactor;

    static FractalState* GetInstance() {
		if (instance == nullptr) {
			instance = new FractalState();
		}
        return instance;
    }

private:
    FractalState() : centerX(0), centerY(0), zoomFactor(1.0) {}
    FractalState(const FractalState&) = delete;
    FractalState& operator=(const FractalState&) = delete;
};
