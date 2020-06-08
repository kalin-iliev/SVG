#pragma once
#include "String.h"
#include "Vector.h"
class Command
{
private:
	String name;
	Vector<String> parameters;
private:
	bool isCommandLetter(char c);
	int countCommand(const String& commandText);
	int extractCommand(const String& commandText, Vector<String>& words);
public:
	Command(const String& text = "");
	Command(const Command& other);
	Command& operator=(const Command& other);
	bool isEmpty() const { return (!name && !parameters.size()); }

	String getName() const { return name; }
	Vector<String> getParameters() const { return parameters; }
	String getParameter(unsigned index) const;
	String operator[](unsigned index) const;
	unsigned size() const { return parameters.size(); }
	friend std::ostream& operator << (std::ostream& out, const Command& currentCommand);
	friend std::istream& operator >> (std::istream& in, Command& currentCommand);
};
