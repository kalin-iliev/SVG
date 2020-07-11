#include "Command.h"

bool Command::isCommandLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
		(c == '\\') || (c == '/') ||
		(c == '.') || (c == ':') ||
		(c >= '0' && c <= '9') ||
		(c == '_') || (c == '-');
}

int Command::countCommand(const String& text) {
	int cnt = 0;
	bool isEqualFound = false;
	bool isWordFoundAfterEqual = false;
	int foundWordAfterEqualSize = 0;
	int length = 0;
	while (text[length]) {
		while (text[length] && !isCommandLetter(text[length]) && text[length] != '=') {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length] && text[length] != '=') {
			if(!isEqualFound)
				++cnt;                              // if there is a word, count it
		}
		while (text[length] && (isCommandLetter(text[length]) && text[length] != '=')) {           // skip to the end of the word
			if(isEqualFound)
				foundWordAfterEqualSize++;
			if (isWordFoundAfterEqual)
				isWordFoundAfterEqual = false;
			++length;
		}
		if (isEqualFound)
		{
			if (!foundWordAfterEqualSize)
				return -1;
			foundWordAfterEqualSize = 0;
			isWordFoundAfterEqual = true;
			isEqualFound = false;
		}
		while (text[length] && !isCommandLetter(text[length]))
		{
			if (text[length] == '=')
			{
				if (isWordFoundAfterEqual)
					return -1;

				if (!isWordFoundAfterEqual && isEqualFound)
					return -1;

				isEqualFound = true;
				isWordFoundAfterEqual = false;
				++length;
			}
			else {
				++length;
			}
		}
	}
	if (isEqualFound) {
		return -1;
	}
	return cnt;
}

int Command::extractCommand(const String& text, Vector<String>& words) {
	int countCommandWords = countCommand(text);
	if (countCommandWords == -1)
		throw String("Sorry, the text you typed is invalid.");
	bool isEqualFound = false;
	bool isWordFoundAfterEqual = false;
	int length = 0;
	for (int i = 0; i < countCommandWords; i++)
	{
		while (text[length] && !isCommandLetter(text[length]) && text[length] != '=') {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length] && text[length] != '=') {
			int start = length;
			int attrSize = 0;
			int currentSize = 0;


			while (text[length] && (isCommandLetter(text[length]) && text[length] != '=')) {           // skip to the end of the word
				++attrSize;
				++length;
			}
			if (isEqualFound)
			{
				isEqualFound = false;
			}
			while (text[length] && !isCommandLetter(text[length]))
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

			while (text[length] && isCommandLetter(text[length]) && isEqualFound)
			{
				++attrSize;
				++length;
			}

			isEqualFound = false;

			String newString(attrSize);
			for (int i = start; i < length; i++)
			{
				if (isCommandLetter(text[i]) || text[i] == '=')
					newString[currentSize++] = text[i];
			}

			words.push_back(newString);
		}
	}
	return countCommandWords;
}

Command::Command(const String& commandText) {
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

Command::Command(const Command& other) {
	if (this != &other)
	{
		name = other.name;
		parameters = other.parameters;
	}
}

Command& Command::operator=(const Command& other) {
	if (this != &other)
	{
		name = other.name;
		parameters = other.parameters;
	}

	return *this;
}

String Command::getParameter(unsigned index) const {
	int size = parameters.size();
	if (!(index >= 0 && index < size))
		throw String("The index is out of bounds.");
	return parameters[index];
}

String Command::operator[](unsigned index) const {
	return getParameter(index);
}

std::ostream& operator << (std::ostream& out, const Command& currentCommand) {
	out << "Number of parameters: " << currentCommand.size() << std::endl;
	out << "Name: " << currentCommand.getName() << ", Parameters: ";
	int parameterSize = currentCommand.size();
	for (int i = 0; i < parameterSize; i++)
	{
		out << currentCommand[i];
		if (i != parameterSize - 1)
			out << ' ';
	}
	out << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Command& currentCommand) {
	String readString;
	in >> readString;
	currentCommand = Command(readString);
	return in;
}