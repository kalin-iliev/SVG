#include "Shape.h"
#include "Constants.h"
#include <iostream>
#include <cstring>
#include <new>

void Shape::setCommonAttributes(const String& svgDefinition)
{
	if(svgDefinition.size() > 0)
	{
		commonAttributes = CommonAttributes(svgDefinition);
	}
}

Shape* Shape::clone()
{
	return nullptr;
}

Shape::Shape(const String& svgDefinition)
{
	setCommonAttributes(svgDefinition);
}

void Shape::copy(const Shape& other)
{
	this->commonAttributes = other.commonAttributes;
	this->svgDefinition = other.svgDefinition;
}

Shape::Shape(const Shape& other)
{
	if(this != &other)
	{
		copy(other);
	}
}

Shape& Shape::operator = (const Shape& other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}
