#include "CommonAttributes.h"

int CommonAttributes::findAttributeIndex(const String& attributeName, const Vector<String>& extractedAttributes)
{
	int size = extractedAttributes.size();
	for (int i = 0; i < size; i++)
	{
		if (extractedAttributes[i].beginWith(attributeName) && extractedAttributes[i].has('=') == attributeName.size())
			return i;
	}
	return -1;
}

int CommonAttributes::findAttributeNameIndex(const String& attributeName, const Vector<String>& attributeNames)
{
	int size = attributeNames.size();
	for (int i = 0; i < size; i++)
	{
		if (attributeNames[i] == attributeName)
			return i;
	}

	return -1;
}

void CommonAttributes::addAllowedAttributes(const AttributeInfo allowedAttributes[], int allowedAttributesCount)
{
	for (int i = 0; i < allowedAttributesCount; i++)
	{
		if(allowedAttributes[i].intValid())
			this->allowedIntAttributes.push_back(allowedAttributes[i].getName());
		this->allowedAttributes.push_back(allowedAttributes[i].getName());
	}
}

bool CommonAttributes::isLetter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

void CommonAttributes::setCurrentAttributes(const String& text)
{
	Vector<String> attributes;
	extractAttributes(text, attributes);

	for (int i = 0; i < allowedAttributes.size(); i++)
	{
		int commonAttributeIndex = findAttributeIndex(allowedAttributes[i], attributes);
		if (commonAttributeIndex > -1)
		{
			bool valueIsInt = false;
			if (findAttributeNameIndex(allowedAttributes[i], allowedIntAttributes) > -1)
				valueIsInt = true;

			Attribute newAttr(attributes[commonAttributeIndex], valueIsInt);
			if (!newAttr)
				throw String("One of the common attributes is invalid.");
			currentAttributes.push_back(newAttr);
		}
	}	
}

// TODO refactor - it is too long and complicated!
int CommonAttributes::extractAttributes(const String& text, Vector<String>& attributes)
{
	int count = 0;
	int index = 0;
	while (text[index])
	{
		while (text[index] && !isLetter(text[index]))
		{  // skip letters to the beginning of a word
			++index;
		}
		if (text[index])
		{ // if there is a word, count it
			int start = index;
			int attrSize = 0;
			int currentSize = 0;
			while (text[index] && (isLetter(text[index]) || text[index] == '-'))
			{  // skip to the end of the word
				++attrSize;
				++index;
			}

			while (text[index] && !isLetter(text[index]))
			{
				if (text[index] == '-')
				{
					++attrSize;
					++index;
					while (text[index] && text[index] != '=')
					{
						++attrSize;
						++index;
					}
					++index;
				}
				if (text[index] == '=')
				{
					++attrSize;
					++index;
					while (text[index] && text[index] != '"')
						++index;
				}
				else if (text[index] == '"')
				{
					++attrSize;
					++index;
					while (text[index] && text[index] != '"')
					{

						if (text[index] != ' ' && text[index] != '\n' && text[index] != '\t')
							++attrSize;
						++index;
					}
					++attrSize;
					++index;
				}
				else {
					++index;
				}
			}

			char* attr = new char[attrSize + 1];
			bool hasAssignmentChar = false;
			for (int p = start; p < index && currentSize < attrSize; p++) {
				if ((isLetter(text[p]) || (text[p] != ' ' && text[p] != '\n' && text[p] != '\t')) && currentSize < attrSize + 1)
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

	return count;
}

CommonAttributes::CommonAttributes(const String& text)
{
	addAllowedAttributes(commonAttributes, commonAttrSize);
	setCurrentAttributes(text);
}

CommonAttributes::CommonAttributes(const CommonAttributes& other)
{
	if (this != &other)
	{
		allowedAttributes = other.allowedAttributes;
		allowedIntAttributes = other.allowedIntAttributes;
		currentAttributes = other.currentAttributes;
	}
}

CommonAttributes& CommonAttributes::operator=(const CommonAttributes& other)
{
	if (this != &other) {
		this->allowedAttributes = other.allowedAttributes;
		this->allowedIntAttributes = other.allowedIntAttributes;
		this->currentAttributes = other.currentAttributes;
	}
	return *this;
}

void CommonAttributes::printAllowedAttributes() const
{
	for (int i = 0; i < allowedAttributes.size(); i++)
	{
		std::cout << allowedAttributes[i];
		if (i != allowedAttributes.size() - 1)
			std::cout << ", ";
	}
}

Vector<String> CommonAttributes::getAllowedAttributes() const
{
	return allowedAttributes;
}

void CommonAttributes::printAllowedIntAttributes() const
{
	for (int i = 0; i < allowedAttributes.size(); i++)
	{
		std::cout << allowedIntAttributes[i];
		if (i != allowedAttributes.size() - 1)
			std::cout << ", ";
	}
}

Vector<String> CommonAttributes::getAllowedIntAttributes() const
{
	return allowedIntAttributes;
}

void CommonAttributes::printCurrentAttributes() const
{
	for (int i = 0; i < currentAttributes.size(); i++)
	{
		std::cout << currentAttributes[i].getValue();
		if (i != currentAttributes.size() - 1)
			std::cout << ' ';
	}
}

Vector<Attribute> CommonAttributes::getCurrentAttributes() const
{
	return currentAttributes;
}

int CommonAttributes::indexOfAllowedAttribute(const String& attr) const
{
	for (int i = 0; i < allowedAttributes.size(); i++)
	{
		if (allowedAttributes[i] == attr)
		{
			return i;
		}
	}
	return -1;
}

int CommonAttributes::indexOfAllowedIntAttribute(const String& attr) const
{
	for (int i = 0; i < allowedIntAttributes.size(); i++)
	{
		if (allowedIntAttributes[i] == attr)
		{
			return i;
		}
	}
	return -1;
}

int CommonAttributes::indexOfCurrentAttribute(const String& attr) const
{
	for (int i = 0; i < currentAttributes.size(); i++)
	{
		if (currentAttributes[i].getName() == attr)
		{
			return i;
		}
	}
	return -1;
}

Attribute CommonAttributes::getAttribute(unsigned index) const
{
	if (index >= currentAttributes.size())
	{
		throw String("The index is out of the range of the attributes.");
	}

	return currentAttributes[index];
}

Attribute CommonAttributes::operator[](unsigned index) const
{
	return getAttribute(index);
}

Attribute& CommonAttributes::operator[](unsigned index)
{
	if (index >= currentAttributes.size())
	{
		throw String("The index is out of the range of the attributes.");
	}
	return currentAttributes[index];
}

void CommonAttributes::setAttributeValue(const String& currentAttr, const String& newValue)
{
	int currentAttributeIndex = indexOfCurrentAttribute(currentAttr);
	if (currentAttributeIndex > -1)
	{
		currentAttributes[indexOfCurrentAttribute(currentAttr)].setValue(newValue);
	}
	else
	{
		// TODO throw exception
		std::cout << "Couldn't find the attribute.";
	}
}

void CommonAttributes::setAttributeValue(unsigned currentAttrIndex, const String& newValue)
{
	if (currentAttrIndex < currentAttributes.size())
	{
		currentAttributes[currentAttrIndex].setValue(newValue);
	}
	// TODO else throw exception
}

String CommonAttributes::currentAttributesToString() const
{
	String result;
	for (int i = 0; i < currentAttributes.size(); i++)
	{
		result += currentAttributes[i].toString();
		if (i != currentAttributes.size() - 1)
			result += ' ';
	}
	return result;
}