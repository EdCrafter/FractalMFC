#include "pch.h"
#include "Command.h"
#include "FractalState.h"

// Implementation of ZoomInCommand
void ZoomInCommand::Execute() {
    FractalState::GetInstance()->zoomFactor *= 1.4;
}

void ZoomInCommand::Undo() {
    FractalState::GetInstance()->zoomFactor /= 1.4;
}

// Implementation of ZoomOutCommand
void ZoomOutCommand::Execute() {
    FractalState::GetInstance()->zoomFactor /= 1.4;
}

void ZoomOutCommand::Undo() {
    FractalState::GetInstance()->zoomFactor *= 1.4;
}

// Implementation of MoveCommand constructor and methods
MoveCommand::MoveCommand(double dx, double dy) : deltaX(dx), deltaY(dy) {}

void MoveCommand::Execute() {
    FractalState* state = FractalState::GetInstance();
    state->centerX += deltaX;
    state->centerY += deltaY;
}

void MoveCommand::Undo() {
    FractalState* state = FractalState::GetInstance();
    state->centerX -= deltaX;
    state->centerY -= deltaY;
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
