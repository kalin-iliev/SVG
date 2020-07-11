#include "String.h"

void String::setStr(const char* newStr) {
	if (!newStr)
	{
		setStr("");
	}
	length = strlen(newStr);
	stringData = new char[length + 1];
	strcpy(stringData, newStr);
}

void String::copy(const String& secondStr) {
	setStr(secondStr.stringData);
}

bool String::isCharLetter(char c) const {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool String::isCharUpper(char c) const {
	return isCharLetter(c) && (c >= 'A' && c <= 'Z');
}

bool String::isCharLower(char c) const {
	return isCharLetter(c) && (c >= 'a' && c <= 'z');
}

String::String(unsigned size) {
	if(!size)
		setStr("");
	else if(size > 0)
	{
		stringData = new char[size + 1];
		stringData[size] = 0;
		length = size;
	}
}

String::String(const char* newStr) {
	setStr(newStr);
}

String::String(const String& secondStr) {
	if (this != &secondStr)
		copy(secondStr);
}

String& String::operator=(const String& secondStr) {
	if (this != &secondStr)
	{
		delete[] stringData;
		copy(secondStr);
	}
	return *this;
}

String::~String() {
	delete[] stringData;
}

String operator+(const String& firstStr, const String& secondStr) {
	char* newText = new char[firstStr.size() + 1];
	strcpy(newText, firstStr.stringData);
	newText = StringHelpers::appendArray(newText, secondStr.stringData);
	String newString(newText);
	delete[] newText;
	return newString;
}

String operator+(const char* firstStr, const String& currentStr) {
	String arrayToString = String(firstStr);
	return operator+(arrayToString, currentStr);
}

String operator+(const String& currentStr, const char* secondStr) {
	String arrayToString = String(secondStr);
	return operator+(currentStr, arrayToString);
}

String operator+(const char symbol, const String& currentStr) {
	char* newStr = new char[strlen(currentStr.stringData) + 1];
	strcpy(newStr, currentStr.stringData);
	newStr = StringHelpers::prependSymbol(newStr, symbol);
	String newString(newStr);
	delete[] newStr;
	return newString;
}

String operator+(const String& currentStr, const char symbol)
{
	String newString = currentStr;
	return newString += symbol;
}

String& String::operator+=(const String& secondStr) {
	stringData = StringHelpers::appendArray(stringData, secondStr.stringData);
	length += secondStr.size();
	return *this;
}

String& String::operator+=(const char* secondStr) {
	return *this += String(secondStr);
}

String& String::operator+=(const char symbol) {
	stringData = StringHelpers::appendSymbol(stringData, symbol);
	length++;
	return *this;
}

bool operator==(const String& firstStr, const String& secondStr) {
	bool compared = strcmp(firstStr.stringData, secondStr.stringData);
	return !compared;
}

bool operator==(const char* firstStr, const String& currentStr) {
	return String(firstStr) == currentStr;
}

bool operator==(const String& currentStr, const char* secondStr) {
	return currentStr == String(secondStr);
}

bool operator==(const char symbol, const String& currentStr) {
	if (currentStr.length != 1)
		return false;
	return currentStr.stringData[0] == symbol;
}

bool operator==(const String& currentStr, const char symbol) {
	if (currentStr.length != 1)
		return false;
	return currentStr.stringData[0] == symbol;
}


char String::operator[](unsigned index) const {
	if (!(index >= 0 && index <= length))
	{
		throw std::out_of_range("The index is out of bounds!");
	}
	return stringData[index];
}

char& String::operator[](unsigned index) {
	if (!(index >= 0 && index <= length))
	{
		throw std::out_of_range("The index is out of bounds!");
	}
	return stringData[index];
}

std::ostream& operator << (std::ostream& out, const String& currentStr) {
	out << currentStr.stringData;
	return out;
}

std::istream& operator >> (std::istream& in, String& currentStr) {
	char buffer[MAX_READ_SIZE];
	in.getline(buffer, MAX_READ_SIZE);
	currentStr = buffer;
	return in;
}

int String::strToInt() const {
	return atoi(stringData);
}

float String::strToFloat() const {
	return atof(stringData);
}

bool String::beginWith(char c) const {
	return stringData[0] == c;
}

bool String::beginWith(const String& other) const {
	return StringHelpers::strBegin(stringData, other.stringData);
}

int String::has(char c) const {
	return StringHelpers::subSymbolIndex(stringData, c);
}

int String::has(const String& other) const {
	return StringHelpers::subStrIndex(stringData, other.stringData);
}

int String::firstIndexOf(char c) const {
	return has(c);
}

int String::firstIndexOf(const String& subText) const {
	return has(subText);
}

int String::lastIndexOf(char c) const {
	for (int i = length - 1; i >= 0; i--)
	{
		if (stringData[i] == c)
			return i;
	}

	return -1;
}

int String::lastIndexOf(const String& subStr) const {
	int lastIndex = -1;
	const char* str = stringData;
	int subIndex = StringHelpers::subStrIndex(str, subStr.stringData);
	while (subIndex > -1)
	{
		str += (subIndex + strlen(subStr.stringData));
		subIndex = StringHelpers::subStrIndex(str, subStr.stringData);
		lastIndex = subIndex;
	}
	return lastIndex;
}

unsigned String::countSymbol(char c) const {
	int count = 0;
	const char* str = stringData;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}

	return count;
}

unsigned String::countSubstr(const String& subStr) const {
	int count = 0;
	const char* str = stringData;
	int subIndex = StringHelpers::subStrIndex(str, subStr.stringData);
	while (subIndex > -1)
	{
		str += (subIndex + strlen(subStr.stringData));
		subIndex = StringHelpers::subStrIndex(str, subStr.stringData);
		++count;
	}
	return count;
}

String String::toLowerCase() const {
	char* result = new char[length + 1];
	for (int i = 0; i < length; i++)
		result[i] = (isCharUpper(stringData[i])) ? stringData[i] ^ 32 : stringData[i];
	result[length] = 0;
	String newString(result);
	delete[] result;
	return newString;
}

String String::toUpperCase() const {
	char* result = new char[length + 1];
	for (int i = 0; i < length; i++)
		result[i] = (isCharLower(stringData[i])) ? stringData[i] ^ 32 : stringData[i];
	result[length] = 0;
	String newString(result);
	delete[] result;
	return newString;
}