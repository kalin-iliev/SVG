#pragma once
class StringHelpers
{
public:
	StringHelpers() = delete;
	static void copyString(char*& dest, const char* source);
	static char* prependArray(char* dest, const char* source);
	static char* prependSymbol(char* dest, const char symbol);
	static char* appendArray(char* dest, const char* source);
	static char* appendSymbol(char* dest, const char symbol, int howMany = 1);
	static bool subSymbol(const char* text, char symbol);
	static int subSymbolIndex(const char* text, char symbol);
	static bool subStr(const char* text, const char* subText);
	static int subStrIndex(const char* text, const char* subText);
	static bool strBegin(const char*, const char*);
};

