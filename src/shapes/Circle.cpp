#include "Circle.h"
#include <iostream>
#include <cmath>
#include <string>

Shape* Circle::clone() const
{
	return new Circle(*this);
}

Attribute Circle::getAttribute(const String& attributeName) const
{
	int attributeIndex = this->attributes.indexOfCurrentAttribute(attributeName);
	if (attributeIndex == -1)
	{
		return Attribute();
	}

	return this->attributes.getAttribute(attributeIndex);
}

String Circle::getType() const
{
	return type;
}

void Circle::init(const String& svgDefinition)
{
	this->type = "circle";
	this->attributes = MainAttributes(svgDefinition, this->type);
	int radius = getAttribute("r").getValue().toInt();
	if (radius < 1)
	{
		throw String("Circle is invalid. Radius can't be less than 1.");
	}

	setSVGDefinition();
}

void Circle::copy(const Circle& other)
{
	this->attributes = other.attributes;
	this->svgDefinition = other.svgDefinition;
}

Circle::Circle(const String& svgDefinition)
{
	setCommonAttributes(svgDefinition);
	init(svgDefinition);
}

Circle::Circle(const Circle& other) : Shape(other)
{
	if (this != &other)
	{
		copy(other);
		type = other.type;
		setSVGDefinition();
	}
}

Circle& Circle::operator=(const Circle& other)
{
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
		setSVGDefinition();
	}
	return *this;
}

void Circle::translateCoordinates(int translateX, int translateY)
{
	unsigned indexOfCxAttribute = attributes.indexOfCurrentAttribute("cx");
	unsigned indexOfCyAttribute = attributes.indexOfCurrentAttribute("cy");
	if (indexOfCxAttribute < 0 || indexOfCyAttribute < 0)
	{
		throw String("The circle has missing attributes and cannot be translated.");
	}

	long int cx = attributes[indexOfCxAttribute].getValue().toInt();
	long int cy = attributes[indexOfCyAttribute].getValue().toInt();
	cx += translateX;
	cy += translateY;
	// TODO create itoa util and refactor this
	String newCx;
	String newCy;
	newCx = String(std::to_string(cx).c_str());
	newCy = String(std::to_string(cy).c_str());
	attributes.setAttributeValue(indexOfCxAttribute, newCx);
	attributes.setAttributeValue(indexOfCyAttribute, newCy);
	setSVGDefinition();
}

String Circle::getSVGDefinition() const
{
	return svgDefinition;
}

void Circle::print() const
{
	std::cout << type;
	std::cout << ' ';
	attributes.printCurrentAttributes();
	std::cout << ' ';
	commonAttributes.printCurrentAttributes();
	std::cout << std::endl;
}

bool Circle::fitsInCircle(const Circle& other) const
{
	long int cx = getAttribute("cx").getValue().toInt();
	long int cy = getAttribute("cy").getValue().toInt();
	long int radius = getAttribute("r").getValue().toInt();

	long int otherCx = other.getAttribute("cx").getValue().toInt();
	long int otherCy = other.getAttribute("cy").getValue().toInt();
	long int otherRadius = other.getAttribute("r").getValue().toInt();

	long int radiusDiff = (otherRadius - radius);
	long int distanceRadiusSquared = (cx - otherCx) * (cx - otherCx) + (cy - otherCy) * (cy - otherCy);

	if (distanceRadiusSquared <= radiusDiff * radiusDiff)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Circle::fitsInRect(const Rectangle& other) const
{
	long int cx = getAttribute("cx").getValue().toInt();
	long int cy = getAttribute("cy").getValue().toInt();
	long int radius = getAttribute("r").getValue().toInt();

	long int rectX = other.getAttribute("x").getValue().toInt();
	long int rectY = other.getAttribute("y").getValue().toInt();
	long int rectWidth = other.getAttribute("width").getValue().toInt();
	long int rectHeight = other.getAttribute("height").getValue().toInt();

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

void Circle::setSVGDefinition()
{
	svgDefinition = '<' + getType() + ' ' + attributes.currentAttributesToString() + ' ' + commonAttributes.currentAttributesToString() + " />";
}

Vector<Attribute> Circle::getCommonAttributes() const
{
	return commonAttributes.getCurrentAttributes();
}

Vector<Attribute> Circle::getMainAttributes() const 
{
	return attributes.getCurrentAttributes();
}