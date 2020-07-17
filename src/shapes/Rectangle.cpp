#include <iostream>

#include "Rectangle.h"
#include "Circle.h"
#include "Helpers.h"

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

void Rectangle::translateCoordinates(Point2D translationPoint)
{
	unsigned xAttributeIndex = attributes.indexOfAttribute("x");
	unsigned yAttributeIndex = attributes.indexOfAttribute("y");

	int currentX = attributes[xAttributeIndex].getValue().toInt();
	int currentY = attributes[yAttributeIndex].getValue().toInt();

	Point2D rectanglePoint(currentX, currentY);
	rectanglePoint += translationPoint;

	String newX = intToString(rectanglePoint.x);
	String newY = intToString(rectanglePoint.y);
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
	Point2D rectanglePoint(currentX, currentY);

	int currentWidth = getAttribute("width").getValue().toInt();
	int currentHeight = getAttribute("height").getValue().toInt();
	
	int otherX = other.getAttribute("x").getValue().toInt();
	int otherY = other.getAttribute("y").getValue().toInt();
	Point2D otherRrectanglePoint(currentX, currentY);

	int otherWidth = other.getAttribute("width").getValue().toInt();
	int otherHeight = other.getAttribute("height").getValue().toInt();

	if ((((rectanglePoint.x >= otherRrectanglePoint.x) && (rectanglePoint.x + currentWidth <= otherRrectanglePoint.x + otherWidth)) &&
		((rectanglePoint.y >= otherRrectanglePoint.y) && (rectanglePoint.y + currentHeight <= otherRrectanglePoint.y + otherHeight))))
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
	Point2D rectanglePoint(currentX, currentY);

	int width = getAttribute("width").getValue().toInt();;
	int height = getAttribute("height").getValue().toInt();;

	int cx = other.getAttribute("cx").getValue().toInt();;
	int cy = other.getAttribute("cy").getValue().toInt();;
	Point2D center(cx, cy);

	int radius = other.getAttribute("r").getValue().toInt();;

	int topLeftPointToCenterDistance = center.squaredDistanceTo(rectanglePoint);
	int bottomLeftToCenterDistance = center.squaredDistanceTo(rectanglePoint + Point2D(0, height));
	int topRightPointToCenterDistance = center.squaredDistanceTo(rectanglePoint + Point2D(width, 0));;
	int bottolRightPointToCenterDistance = center.squaredDistanceTo(rectanglePoint + Point2D(width, height));;

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