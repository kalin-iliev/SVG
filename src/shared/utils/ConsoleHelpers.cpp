#include "ConsoleHelpers.h"

void ConsoleHelpers::listHelpFunctions()
{
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << "open <file>   opens file" << std::endl;
	std::cout << "close         closes currently opened file" << std::endl;
	std::cout << "save          saves the currently opened file" << std::endl;
	std::cout << "saveas <file> saves the currently opened file in <file>" << std::endl;
	std::cout << "help          prints this information" << std::endl;
	std::cout << "exit          exits the program" << std::endl;
}

String ConsoleHelpers::initCommand(const Command& command, SVGShapesManager& shapesManager)
{
	if (command.getName() == "open")
	{
		if (command.size() != 1)
		{
			throw String("Invalid arguments.");
		}

		handleInput.loadFile(shapesManager, command.getParameter(0));
		std::cout << "Successfully read file." << std::endl;
	}
	else if (command.getName() == "close")
	{
		if (!handleInput.isFileOpen())
		{
			throw String("Currently there is no file open.");
		}

		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments");
		}

		if (handleInput.hasShapes(shapesManager))
		{
			shapesManager.removeShapes();
		}
		handleInput.closeFile();
		std::cout << "Successfully close the file." << std::endl;
	}
	else if (command.getName() == "save")
	{
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments");
		}

		if (handleInput.hasShapes(shapesManager))
		{
			handleInput.saveFile(shapesManager);
		}
		std::cout << "Successfully saved current shapes." << std::endl;
	}
	else if (command.getName() == "saveas")
	{
		if (command.size() != 1)
		{
			throw String("Invalid arguments.");
		}

		handleInput.saveFileAs(shapesManager, command.getParameter(0));
		std::cout << "Successfully saved current shapes into file: " << command.getParameter(0) << std::endl;
	}
	else if (command.getName() == "help")
	{
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments.");
		}
		listHelpFunctions();
		std::cout << std::endl;

		shapesManager.printCommands();
		std::cout << std::endl;
	}
	else if (command.getName() == "shapes")
	{
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments");
		}

		shapesManager.printAllowedShapes();
	}
	else if (command.getName() == "attributes")
	{
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments");
		}

		shapesManager.printAllowedAttributes();
	}
	else if (command.getName() == "print")
	{
		if (!handleInput.isFileOpen())
		{
			throw String("Currently there is no open file.");
		}
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments");
		}
		shapesManager.printShapes();
	}
	else if (command.getName() == "create")
	{
		if (!handleInput.isFileOpen())
		{
			throw String("Currently there is no open file.");
		}

		handleInput.createShape(shapesManager, command.getParameters());
	}
	else if (command.getName() == "within")
	{
		if (!handleInput.isFileOpen())
		{
			throw String("Currently there is no open file.");
		}

		handleInput.isWithin(shapesManager, command.getParameters());
	}
	else if (command.getName() == "erase")
	{
		if (!handleInput.isFileOpen())
		{
			throw String("Currently there is no open file.");
		}
		if (command.size() != 1)
		{
			throw String("This command accepts only one argument.");
		}

		handleInput.eraseShape(shapesManager, command.getParameter(0));
	}
	else if (command.getName() == "translate")
	{
		handleInput.translate(shapesManager, command.getParameters());
	}
	else if (command.getName() == "exit")
	{
		if (command.size() > 0)
		{
			throw String("This command doesn't need arguments.");
		}
	}
	else
	{
		throw String("Unsupported command.");
	}
	return command.getName();
}

String ConsoleHelpers::readCommand(SVGShapesManager& shapesManager)
{
	Command newCommand;
	std::cin >> newCommand;
	return initCommand(newCommand, shapesManager);
}