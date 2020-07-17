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

void Circle::translateCoordinates(int translateX, int translateY)
{
	unsigned indexOfCxAttribute = attributes.indexOfAttribute("cx");
	unsigned indexOfCyAttribute = attributes.indexOfAttribute("cy");
	if (indexOfCxAttribute < 0 || indexOfCyAttribute < 0)
	{
		throw String("The circle has missing attributes and cannot be translated.");
	}

	int cx = attributes[indexOfCxAttribute].getValue().toInt();
	int cy = attributes[indexOfCyAttribute].getValue().toInt();
	cx += translateX;
	cy += translateY;

	String newCx = intToString(cx);
	String newCy = intToString(cy);
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
	int radius = getAttribute("r").getValue().toInt();

	int otherCx = other.getAttribute("cx").getValue().toInt();
	int otherCy = other.getAttribute("cy").getValue().toInt();
	int otherRadius = other.getAttribute("r").getValue().toInt();

	int radiusDiff = (otherRadius - radius);
	int distanceRadiusSquared = (cx - otherCx) * (cx - otherCx) + (cy - otherCy) * (cy - otherCy);

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
	int radius = getAttribute("r").getValue().toInt();

	int rectX = other.getAttribute("x").getValue().toInt();
	int rectY = other.getAttribute("y").getValue().toInt();
	int rectWidth = other.getAttribute("width").getValue().toInt();
	int rectHeight = other.getAttribute("height").getValue().toInt();

	if (!(cx > rectX && cx < (rectX + rectWidth)))
	{
		return false;
	}

	if (!(cy > rectY && cy < (rectY + rectHeight)))
	{
		return false;
	}

	if ((cx + radius) > (rectX + rectWidth) || (cx - radius) < rectX)
	{
		return false;
	}

	if ((cy + radius) > (rectY + rectWidth) || (cy - radius) < rectY)
	{
		return false;
	}

	return true;
}