#pragma once
#include "String.h"
#include "Vector.h"
class Command
{
private:
	String name;
	Vector<String> parameters;
private:
	bool isSymbolValid(char c);
	int extractCommand(const String& commandText, Vector<String>& words);
public:
	Command(const String& text = "");
	Command(const Command& other);
	Command& operator=(const Command& other);
	bool isEmpty() const;

	String getName() const;
	Vector<String> getParameters() const;
	String getParameterByIndex(unsigned index) const;
	String operator[](unsigned index) const;
	unsigned size() const;
	friend std::ostream& operator << (std::ostream& out, const Command& currentCommand);
	friend std::istream& operator >> (std::istream& in, Command& currentCommand);
};
