#include "String.h"

void String::setData(const char* newValue)
{
	if (!newValue)
	{
		setData("");
	}

	this->length = strlen(newValue);
	this->data = new char[this->length + 1];
	strcpy(this->data, newValue);
}

void String::copy(const String& secondString)
{
	setData(secondString.data);
}

bool String::isCharLetter(char c) const
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool String::isCharUpper(char c) const
{
	return isCharLetter(c) && (c >= 'A' && c <= 'Z');
}

bool String::isCharLower(char c) const
{
	return isCharLetter(c) && (c >= 'a' && c <= 'z');
}

String::String(unsigned size)
{
	if(!size)
	{
		setData("");
	}

	else
	{
		this->data = new char[size + 1];
		this->data[size] = '\0';
		this->length = size;
	}
}

String::String(const char* newStr)
{
	setData(newStr);
}

String::String(const String& secondString)
{
	if (this != &secondString)
	{
		copy(secondString);
	}
}

String& String::operator=(const String& secondString)
{
	if (this != &secondString)
	{
		delete[] data;
		copy(secondString);
	}

	return *this;
}

String::~String()
{
	delete[] data;
}

String operator+(const String& firstString, const String& secondString)
{
	String resultString(firstString);
	resultString += secondString;
	return resultString;
}

String operator+(const char* firstString, const String& secondString)
{
	String resultString(firstString);
	resultString += secondString;
	return resultString;
}

String operator+(const String& firstString, const char* secondString)
{
	String resultString(firstString);
	resultString += secondString;
	return resultString;
}

String operator+(const char symbol, const String& secondString)
{
	String resultString;
	resultString += symbol;
	resultString += secondString;
	return resultString;
}

String operator+(const String& firstString, const char symbol)
{
	String resultString;
	resultString += firstString;
	resultString += symbol;

	return resultString;
}

String& String::operator+=(const String& secondString)
{
	return *this += secondString.data;
}

String& String::operator+=(const char* secondString)
{
	int newLength = strlen(secondString) + this->length + 1;
	char* newData = new (std::nothrow) char[newLength];
	if (!newData)
	{
		return *this;
	}

	strncpy(newData, this->data, this->length);
	strncpy(newData + this->length, secondString, strlen(secondString));
	newData[newLength - 1] = '\0';
	delete[] this->data;
	this->data = newData;
	this->length = newLength - 1;

	return *this;

}

String& String::operator+=(const char symbol)
{
	char* newData = new (std::nothrow) char[this->length + 2];
	if (!newData)
	{
		return *this;
	}

	strncpy(newData, this->data, this->length);
	newData[this->length] = symbol;
	newData[this->length + 1] = '\0';

	delete[] this->data;
	this->data = newData;
	this->length++;

	return *this;
}

bool operator==(const String& firstString, const String& secondString)
{
	bool areDirrefent = strcmp(firstString.data, secondString.data);
	return !areDirrefent;
}

bool operator==(const char* firstString, const String& secondString)
{
	return String(firstString) == secondString;
}

bool operator==(const String& firstString, const char* secondString)
{
	return firstString == String(secondString);
}

bool operator==(const char symbol, const String& secondString)
{
	return secondString != symbol;
}

bool operator==(const String& firstString, const char symbol)
{
	if (firstString.length != 1)
	{
		return false;
	}

	return firstString.data[0] == symbol;
}

char String::operator[](unsigned index) const
{
	if (!(index >= 0 && index <= length))
	{	
		throw std::out_of_range("The index is out of bounds!");
	}

	return data[index];
}

char& String::operator[](unsigned index)
{
	if (!(index >= 0 && index <= length))
	{
		throw std::out_of_range("The index is out of bounds!");
	}
	return data[index];
}

std::ostream& operator << (std::ostream& out, const String& currentString)
{
	out << currentString.data;
	return out;
}

std::istream& operator >> (std::istream& in, String& currentString)
{
	char buffer[MAX_READ_SIZE];
	in.getline(buffer, MAX_READ_SIZE);
	currentString = buffer;
	return in;
}

int String::toInt() const
{
	return atoi(data);
}

float String::toFloat() const
{
	return atof(data);
}

bool String::beginsWith(char c) const
{
	return data[0] == c;
}

bool String::beginsWith(const String& other) const 
{
	if (this->length < other.length)
	{
		return false;
	}

	for (int i = 0; i < this->length && i < other.length; ++i)
	{
		if (this->data[i] != other.data[i])
		{
			return false;
		}
	}

	return true;
}

bool String::contains(char c) const
{
	return this->firstIndexOf(c) != -1;
}

bool String::contains(const String& other) const
{
	return this->firstIndexOf(other) != -1;
}

int String::firstIndexOf(char c) const
{
	for (int i = 0; i < this->length; ++i)
	{
		if (this->data[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int String::firstIndexOf(const String& subStr) const
{
	for (int i = 0; i < this->length - subStr.length + 1; ++i)
	{
		bool found = true;
		for (int j = 0; j < subStr.length && this->data[i+j]; ++j)
		{
			if (this->data[i + j] != subStr.data[j])
			{
				found = false;
				break;
			}	
		}
		if (found)
		{
			return i;
		}
	}

	return -1;
}

int String::lastIndexOf(char c) const
{
	for (int i = this->length - 1; i >= 0; i--)
	{
		if (data[i] == c)
			return i;
	}

	return -1;
}

int String::lastIndexOf(const String& subStr) const
{
	for (int i = this->length - subStr.length; i >= 0 ; --i)
	{
		bool found = true;
		for (int j = subStr.length - 1; j >= 0 && this->data[i+j]; --j)
		{
			if (this->data[i + j] != subStr.data[j])
			{
				found = false;
				break;
			}	
		}
		if (found)
		{
			return i;
		}
	}

	return -1;
}

unsigned String::numberOfOccurrences(char c) const
{
	int count = 0;
	const char* str = data;
	while (*str)
	{
		if (*str == c)
		{
			count++;
		}

		str++;
	}

	return count;
}

unsigned String::numberOfOccurrences(const String& subStr) const
{
	int count = 0;
	String originalString(*this);
	int subIndex = originalString.firstIndexOf(subStr);
	while (subIndex != -1)
	{
		++count;
		originalString.data += (subIndex + subStr.length);
		subIndex = originalString.firstIndexOf(subStr);
	}

	return count;
}

String String::toLowerCase() const
{
	char* result = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		if (isCharUpper(data[i]))
		{
			// TODO create util
			result[i] = data[i] - 'A' + 'a';
		}
		else
		{
			result[i] = data[i];
		}
	}
	result[length] = '\0';
	String lowerString(result);
	delete[] result;
	return lowerString;
}

String String::toUpperCase() const {
	char* result = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		if (isCharLower(data[i]))
		{
			// TODO create util
			result[i] = data[i] - 'a' + 'A';
		}
		else
		{
			result[i] = data[i];
		}
	}
	result[length] = '\0';
	String upperString(result);
	delete[] result;
	return upperString;
}

unsigned String::size() const
{
	return length;
}

const char* String::toCharArray() const
{
	return data;
}

String::operator bool() const
{
	return length > 0;
}