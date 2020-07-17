#ifndef COMMAND_HEADER_INCLUDED
#define COMMAND_HEADER_INCLUDED

#include "String.h"
#include "Vector.h"
class Command
{
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

private:
	String name;
	Vector<String> parameters;

	bool isSymbolValid(char c);
	int extractCommand(const String& commandText, Vector<String>& words);
};

#endif