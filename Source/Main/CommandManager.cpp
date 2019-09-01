#include "CommandManager.h"

CommandManager commandManager;

CommandManager& getCommandManager()
{
    return commandManager;
}

void invokeCommand(Command* command)
{
    getCommandManager().invokeCommand(command);
}
