#pragma once

#include <deque>
#include <memory>
#include "FractalFacade.h"

class FractalFacade;

class IFractalCommand {
protected:
	FractalFacade& facade;
public:
	IFractalCommand(FractalFacade& facade) : facade(facade) {}
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual ~IFractalCommand() = default;
};

// ZoomInCommand - for zooming in
class ZoomCommand : public IFractalCommand {
	double deltaX, deltaY, scale;
    static int countFMove;
	bool centered;
public:
	ZoomCommand(FractalFacade& facade, double dx, double dy, double scale, bool centered=0);
    void Execute() override;
    void Undo() override;
};


// MoveCommand - for moving
class MoveCommand : public IFractalCommand {
private:
    double deltaX, deltaY, scale;
	bool centered;
public:
    MoveCommand(FractalFacade& facade,double dx, double dy,double scale,bool centered);
    void Execute() override;
    void Undo() override;
};

class SetFractalTypeCommand : public IFractalCommand {
	FractalFactory::FractalType type;
public:
	SetFractalTypeCommand(FractalFacade& facade,FractalFactory::FractalType type);
	void Execute() override;
	void Undo() override;
};

class SetDecoratorCommand : public IFractalCommand {
	FractalFacade::DecoratorType decoratorType;
	COLORREF color;
public:
	SetDecoratorCommand(FractalFacade& facade, FractalFacade::DecoratorType decoratorType, COLORREF color);
	void Execute() override;
	void Undo() override;

};

class CommandManager {
    int maxStackSize;
    std::deque<std::unique_ptr<IFractalCommand>> commandsHistory;
    int currentCommandIndex;

public:
	CommandManager(int maxStackSize=20);
    void ExecuteCommand(std::unique_ptr<IFractalCommand> command);
    void Undo(); 
    void Redo();
	void Clear();
};
