#pragma once

#include <deque>
#include <memory>
#include "FractalFacade.h"

class FractalFacade;

class IFractalCommand {
protected:
	FractalFacade facade;
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
public:
	ZoomCommand(FractalFacade& facade, double dx, double dy, double scale);
    void Execute() override;
    void Undo() override;
};


// MoveCommand - for moving
class MoveCommand : public IFractalCommand {
private:
    double deltaX, deltaY, scale;

public:
    MoveCommand(FractalFacade& facade,double dx, double dy,double scale);
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

class CommandManager {
    int maxStackSize;
    std::deque<std::unique_ptr<IFractalCommand>> commandsHistory;
    int currentCommandIndex = -1;

public:
    CommandManager() = default;
    CommandManager(int maxStackSize);
    void ExecuteCommand(std::unique_ptr<IFractalCommand> command);
    void Undo(); 
    void Redo();
};
