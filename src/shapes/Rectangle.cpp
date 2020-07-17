#include "Rectangle.h"
#include "Circle.h"
#include "Helpers.h"
#include <iostream>
#include <cstring>

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

Rectangle::Rectangle(const Vector<Attribute>& attributes)
	: Shape(attributes)
{
	this->type = Shape::RectangleType;
}

Rectangle::Rectangle(const Rectangle& other)
{
	this->attributes = other.attributes;
	this->type = Shape::RectangleType;
}

void Rectangle::translateCoordinates(int x, int y)
{
	unsigned xAttributeIndex = attributes.indexOfAttribute("x");
	unsigned yAttributeIndex = attributes.indexOfAttribute("y");

	int currentX = attributes[xAttributeIndex].getValue().toInt();
	int currentY = attributes[yAttributeIndex].getValue().toInt();

	currentX += x;
	currentY += y;

	String newX = intToString(currentX);
	String newY = intToString(currentY);
	attributes.setAttributeValue(xAttributeIndex, newX);
	attributes.setAttributeValue(yAttributeIndex, newY);
}

void Rectangle::print() const
{
	std::cout << "rect";
	this->attributes.printAttributes();
	std::cout << std::endl;
}

bool Rectangle::fitsInRectangle(const Rectangle& other) const
{
	int currentX = getAttribute("x").getValue().toInt();
	int currentY = getAttribute("y").getValue().toInt();
	int currentWidth = getAttribute("width").getValue().toInt();
	int currentHeight = getAttribute("height").getValue().toInt();
	
	int otherX = other.getAttribute("x").getValue().toInt();
	int otherY = other.getAttribute("y").getValue().toInt();
	int otherWidth = other.getAttribute("width").getValue().toInt();
	int otherHeight = other.getAttribute("height").getValue().toInt();

	if ((((currentX >= otherX) && (currentX + currentWidth <= otherX + otherWidth)) &&
		((currentY >= otherY) && (currentY + currentHeight <= otherY + otherHeight))))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rectangle::fitsInCircle(const Circle& other) const
{
	int currentX = getAttribute("x").getValue().toInt();;
	int currentY = getAttribute("y").getValue().toInt();;
	int width = getAttribute("width").getValue().toInt();;
	int height = getAttribute("height").getValue().toInt();;

	int cx = other.getAttribute("cx").getValue().toInt();;
	int cy = other.getAttribute("cy").getValue().toInt();;
	int radius = other.getAttribute("r").getValue().toInt();;

	int topLeftPointToCenterDistance = ((cx - currentX) * (cx - currentX)) + ((cy - currentY) * (cy - currentY));
	int bottomLeftToCenterDistance = ((cx  - currentX) * (cx - currentX)) + (cy - (currentY + height)) * (cy - (currentY + height));
	int topRightPointToCenterDistance = (cx - (currentX + width)) * (cx - (currentX + width)) + (cy - currentY) * (cy - currentY);
	int bottolRightPointToCenterDistance = (cx - (currentX + width)) * (cx - (currentX + width)) + (cy - (currentY + height)) * (cy - (currentY + height));

	bool topLeftPointInCircle = topLeftPointToCenterDistance <= radius * radius;
	bool bottomLeftPointInCircle = bottomLeftToCenterDistance <= radius * radius;
	bool topRightPointInCircle = topRightPointToCenterDistance <= radius * radius;
	bool bottolRightInCircle = bottolRightPointToCenterDistance <= radius * radius;

	return topLeftPointInCircle && bottomLeftPointInCircle && topRightPointInCircle && bottolRightInCircle;
}

String Rectangle::getSVGDefinition() const
{
	String svg("<rectangle ");
	svg += attributes.toString();
	svg += " />";

	return svg;
}