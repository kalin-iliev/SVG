#include <iostream>
#include <cmath>
#include <string>

#include "Circle.h"
#include "Rectangle.h"

Shape* Circle::clone() const
{
	return new Circle(*this);
}

Circle::Circle(const Vector<Attribute>& attributes)
	: Shape(attributes)
{
	this->type = Shape::CircleType;
}

Circle::Circle(const Circle& other)
{
	if (this != &other)
	{
		this->type = Shape::CircleType;
		this->attributes = other.attributes;
	}
}

void Circle::translateCoordinates(Point2D translationPoint)
{
	unsigned indexOfCxAttribute = attributes.indexOfAttribute("cx");
	unsigned indexOfCyAttribute = attributes.indexOfAttribute("cy");
	if (indexOfCxAttribute < 0 || indexOfCyAttribute < 0)
	{
		throw String("The circle has missing attributes and cannot be translated.");
	}

	int cx = attributes[indexOfCxAttribute].getValue().toInt();
	int cy = attributes[indexOfCyAttribute].getValue().toInt();
	Point2D center(cx, cy);
	
	center += translationPoint;

	String newCx = intToString(center.x);
	String newCy = intToString(center.y);
	attributes.setAttributeValueByIndex(indexOfCxAttribute, newCx);
	attributes.setAttributeValueByIndex(indexOfCyAttribute, newCy);
}

String Circle::getSVGDefinition() const
{
	String svg("<circle ");
	svg += attributes.toString();
	svg += " />";

	return svg;
}

void Circle::print() const
{
	std::cout << "circle";
	attributes.printAttributes();
	std::cout << std::endl;
}

bool Circle::fitsInCircle(const Circle& other) const
{
	int cx = getAttribute("cx").getValue().toInt();
	int cy = getAttribute("cy").getValue().toInt();
	Point2D center(cx, cy);

	int radius = getAttribute("r").getValue().toInt();

	int otherCx = other.getAttribute("cx").getValue().toInt();
	int otherCy = other.getAttribute("cy").getValue().toInt();
	Point2D otherPointCenter(otherCx, otherCy);

	int otherRadius = other.getAttribute("r").getValue().toInt();

	int radiusDiff = (otherRadius - radius);
	int distanceRadiusSquared = center.squaredDistanceTo(otherPointCenter);

	if (distanceRadiusSquared <= radiusDiff * radiusDiff)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Circle::fitsInRectangle(const Rectangle& other) const
{
	int cx = getAttribute("cx").getValue().toInt();
	int cy = getAttribute("cy").getValue().toInt();
	Point2D center(cx, cy);

	int radius = getAttribute("r").getValue().toInt();

	int rectX = other.getAttribute("x").getValue().toInt();
	int rectY = other.getAttribute("y").getValue().toInt();
	Point2D rectanglePoint(rectX, rectY);

	int rectWidth = other.getAttribute("width").getValue().toInt();
	int rectHeight = other.getAttribute("height").getValue().toInt();

	if (!(center.x > rectanglePoint.x && center.x < (rectanglePoint.x + rectWidth)))
	{
		return false;
	}

	if (!(center.y > rectanglePoint.y && center.y < (rectanglePoint.y + rectHeight)))
	{
		return false;
	}

	if ((center.x + radius) > (rectanglePoint.x + rectWidth) || (center.x - radius) < rectanglePoint.x)
	{
		return false;
	}

	if ((center.y + radius) > (rectanglePoint.y + rectWidth) || (center.y - radius) < rectanglePoint.y)
	{
		return false;
	}

	return true;
}