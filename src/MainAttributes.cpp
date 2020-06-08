#include "MainAttributes.h"

void MainAttributes::setCurrentAttributes(const String& text, const String& shapeType) {
	try {
		Vector<String> attributes;
		extractAttributes(text, attributes);
		int allowedAttrSize = allowedAttributes.size();

		if (findAttributeName(shapeType, attributes) == -1)
			throw String("Can't recognise the shape.");

		for (int i = 0; i < allowedAttrSize; i++)
		{
			int indexCommonAttrInArray = findAttribute(allowedAttributes[i], attributes);
			if (indexCommonAttrInArray == -1)
				throw String("One of the mandatory main attributes is missing.");
			
			bool valueIsInt = false;
			if (findAttributeName(allowedAttributes[i], allowedIntAttributes) > -1)
				valueIsInt = true;
			Attribute newAttr(attributes[indexCommonAttrInArray], valueIsInt);
			if (!newAttr)
				throw String("One of the mandatory main attributes is invalid.");

			currentAttributes.push_back(newAttr);
		}
	}
	catch (const String& error) {
		throw error;
	}
}

MainAttributes::MainAttributes(const String& text, const String& shapeType) {
	try {
		if (shapeType == "circle")
			pushInAllowedAttributes(circleAttributes, circleAttrSize);
		else if (shapeType == "rect")
			pushInAllowedAttributes(rectAttributes, rectAttrSize);
		else if (shapeType == "line")
			pushInAllowedAttributes(lineAttributes, lineAttrSize);
		else
			throw String("Unrecognised shape type.");
		setCurrentAttributes(text, shapeType);
	}
	catch (const String& error) {
		throw error;
	}
}

MainAttributes::MainAttributes(const MainAttributes& other) : CommonAttributes(other) {}

MainAttributes& MainAttributes::operator=(const MainAttributes& other) {
	if (this != &other)
		CommonAttributes::operator=(other);
	
	return *this;
}