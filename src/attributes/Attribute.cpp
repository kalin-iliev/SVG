#include "Attribute.h"

bool Attribute::isInt(char c) {
	return (c >= '0' && c <= '9');
}

bool Attribute::isInt(const String& currentString) {
	int size = currentString.size();
	int start = 0;
	int dashIndex = currentString.firstIndexOf('-');
	if (dashIndex > -1 &&  dashIndex != 0)
		return false;
	if (dashIndex > -1) start++;
	for (int i = start; i < size; i++)
	{
		if (!isInt(currentString[i]))
			return false;
	}

	return true;
}

bool Attribute::isLetter(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

String Attribute::getAttrValue(const String& attribute) {
	char* attrValue = nullptr;
	int lenValue = 0;
	int length = 0;
	if (!attribute.contains('"'))
		return attrValue;
	if (attribute.numberOfOccurrences('"') != 2)
		return attrValue;
	while (attribute[length]) {
		while (attribute[length] && (isLetter(attribute[length]) || attribute[length] == '-'))
			++length;
		if (attribute[length])
		{
			if (attribute[length] == '=')
			{
				++length;
			}
			if (attribute[length] == '"')
			{
				++length;
				int start = length;
				while (attribute[length] && attribute[length] != '"')
				{
					if (attribute[length] != ' ' && attribute[length] != '\n' && attribute[length] != '\t')
						++lenValue;
					++length;
				}
				if (attribute[length] != '"')
					return attrValue;

				attrValue = new char[lenValue + 1];
				int currentIndex = 0;
				for (int i = start; i < length; i++)
				{
					if (attribute[i] != ' ' && attribute[i] != '\n' && attribute[i] != '\t') {
						if (currentIndex < lenValue)
							attrValue[currentIndex++] = attribute[i];
					}
				}
				attrValue[currentIndex] = 0;

				++length;
			}
		}
	}

	String newString(attrValue);
	delete[] attrValue;

	return newString;
}

String Attribute::getAttrName(const String& attribute) {
	char* attrName = nullptr;
	int lenValue = 0;
	int length = 0;
	if (!attribute.contains('='))
		return attrName;

	while (attribute[length]) {
		while (attribute[length] && (isLetter(attribute[length]) || attribute[length] == '-') && attribute[length] != '=')
		{
			++lenValue;
			++length;
		}

		if (attribute[length] && attribute[length] != '=')
			++length;
		else
			break;

	}

	if (lenValue > 0)
	{
		attrName = new char[lenValue + 1];
		int currentIndex = 0;
		for (int i = 0; i < length; i++)
		{
			if (isLetter(attribute[i]) || attribute[i] == '-')
			{
				if (currentIndex < lenValue)
					attrName[currentIndex++] = attribute[i];
			}
		}
		attrName[currentIndex] = 0;
	}

	String newString(attrName);
	delete[] attrName;

	return newString;
}

Attribute::Attribute() {
	name = value = "";
	isValid = false;
	isValueInt = false;
}

Attribute::Attribute(const String& attrName, const String& attrValue, bool valueIsInt) {
	if (valueIsInt && !isInt(attrValue))
	{
		name = value = String();
		isValueInt = isValid = false;
	}
	else {
		name = attrName;
		value = attrValue;
		if (!name.size() || !value.size())
		{
			name = value = String();
			isValueInt = isValid = false;
		}
		else {
			isValid = true;
			isValueInt = valueIsInt;
		}
	}
}

Attribute::Attribute(const String& attribute, bool valueIsInt)
{
	if (!attribute.size())
	{
		name = value = "";
		isValid = true;
		isValueInt = false;
	}
	else {
		name = String(getAttrName(attribute));
		value = String(getAttrValue(attribute));
		if (!name.size() || !value.size())
		{
			name = value = String();
			isValid = false;
			isValueInt = false;
		}
		else
		{
			if (valueIsInt && !isInt(value))
			{
				name = value = String();
				isValid = false;
			}
			else
			{
				isValid = true;
				isValueInt = true;
			}
		}
	}
}

Attribute::Attribute(const Attribute& attribute) {
	if (this != &attribute)
	{
		name = attribute.name;
		value = attribute.value;
		isValid = attribute.isValid;
	}
}

Attribute& Attribute::operator=(const Attribute& attribute) {
	if (this != &attribute)
	{
		name = attribute.name;
		value = attribute.value;
		isValid = attribute.isValid;
	}
	return *this;
}

Attribute& Attribute::operator=(const String& attrValue) {
	if (!(value == attrValue))
		value = attrValue;
	return *this;
}

void Attribute::setValue(const String& newValue) {
	if (isValueInt && !isInt(newValue))
		return;
	value = newValue;
}

std::ostream& operator << (std::ostream& out, const Attribute& currentAttr) {
	out << (currentAttr.name + '=' + '"' + currentAttr.value + '"');
	return out;
}

std::istream& operator >> (std::istream& in, Attribute& currentAttr) {
	String currentName;
	String currentValue;
	in >> currentName >> currentValue;
	String attr = (currentName + '=' + '"' + currentValue + '"');
	currentAttr = attr;
	return in;
}

String Attribute::toString() const
{
	if (name.size() > 0 && value.size() > 0)
	{
		return getName() + "=\"" + getValue() + "\"";
	}
	else
	{
		return "";
	}
}

bool Attribute::operator==(const Attribute& other) const
{
	return this->name == other.name && this->value == other.value;
}

bool Attribute::operator!=(const Attribute& other) const 
{
	return !(*this == other);
}
