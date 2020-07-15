#include "MainAttributes.h"

void MainAttributes::setCurrentAttributes(const String& text, const String& shapeType)
{
	Vector<String> attributes;
	extractAttributes(text, attributes);

	if (findAttributeNameIndex(shapeType, attributes) == -1)
		throw String("Can't recognise the shape.");

	for (int i = 0; i < allowedAttributes.size(); i++)
	{
		int indexCommonAttrInArray = findAttributeIndex(allowedAttributes[i], attributes);
		if (indexCommonAttrInArray == -1)
		{
			throw String("One of the mandatory main attributes is missing.");
		}
		
		bool valueIsInt = false;
		if (findAttributeNameIndex(allowedAttributes[i], allowedIntAttributes) > -1)
		{
			valueIsInt = true;
		}
		Attribute newAttribute(attributes[indexCommonAttrInArray], valueIsInt);
		if (!newAttribute)
		{
			throw String("One of the mandatory main attributes is invalid.");
		}

		currentAttributes.push_back(newAttribute);
	}
}

MainAttributes::MainAttributes(const String& text, const String& shapeType)
{
	if (shapeType == "circle")
	{
		addAllowedAttributes(circleAttributes, circleAttrSize);
	}
	else if (shapeType == "rect")
	{
		addAllowedAttributes(rectAttributes, rectAttrSize);
	}
	else if (shapeType == "line")
	{
		addAllowedAttributes(lineAttributes, lineAttrSize);
	}
	else
	{
		throw String("Unrecognised shape type.");
	}

	setCurrentAttributes(text, shapeType);
}

MainAttributes::MainAttributes(const MainAttributes& other) : CommonAttributes(other) {}

MainAttributes& MainAttributes::operator=(const MainAttributes& other) {
	if (this != &other)
		CommonAttributes::operator=(other);
	
	return *this;
}