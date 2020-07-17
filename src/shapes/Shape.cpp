#include "Shape.h"
#include "Constants.h"

Shape::Shape(const Vector<Attribute>& attributes)
	: attributes(attributes)
{}

Shape::ShapeType Shape::getType()
{
	return this->type;
}

Attribute Shape::getAttribute(const String& attributeName) const
{
	int attributeIndex = this->attributes.indexOfAttribute(attributeName);
	if (attributeIndex == -1)
	{
		return Attribute();
	}

	return this->attributes.getAttributeByIndex(attributeIndex);
}