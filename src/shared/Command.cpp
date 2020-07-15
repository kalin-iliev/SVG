#include "Command.h"

bool Command::isSymbolValid(char c)
{
	// TODO refactor - use isLetter, isNumber from utils
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
		   (c == '\\') || (c == '/') ||
		(c == '.') || (c == ':') ||
		(c >= '0' && c <= '9') ||
		(c == '_') || (c == '-');
}

int Command::extractCommand(const String& text, Vector<String>& words)
{
	int countCommandWords = 0;
	bool isEqualFound = false;
	bool isWordFoundAfterEqual = false;
	int length = 0;
	while (text[length])
	{
		while (text[length] && !isSymbolValid(text[length]))
		{  // skip letters to the beginning of a word
			++length;
		}
		if (text[length] && text[length] != '=' && !isEqualFound)
		{
			++countCommandWords; // if there is a word, count it
		}

		if (text[length] && text[length] != '=')
		{
			int start = length;
			int attrSize = 0;
			int currentSize = 0;

			while (text[length] && isSymbolValid(text[length]))
			{  // skip to the end of the word
				++attrSize;
				++length;
			}
			if (isEqualFound)
			{
				isEqualFound = false;
			}
			while (text[length] && !isSymbolValid(text[length]))
			{
				if (text[length] == '=')
				{
					isEqualFound = true;
					++attrSize;
					++length;
				}
				else {
					++length;
				}
			}

			while (text[length] && isSymbolValid(text[length]) && isEqualFound)
			{
				++attrSize;
				++length;
			}

			isEqualFound = false;

			String newString(attrSize);
			for (int i = start; i < length; i++)
			{
				if (isSymbolValid(text[i]) || text[i] == '=')
				{
					newString[currentSize++] = text[i];
				}
			}

			words.push_back(newString);
		}
	}
	return countCommandWords;
}

Command::Command(const String& commandText)
{
	if(commandText)
	{
		Vector<String> commandWords;
		int words = extractCommand(commandText, commandWords);
		if (words > 0)
		{
			name = commandWords[0];
			if (commandWords.size() > 0)
			{
				commandWords.remove(0);
				parameters = commandWords;
			}
		}
	}
}

Command::Command(const Command& other)
{
	if (this != &other)
	{
		name = other.name;
		parameters = other.parameters;
	}
}

Command& Command::operator=(const Command& other)
{
	if (this != &other)
	{
		name = other.name;
		parameters = other.parameters;
	}

	return *this;
}

String Command::getParameterByIndex(unsigned index) const
{
	int size = parameters.size();
	if (!(index >= 0 && index < size))
	{
		throw String("The index is out of bounds.");
	}
	return parameters[index];
}

String Command::operator[](unsigned index) const
{
	return getParameterByIndex(index);
}

std::ostream& operator << (std::ostream& out, const Command& currentCommand)
{
	out << "Number of parameters: " << currentCommand.size() << std::endl;
	out << "Name: " << currentCommand.getName() << ", Parameters: ";
	int parameterSize = currentCommand.size();
	for (int i = 0; i < parameterSize; i++)
	{
		out << currentCommand[i];
		if (i != parameterSize - 1)
		{
			out << ' ';
		}
	}
	out << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Command& currentCommand)
{
	String readString;
	in >> readString;
	currentCommand = Command(readString);
	return in;
}

bool Command::isEmpty() const
{
	return !name && !parameters.size();
}

String Command::getName() const
{
	return name;
}

Vector<String> Command::getParameters() const
{
	return parameters;
}

unsigned Command::size() const
{
	return parameters.size();
}