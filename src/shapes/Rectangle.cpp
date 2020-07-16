#include "Rectangle.h"
#include <iostream>
#include <cstring>

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

Attribute Rectangle::getAttribute(const String& attributeName) const
{
	int attributeIndex = attributes.indexOfCurrentAttribute(attributeName);
	if (attributeIndex == -1)
	{
		return Attribute();
	}
	return this->attributes.getAttribute(attributeIndex);
}

void Rectangle::init(const String& svgDefinition)
{
	this->type = "rect";
	attributes = MainAttributes(svgDefinition, this->type);

	long int width = getAttribute("width").getValue().toInt();
	long int height = getAttribute("height").getValue().toInt();

	if (!(width >= 1) || !(height >= 1))
	{
		throw String("Height and width can't be less than 1.");
	}
	setSVGDefinition();
}

Rectangle::Rectangle(const String& svgDefinition)
{
	setCommonAttributes(svgDefinition);
	init(svgDefinition);
}

Rectangle::Rectangle(const Rectangle& other) : Shape(other)
{
	if (this != &other)
	{
		this->type = other.type;
		copy(other);
	}
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
	}
	return *this;
}

void Rectangle::copy(const Rectangle& other)
{
	attributes = other.attributes;
	setSVGDefinition();
}

void Rectangle::translateCoordinates(int x, int y)
{
	unsigned xAttributeIndex = attributes.indexOfCurrentAttribute("x");
	unsigned yAttributeIndex = attributes.indexOfCurrentAttribute("y");

	long int currentX = attributes[xAttributeIndex].getValue().toInt();
	long int currentY = attributes[yAttributeIndex].getValue().toInt();

	currentX += x;
	currentY += y;
	// TODO reuse the util itoa
	String newX;
	String newY;
	newX = String(std::to_string(currentX).c_str());
	newY = String(std::to_string(currentY).c_str());

	attributes.setAttributeValue(xAttributeIndex, newX);
	attributes.setAttributeValue(yAttributeIndex, newY);
	setSVGDefinition();
}

void Rectangle::setSVGDefinition()
{
	svgDefinition = ('<' + type + ' ' + attributes.currentAttributesToString() + ' ' + commonAttributes.currentAttributesToString() + " />");
}

void Rectangle::print() const
{
	std::cout << type << " ";
	this->attributes.printCurrentAttributes();
	std::cout << ' ';
	commonAttributes.printCurrentAttributes();
	std::cout << std::endl;
}

bool Rectangle::fitsInRect(const Rectangle& other) const
{
	long int currentX = getAttribute("x").getValue().toInt();
	long int currentY = getAttribute("y").getValue().toInt();
	long int currentWidth = getAttribute("width").getValue().toInt();
	long int currentHeight = getAttribute("height").getValue().toInt();
	
	long int otherX = other.getAttribute("x").getValue().toInt();
	long int otherY = other.getAttribute("y").getValue().toInt();
	long int otherWidth = other.getAttribute("width").getValue().toInt();
	long int otherHeight = other.getAttribute("height").getValue().toInt();

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
	long int currentX = getAttribute("x").getValue().toInt();;
	long int currentY = getAttribute("y").getValue().toInt();;
	long int width = getAttribute("width").getValue().toInt();;
	long int height = getAttribute("height").getValue().toInt();;

	long int cx = other.getAttribute("cx").getValue().toInt();;
	long int cy = other.getAttribute("cy").getValue().toInt();;
	long int radius = other.getAttribute("r").getValue().toInt();;

	bool topLeftPointInCircle = ( ((cx - currentX) * (cx - currentX))
							+ ((cy - currentY) * (cy - currentY)) ) <= (radius * radius);
	bool bottolLeftPointInCircle2 = ( ((cx  - currentX) * (cx - currentX))
							+ ( (cy - (currentY + height)) * (cy - (currentY + height)) ) ) <= (radius * radius);
	bool topRightPointInCircle3 = ( ( (cx - (currentX + width)) * (cx - (currentX + width)) ) 
							+ ((cy - currentY) * (cy - currentY)) ) <= (radius * radius);
	bool bottolRightInCircle4 = ( ( (cx - (currentX + width)) * (cx - (currentX + width)) ) 
							+ ( (cy - (currentY + height)) * (cy - (currentY + height)) ) ) <= (radius * radius);

	return topLeftPointInCircle && bottolLeftPointInCircle2 && topRightPointInCircle3 && bottolRightInCircle4;
}

Vector<Attribute> Rectangle::getCommonAttributes() const
{
	return commonAttributes.getCurrentAttributes();
}

Vector<Attribute> Rectangle::getMainAttributes() const
{ 
	return attributes.getCurrentAttributes(); 
}
