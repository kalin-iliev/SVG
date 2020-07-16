#include "Line.h"
#include <iostream>
#include <cstring>

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::copy(const Line& other)
{
	this->attributes = other.attributes;
	setSVGDefinition();
}

Attribute Line::getAttribute(const String& attributeName) const
{
	int attributeIndex = attributes.indexOfCurrentAttribute(attributeName);
	if (attributeIndex == -1)
	{
		return Attribute();
	}

	return attributes.getAttribute(attributeIndex);
}

void Line::init(const String& svgDefinition)
{
	this->type = "line";
	attributes = MainAttributes(svgDefinition, this->type);
	setSVGDefinition();
}

Line::Line(const String& svgDefinition)
{
	setCommonAttributes(svgDefinition);
	init(svgDefinition);
}

Line::Line(const Line& other) : Shape(other)
{
	if (this != &other)
	{
		copy(other);
	}
}

Line& Line::operator=(const Line& other)
{
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
	}
	return *this;
}

void Line::translateCoordinates(int x, int y)
{
	unsigned x1AttributeIndex = attributes.indexOfCurrentAttribute("x1");
	unsigned y1AttributeIndex = attributes.indexOfCurrentAttribute("y1");
	unsigned x2AttributeIndex = attributes.indexOfCurrentAttribute("x2");
	unsigned y2AttributeIndex = attributes.indexOfCurrentAttribute("y2");
	if (x1AttributeIndex < 0 || y1AttributeIndex < 0 || x2AttributeIndex < 0 || y2AttributeIndex < 0)
	{
		throw String("Invalid line object attributes. Cannot translate.");
	}

	long int x1 = attributes[x1AttributeIndex].getValue().toInt();
	long int y1 = attributes[y1AttributeIndex].getValue().toInt();
	long int x2 = attributes[x2AttributeIndex].getValue().toInt();
	long int y2 = attributes[y2AttributeIndex].getValue().toInt();

	x1 += x;
	x2 += x;
	y1 += y;
	y2 += y;

	// TODO reuse the util from Circle
	String bufferX1;
	String bufferX2;
	String bufferY1;
	String bufferY2;
	bufferX1 = String(std::to_string(x1).c_str());
	bufferY1 = String(std::to_string(y1).c_str());
	bufferX2 = String(std::to_string(x2).c_str());
	bufferY2 = String(std::to_string(y2).c_str());
	attributes.setAttributeValue(x1AttributeIndex, bufferX1);
	attributes.setAttributeValue(y1AttributeIndex, bufferY1);
	attributes.setAttributeValue(x2AttributeIndex, bufferX2);
	attributes.setAttributeValue(y2AttributeIndex, bufferY2);
	setSVGDefinition();
}

void Line::setSVGDefinition()
{
	this->svgDefinition = ('<' + type + ' ' + attributes.currentAttributesToString() + ' ' + commonAttributes.currentAttributesToString() + " />");
}

void Line::print() const
{
	std::cout << type << " ";
	attributes.printCurrentAttributes();
	std::cout << ' ';
	commonAttributes.printCurrentAttributes();
	std::cout << std::endl;
}

bool Line::fitsInRect(const Rectangle& other) const
{
	long int currX1 = getAttribute("x1").getValue().toInt();
	long int currY1 = getAttribute("y1").getValue().toInt();
	long int currX2 = getAttribute("x2").getValue().toInt();
	long int currY2 = getAttribute("y2").getValue().toInt();

	long int rectX = other.getAttribute("x").getValue().toInt();
	long int rectY = other.getAttribute("y").getValue().toInt();
	long int width = other.getAttribute("width").getValue().toInt();
	long int height = other.getAttribute("height").getValue().toInt();

	bool firstPointIsInside = (currX1 >= rectX && currX1 <= rectX + width) && (currY1 >= rectY && currY1 <= rectY + height);
	bool secondPointIsInside = (currX2 >= rectX && currX2 <= rectX + width) && (currY2 >= rectY && currY2 <= rectY + height);

	return firstPointIsInside && secondPointIsInside;
}

bool Line::fitsInCircle(const Circle& other) const
{
	long int currX1 = getAttribute("x1").getValue().toInt();
	long int currY1 = getAttribute("y1").getValue().toInt();
	long int currX2 = getAttribute("x2").getValue().toInt();
	long int currY2 = getAttribute("y2").getValue().toInt();

	long int cx = other.getAttribute("cx").getValue().toInt();
	long int cy = other.getAttribute("cy").getValue().toInt();
	long int radius = other.getAttribute("r").getValue().toInt();


	int pointOneDistanceSquared = (cx - currX1) * (cx - currX1) + (cy - currY1) * (cy - currY1);
	int pointTwoDistanceSquared = (cx - currX2) * (cx - currX2) + (cy - currY2) * (cy - currY2);
	bool firstPointIsInside = pointOneDistanceSquared <= radius * radius;
	bool secondPointIsInside = pointTwoDistanceSquared <= radius * radius;

	return firstPointIsInside && secondPointIsInside;
}

Vector<Attribute> Line::getCommonAttributes() const
{ 
	return commonAttributes.getCurrentAttributes();
}

Vector<Attribute> Line::getMainAttributes() const
{
	return attributes.getCurrentAttributes();
}