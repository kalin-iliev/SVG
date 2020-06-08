#pragma once
#include <iostream>
#include "StringHelpers.h"

const int MAX_READ_SIZE = 1024;

class String
{

private:
	char* stringData;
	unsigned length;
private:
	void setStr(const char* newStr);
	void copy(const String& secondStr);
	bool isCharLetter(char c) const;
	bool isCharUpper(char c) const;
	bool isCharLower(char c) const;
public:
	String(unsigned size = 0);
	String(const char* data);
	String(const String& secondStr);
	String& operator=(const String& secondStr);
	~String();

	friend bool operator==(const String& firstStr, const String& secondStr);
	friend bool operator==(const char* firstStr, const String& currentStr);
	friend bool operator==(const String& currentStr, const char* secondStr);
	friend bool operator==(const char symbol, const String& currentStr);
	friend bool operator==(const String& currentStr, const char symbol);
	
	String& operator +=(const String& secondStr);
	String& operator +=(const char* secondStr);
	String& operator +=(const char symbol);

	friend String operator+(const String& firstStr, const String& secondStr);
	friend String operator+(const char* firstStr, const String& currentStr);
	friend String operator+(const String& currentStr, const char* secondStr);
	friend String operator+(const char symbol, const String& currentStr);
	friend String operator+(const String& currentStr, const char symbol);
	
	char operator[](unsigned index) const;
	char& operator[](unsigned index);

	unsigned size() const { return length; }

	friend std::ostream& operator << (std::ostream& outputstream, const String& currentStr);
	friend std::istream& operator >> (std::istream& inputstream, String& currentStr);

	int strToInt() const;
	float strToFloat() const;
	bool beginWith(char) const;
	bool beginWith(const String&) const;
	int has(char) const;
	int has(const String&) const;
	int firstIndexOf(char c) const;
	int firstIndexOf(const String&) const;
	int lastIndexOf(char c) const;
	int lastIndexOf(const String&) const;
	unsigned countSymbol(char c) const;
	unsigned countSubstr(const String&) const;
	String toLowerCase() const;
	String toUpperCase() const;
	const char* toCharArray() const { return stringData; }

	operator bool() const { return length > 0; }
};

