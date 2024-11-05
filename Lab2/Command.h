#pragma once

#include <deque>
#include <memory>

class IFractalCommand {
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual ~IFractalCommand() = default;
};

// ZoomInCommand - for zooming in
class ZoomInCommand : public IFractalCommand {
public:
    void Execute() override;
    void Undo() override;
};

// ZoomOutCommand - for zooming out
class ZoomOutCommand : public IFractalCommand {
public:
    void Execute() override;
    void Undo() override;
};

// MoveCommand - for moving
class MoveCommand : public IFractalCommand {
private:
    double deltaX, deltaY;

public:
    MoveCommand(double dx, double dy);
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
