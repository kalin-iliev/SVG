#include "CommonAttributes.h"

int CommonAttributes::findAttribute(const String& attributeName, const Vector<String>& extractedAttributes) {
	int size = extractedAttributes.size();
	for (int i = 0; i < size; i++)
	{
		if (extractedAttributes[i].beginWith(attributeName) && extractedAttributes[i].has('=') == attributeName.size())
			return i;
	}
	return -1;
}

int CommonAttributes::findAttributeName(const String& attributeName, const Vector<String>& attributeNames) {
	int size = attributeNames.size();
	for (int i = 0; i < size; i++)
	{
		if (attributeNames[i] == attributeName)
			return i;
	}

	return -1;
}

void CommonAttributes::pushInAllowedAttributes(const AttributeInfo elements[], int size) {
	for (int i = 0; i < size; i++)
	{
		if(elements[i].intValid())
			allowedIntAttributes.push_back(elements[i].getName());
		allowedAttributes.push_back(elements[i].getName());
	}
}

bool CommonAttributes::isAttributeLetter(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

void CommonAttributes::setCurrentAttributes(const String& text) {
	try {
		Vector<String> attributes;
		extractAttributes(text, attributes);
		int allowedAttrSize = allowedAttributes.size();

		for (int i = 0; i < allowedAttrSize; i++)
		{
			int indexCommonAttrInArray = findAttribute(allowedAttributes[i], attributes);
			if (indexCommonAttrInArray > -1)
			{
				bool valueIsInt = false;
				if (findAttributeName(allowedAttributes[i], allowedIntAttributes) > -1)
					valueIsInt = true;
				String attr = attributes[indexCommonAttrInArray];
				Attribute newAttr(attr, valueIsInt);
				if (!newAttr)
					throw String("One of the common attributes is invalid.");
				currentAttributes.push_back(newAttr);
			}
		}
	}
	catch (const String& error) {
		throw error;
	}
	
}

int CommonAttributes::attributesCount(const String& text) {
	int cnt = 0;
	int length = 0;
	while (text[length]) {
		while (text[length] && !isAttributeLetter(text[length])) {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length]) {
			++cnt;                              // if there is a word, count it
		}
		while (text[length] && (isAttributeLetter(text[length]) || text[length] == '-')) {           // skip to the end of the word
			++length;
		}
		while (text[length] && !isAttributeLetter(text[length]))
		{
			if (text[length] == '-')
			{
				++length;
				while (text[length] && text[length] != '=')
				{
					++length;
				}
				++length;
			}
			if (text[length] == '=')
			{
				++length;
				while (text[length] && text[length] != '"')
					++length;
			}
			else if (text[length] == '"')
			{
				++length;
				while (text[length] && text[length] != '"')
				{
					++length;
				}
				++length;
			}
			else {
				++length;
			}
		}
	}
	return cnt;
}

int CommonAttributes::extractAttributes(const String& text, Vector<String>& attributes) {
	int countAttr = attributesCount(text);
	int length = 0;
	for (int i = 0; i < countAttr; i++)
	{
		while (text[length] && !isAttributeLetter(text[length])) {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length]) {                            // if there is a word, count it
			int start = length;
			int attrSize = 0;
			int currentSize = 0;
			while (text[length] && (isAttributeLetter(text[length]) || text[length] == '-')) {         // skip to the end of the word
				++attrSize;
				++length;
			}

			while (text[length] && !isAttributeLetter(text[length]))
			{
				if (text[length] == '-')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '=')
					{
						++attrSize;
						++length;
					}
					++length;
				}
				if (text[length] == '=')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '"')
						++length;
				}
				else if (text[length] == '"')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '"')
					{

						if (text[length] != ' ' && text[length] != '\n' && text[length] != '\t')
							++attrSize;
						++length;
					}
					++attrSize;
					++length;
				}
				else {
					++length;
				}
			}

			char* attr = new char[attrSize + 1];
			bool hasAssignmentChar = false;
			for (int p = start; p < length && currentSize < attrSize; p++) {
				if ((isAttributeLetter(text[p]) || (text[p] != ' ' && text[p] != '\n' && text[p] != '\t')) && currentSize < attrSize + 1)
				{
					if (hasAssignmentChar) {
						if (text[p] != '"')
							continue;
						hasAssignmentChar = false;
					}
					if (text[p] == '=')
						hasAssignmentChar = true;

					attr[currentSize++] = text[p];
				}
			}

			attr[attrSize] = '\0';
			String newString(attr);
			attributes.push_back(newString);
			delete[] attr;
		}
	}

	return countAttr;
}

