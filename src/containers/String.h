#pragma once // TODO remove pragma once's
#include <iostream>
#include <string.h>

const int MAX_READ_SIZE = 1024;

class String
{
public:
	String(unsigned size = 0);
	String(const char* data);
	String(const String& secondString);
	String& operator=(const String& secondString);
	~String();

	friend bool operator==(const String& firstString, const String& secondString);
	friend bool operator==(const char* firstString, const String& currentString);
	friend bool operator==(const String& currentString, const char* secondString);
	friend bool operator==(const char symbol, const String& currentString);
	friend bool operator==(const String& currentString, const char symbol);
	
	String& operator +=(const String& other);
	String& operator +=(const char* other);
	String& operator +=(const char symbol);

	friend String operator+(const String& firstString, const String& secondString);
	friend String operator+(const char* firstString, const String& secondString);
	friend String operator+(const String& firstString, const char* secondString);
	friend String operator+(const char symbol, const String& currentString);
	friend String operator+(const String& firstString, const char symbol);
	
	char operator[](unsigned index) const;
	char& operator[](unsigned index);

	unsigned size() const;

	friend std::ostream& operator << (std::ostream& outputStream, const String& currentString);
	friend std::istream& operator >> (std::istream& inputStream, String& currentString);

	int toInt() const;
	bool beginsWith(char) const;
	bool beginsWith(const String&) const;
	bool contains(char c) const;
	bool contains(const String&) const;
	int firstIndexOf(char c) const;
	int firstIndexOf(const String&) const;
	int lastIndexOf(char c) const;
	int lastIndexOf(const String&) const;
	unsigned numberOfOccurrences(char c) const;
	unsigned numberOfOccurrences(const String&) const;
	String toLowerCase() const;
	String toUpperCase() const;
	const char* toCharArray() const;

	operator bool() const;

private:
	char* data;
	unsigned length;

	void setData(const char* newValue);
	void copy(const String& secondString);
};
