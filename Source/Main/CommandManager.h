#pragma once

#include "JuceHeader.h"

struct Command
{
    virtual ~Command() = default;
};

namespace Commands
{
struct NewProject : Command
{

};

struct LoadProject : Command
{
    LoadProject(const File& fileToUse) : file(fileToUse) {}

    File file;
};

}


class CommandTarget
{
public:
    virtual ~CommandTarget() = default;

    virtual void performCommand(Command* command) = 0;
};

class CommandManager
{
public:
    void setTarget(CommandTarget* targetToUse) { target = targetToUse; }
    void invokeCommand(Command* command)
    {
        std::unique_ptr<Command> commandToUse;
        commandToUse.reset(command);
        target->performCommand(commandToUse.get());
    }

private:
    CommandTarget* target = nullptr;

};

CommandManager& getCommandManager();
void invokeCommand(Command* command);