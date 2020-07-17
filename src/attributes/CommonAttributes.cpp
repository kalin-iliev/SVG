#include "CommonAttributes.h"

int CommonAttributes::findAttributeIndex(const String& attributeName, const Vector<String>& extractedAttributes)
{
	int size = extractedAttributes.size();
	for (int i = 0; i < size; i++)
	{
		if (extractedAttributes[i].beginsWith(attributeName) && extractedAttributes[i].firstIndexOf('=') == attributeName.size())
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
		this->allowedAttributes.push_back(allowedAttributes[i].getName());
	}
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

			Attribute newAttr(attributes[commonAttributeIndex], false);
			if (!newAttr)
				throw String("One of the common attributes is invalid.");
			currentAttributes.push_back(newAttr);
		}
	}	
}

Vector<Attribute> CommonAttributes::getCurrentAttributes() const
{
	return currentAttributes;
}







