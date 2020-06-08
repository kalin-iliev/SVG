#include "StringHelpers.h"
#include <iostream>
#include <cstring>

void StringHelpers::copyString(char*& dest, const char* source) {
	int sourceLen = strlen(source);
	dest = new char[sourceLen + 1];
	strncpy(dest, source, sourceLen);
	dest[sourceLen] = 0;
}

char* StringHelpers::prependArray(char* dest, const char* source) {
	int prependSize = strlen(source);
	int newSize = strlen(dest) + prependSize + 1;
	char* newStr = new (std::nothrow) char[newSize];
	if (!newStr)
		return dest;
	strncpy(newStr, source, prependSize);
	strncpy(newStr + prependSize, dest, strlen(dest));
	newStr[newSize - 1] = 0;
	delete[] dest;
	dest = newStr;
	return newStr;
}

char* StringHelpers::prependSymbol(char* dest, const char symbol) {
	int newSize = strlen(dest) + 2;
	char* newStr = new (std::nothrow) char[newSize];
	if (!newStr)
		return dest;
	newStr[0] = symbol;
	strncpy(newStr + 1, dest, strlen(dest));
	newStr[newSize - 1] = 0;
	delete[] dest;
	dest = newStr;
	return newStr;
}

char* StringHelpers::appendArray(char* dest, const char* source) {
	int appendSize = strlen(source);
	int newSize = strlen(dest) + appendSize + 1;
	char* newDest = new (std::nothrow) char[newSize];
	if (!newDest)
		return dest;
	strncpy(newDest, dest, strlen(dest));
	strncpy(newDest + strlen(dest), source, appendSize);
	newDest[newSize - 1] = 0;
	delete[] dest;
	dest = newDest;
	return newDest;
}

char* StringHelpers::appendSymbol(char* dest, const char symbol, int appendSize) {
	if (appendSize < 1)
		return dest;
	int sizeDest = strlen(dest);
	int newSize = strlen(dest) + appendSize + 1;
	char* newDest = new (std::nothrow) char[newSize];
	if (!newDest)
		return dest;
	strncpy(newDest, dest, sizeDest);
	for (int i = sizeDest; i < newSize - 1; i++)
		newDest[i] = symbol;
	newDest[newSize - 1] = 0;
	delete[] dest;
	dest = newDest;
	return newDest;
}

bool StringHelpers::subSymbol(const char* text, char symbol)
{
	while (*text)
	{
		if (*text == symbol)
			return true;
		++text;
	}
	return false;
}

bool StringHelpers::subStr(const char* text, const char* subText) {
	size_t subLen = strlen(subText);
	size_t pos;
	const char* textLen = text + strlen(text);

	while (text + subLen <= textLen) {
		for (pos = 0; pos < subLen; ++pos) {
			if (text[pos] != subText[pos]) {
				break;
			}
		}
		if (!subText[pos]) return true;
		++text;
	}
	return false;
}

int StringHelpers::subSymbolIndex(const char* text, char symbol)
{
	const char* start = text;
	while (*text)
	{
		if (*text == symbol)
			return text - start;
		++text;
	}
	return -1;
}

int StringHelpers::subStrIndex(const char* text, const char* subText) {
	size_t subLen = strlen(subText);
	size_t pos;
	const char* textLen = text + strlen(text);
	const char* start = text;
	while (text + subLen <= textLen) {
		for (pos = 0; pos < subLen; ++pos) {
			if (text[pos] != subText[pos]) {
				break;
			}
		}
		if (!subText[pos]) return text - start;
		++text;
	}
	return -1;
}

bool StringHelpers::strBegin(const char* currentStr, const char* comparingString) {
	if (strlen(currentStr) < strlen(comparingString))
		return false;
	while (*comparingString && *currentStr) {
		if (*comparingString != *currentStr)
			return false;
		++comparingString;
		++currentStr;
	}
	return true;
}
