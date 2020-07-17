#ifndef CONSOLE_HELPERS_HEADER_INCLUDED
#define CONSOLE_HELPERS_HEADER_INCLUDED

#include "InputHandler.h"
#include "SVGShapesManager.h"
#include "InputHandler.h"
#include "Command.h"

class ConsoleHelpers
{
public:
	void listHelpFunctions();
	String readCommand(SVGShapesManager&);
	String initCommand(const Command& command, SVGShapesManager&);

private:
    InputHandler handleInput;
};

#endif
