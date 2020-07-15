#include "SVGAppWrapper.h"
void SVGAppWrapper::start()
{
	bool appStarted = true;
	ConsoleHelpers consoleHelp;
	SVGShapesManager newManager;
	std::cout << "Welcome to SVG reader/writer application." << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "If you want to get started, just type help for list of functions and how to work with them." << std::endl;

	while (appStarted) {
		try {
			String commandName = consoleHelp.readCommand(newManager);
			if (commandName == "exit")
			{
				std::cout << "Exiting program..." << std::endl;
				appStarted = false;
			}
		}
		catch (const String& error) {
			std::cout << error << std::endl;
		}
	}
}