CommonAttributes::CommonAttributes(const String& text) {
	try {
		pushInAllowedAttributes(commonAttributes, commonAttrSize);
		setCurrentAttributes(text);
	}
	catch (const String& error) {
		throw error;
	}
}

CommonAttributes::CommonAttributes(const CommonAttributes& other) {
	if (this != &other)
	{
		allowedAttributes = other.allowedAttributes;
		allowedIntAttributes = other.allowedIntAttributes;
		currentAttributes = other.currentAttributes;
	}
}

CommonAttributes& CommonAttributes::operator=(const CommonAttributes& other) {
	if (this != &other) {
		allowedAttributes = other.allowedAttributes;
		allowedIntAttributes = other.allowedIntAttributes;
		currentAttributes = other.currentAttributes;
	}
	return *this;
}

void CommonAttributes::printAllowedAttributes() const {
	int size = allowedAttributes.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << allowedAttributes[i];
		if (i != size - 1)
			std::cout << ", ";
	};
}

Vector<String> CommonAttributes::getAllowedAttributes() const { return allowedAttributes; }

void CommonAttributes::printAllowedIntAttributes() const {
	int size = allowedAttributes.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << allowedIntAttributes[i];
		if (i != size - 1)
			std::cout << ", ";
	};
}

Vector<String> CommonAttributes::getAllowedIntAttributes() const { return allowedIntAttributes; }

void CommonAttributes::printCurrentAttributes() const {
	int size = currentAttributes.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << currentAttributes[i].getValue();
		if (i != size - 1)
			std::cout << ' ';
	};
}

Vector<Attribute> CommonAttributes::getCurrentAttributes() const { return currentAttributes; }

int CommonAttributes::findAllowedAttribute(const String& attr) const {
	int size = allowedAttributes.size();
	for (int i = 0; i < size; i++)
		if (allowedAttributes[i] == attr)
			return i;
	return -1;
}

int CommonAttributes::findAllowedIntAttribute(const String& attr) const {
	int size = allowedIntAttributes.size();
	for (int i = 0; i < size; i++)
		if (allowedIntAttributes[i] == attr)
			return i;
	return -1;
}

int CommonAttributes::findCurrentAttribute(const String& attr) const {
	int size = currentAttributes.size();
	for (int i = 0; i < size; i++)
		if (currentAttributes[i].getName() == attr)
			return i;
	return -1;
}

Attribute CommonAttributes::getAttribute(unsigned index) const {
	if (index >= currentAttributes.size())
		throw String("The index is out of the range of the attributes.");
	return currentAttributes[index];
}

Attribute CommonAttributes::operator[](unsigned index) const {
	if (index >= currentAttributes.size())
		throw String("The index is out of the range of the attributes.");
	return currentAttributes[index];
}

void CommonAttributes::setAttrValue(const String& currentAttr, const String& newValue) {
	int currentAttributeIndex = findCurrentAttribute(currentAttr);
	if (currentAttributeIndex > -1)
		currentAttributes[findCurrentAttribute(currentAttr)].setValue(newValue);
	else
		std::cout << "Couldn't find the attribute.";
}

void CommonAttributes::setAttrValue(unsigned currentAttrIndex, const String& newValue) {
	if (currentAttrIndex >= 0 && currentAttrIndex < currentAttributes.size())
		currentAttributes[currentAttrIndex].setValue(newValue);
}

String CommonAttributes::getText() const {
	int size = currentAttributes.size();
	String result;
	for (int i = 0; i < size; i++)
	{
		result += currentAttributes[i].toString();
		if (i != size - 1)
			result += ' ';
	}
	return result;
}