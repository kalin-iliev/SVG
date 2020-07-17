#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Helpers.h"
#include <iostream>
#include <cstring>

Shape* Line::clone() const
{
	return new Line(*this);
}

Line::Line(const Line& other)
{
	this->attributes = other.attributes;
	this->type = Shape::ShapeType::LineType;
}

Line::Line(const Vector<Attribute>& attributes)
	: Shape(attributes)
{
	this->type = Shape::ShapeType::LineType;
}

void Line::translateCoordinates(int x, int y)
{
	unsigned x1AttributeIndex = attributes.indexOfAttribute("x1");
	unsigned y1AttributeIndex = attributes.indexOfAttribute("y1");
	unsigned x2AttributeIndex = attributes.indexOfAttribute("x2");
	unsigned y2AttributeIndex = attributes.indexOfAttribute("y2");
	if (x1AttributeIndex < 0 || y1AttributeIndex < 0 || x2AttributeIndex < 0 || y2AttributeIndex < 0)
	{
		throw String("Invalid line object attributes. Cannot translate.");
	}

	int x1 = attributes[x1AttributeIndex].getValue().toInt();
	int y1 = attributes[y1AttributeIndex].getValue().toInt();
	int x2 = attributes[x2AttributeIndex].getValue().toInt();
	int y2 = attributes[y2AttributeIndex].getValue().toInt();

	x1 += x;
	x2 += x;
	y1 += y;
	y2 += y;

	String bufferX1 = intToString(x1);
	String bufferX2 = intToString(y1);
	String bufferY1 = intToString(x2);
	String bufferY2 = intToString(y2);
	attributes.setAttributeValue(x1AttributeIndex, bufferX1);
	attributes.setAttributeValue(y1AttributeIndex, bufferY1);
	attributes.setAttributeValue(x2AttributeIndex, bufferX2);
	attributes.setAttributeValue(y2AttributeIndex, bufferY2);
}

String Line::getSVGDefinition() const
{
	String svg("<line ");
	svg += attributes.toString();
	svg += " />";

	return svg;
}

void Line::print() const
{
	std::cout << "line";
	attributes.printAttributes();
	std::cout << std::endl;
}

bool Line::fitsInRectangle(const Rectangle& other) const
{
	int currX1 = getAttribute("x1").getValue().toInt();
	int currY1 = getAttribute("y1").getValue().toInt();
	int currX2 = getAttribute("x2").getValue().toInt();
	int currY2 = getAttribute("y2").getValue().toInt();

	int rectX = other.getAttribute("x").getValue().toInt();
	int rectY = other.getAttribute("y").getValue().toInt();
	int width = other.getAttribute("width").getValue().toInt();
	int height = other.getAttribute("height").getValue().toInt();

	bool firstPointIsInside = (currX1 >= rectX && currX1 <= rectX + width) && (currY1 >= rectY && currY1 <= rectY + height);
	bool secondPointIsInside = (currX2 >= rectX && currX2 <= rectX + width) && (currY2 >= rectY && currY2 <= rectY + height);

	return firstPointIsInside && secondPointIsInside;
}

bool Line::fitsInCircle(const Circle& other) const
{
	int currX1 = getAttribute("x1").getValue().toInt();
	int currY1 = getAttribute("y1").getValue().toInt();
	int currX2 = getAttribute("x2").getValue().toInt();
	int currY2 = getAttribute("y2").getValue().toInt();

	int cx = other.getAttribute("cx").getValue().toInt();
	int cy = other.getAttribute("cy").getValue().toInt();
	int radius = other.getAttribute("r").getValue().toInt();


	int pointOneDistanceSquared = (cx - currX1) * (cx - currX1) + (cy - currY1) * (cy - currY1);
	int pointTwoDistanceSquared = (cx - currX2) * (cx - currX2) + (cy - currY2) * (cy - currY2);
	bool firstPointIsInside = pointOneDistanceSquared <= radius * radius;
	bool secondPointIsInside = pointTwoDistanceSquared <= radius * radius;

	return firstPointIsInside && secondPointIsInside;
}