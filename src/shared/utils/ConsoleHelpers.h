#pragma once
#include "InputHandler.h"
#include "SVGShapesManager.h"
#include "InputHandler.h"
#include "Command.h"

class ConsoleHelpers
{
	InputHandler handleInput;
public:
	void listHelpFunctions();
	String readCommand(SVGShapesManager&);
	String initCommand(const Command& command, SVGShapesManager&);
};

