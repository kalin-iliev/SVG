#include "Attribute.h"

bool Attribute::isLetterInt(char c) {
	return (c >= '0' && c <= '9');
}

bool Attribute::isStringInt(const String& currentStr) {
	int size = currentStr.size();
	int start = 0;
	int dashIndex = currentStr.has('-');
	if (dashIndex > -1 &&  dashIndex != 0)
		return false;
	if (dashIndex > -1) start++;
	for (int i = start; i < size; i++)
	{
		if (!isLetterInt(currentStr[i]))
			return false;
	}

	return true;
}

bool Attribute::isAttributeLetter(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

String Attribute::getAttrValue(const String& attribute) {
	char* attrValue = nullptr;
	int lenValue = 0;
	int length = 0;
	if (attribute.has('"') == -1)
		return attrValue;
	if (attribute.countSymbol('"') != 2)
		return attrValue;
	while (attribute[length]) {
		while (attribute[length] && (isAttributeLetter(attribute[length]) || attribute[length] == '-'))
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
	if (attribute.has('=') == -1)
		return attrName;

	while (attribute[length]) {
		while (attribute[length] && (isAttributeLetter(attribute[length]) || attribute[length] == '-') && attribute[length] != '=')
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
			if (isAttributeLetter(attribute[i]) || attribute[i] == '-')
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
	isInt = false;
}

Attribute::Attribute(const String& attrName, const String& attrValue, bool valueIsInt) {
	if (valueIsInt && !isStringInt(attrValue))
	{
		name = value = String();
		isInt = isValid = false;
	}
	else {
		name = attrName;
		value = attrValue;
		if (!name.size() || !value.size())
		{
			name = value = String();
			isInt = isValid = false;
		}
		else {
			isValid = true;
			isInt = valueIsInt;
		}
	}
}

Attribute::Attribute(const String& attribute, bool valueIsInt) {
	if (!attribute.size())
	{
		name = value = "";
		isValid = true;
		isInt = false;
	}
	else {
		name = String(getAttrName(attribute));
		value = String(getAttrValue(attribute));
		if (!name.size() || !value.size())
		{
			name = value = String();
			isValid = false;
			isInt = false;
		}
		else
		{
			if (valueIsInt && !isStringInt(value))
			{
				name = value = String();
				isValid = false;
			}
			else
			{
				isValid = true;
				isInt = true;
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
	if (isInt && !isStringInt(newValue))
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