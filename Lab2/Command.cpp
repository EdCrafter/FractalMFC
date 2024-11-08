#include "pch.h"
#include "Command.h"
#include "FractalFacade.h"

// Implementation of ZoomInCommand
int ZoomCommand::countFMove = 0;

ZoomCommand::ZoomCommand(FractalFacade& facade, double dx, double dy, double scale = 1) : IFractalCommand(facade), deltaX(dx), deltaY(dy), scale(scale) {}
void ZoomCommand::Execute() {
    if (facade.ZoomIn(scale)) {
	    facade.Move(deltaX, deltaY, scale);
    }
    else {
	    facade.Move(deltaX, deltaY, 1);
        countFMove++;
    }
}

void ZoomCommand::Undo() {
	if (countFMove > 0) {
	    facade.MoveOut(deltaX, deltaY, 1);
        countFMove--;
	}
	else {
		facade.ZoomOut(scale);
		facade.MoveOut(deltaX, deltaY, scale);
	}
}


// Implementation of MoveCommand constructor and methods
MoveCommand::MoveCommand(FractalFacade& facade, double dx, double dy, double scale = 1) : IFractalCommand(facade), deltaX(dx), deltaY(dy), scale(scale) {}

void MoveCommand::Execute() {
	facade.Move(deltaX, deltaY, scale);
}

void MoveCommand::Undo() {
    FractalState* state = FractalState::GetInstance();
    state->centerWX -= deltaX;
    state->centerWY -= deltaY;
}

// Implementation of CommandManager constructor and methods
CommandManager::CommandManager(int maxSize) : maxStackSize(maxSize) {}

void CommandManager::ExecuteCommand(std::unique_ptr<IFractalCommand> command) {
    // Remove commands that are ahead of the current index to support proper Redo
    if (currentCommandIndex < static_cast<int>(commandsHistory.size()) - 1) {
        commandsHistory.erase(commandsHistory.begin() + currentCommandIndex + 1, commandsHistory.end());
    }

    // Execute the command
    command->Execute();

    // Add to history
    commandsHistory.push_back(std::move(command));
    if (commandsHistory.size() > maxStackSize) {
        commandsHistory.pop_front();
    }
    else {
        currentCommandIndex++;
    }
}

void CommandManager::Undo() {
    if (currentCommandIndex >= 0) {
        commandsHistory[currentCommandIndex]->Undo();
        currentCommandIndex--;
    }
}

void CommandManager::Redo() {
    if (currentCommandIndex < static_cast<int>(commandsHistory.size()) - 1) {
        currentCommandIndex++;
        commandsHistory[currentCommandIndex]->Execute();
    }
}

SetFractalTypeCommand::SetFractalTypeCommand(FractalFacade& facade, FractalFactory::FractalType type) : IFractalCommand(facade)
{
	this->type = type;
}

void SetFractalTypeCommand::Execute()
{
	facade.SetFractalType(type);
}

void SetFractalTypeCommand::Undo()
{
	facade.SetFractalType(FractalFactory::FractalType::Invalid);
}
