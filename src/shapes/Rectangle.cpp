#include "Rectangle.h"
#include <iostream>
#include <cstring>

Shape* Rectangle::clone() {
	return new Rectangle(*this);
}

Attribute Rectangle::getAttribute(const String& attrName) const {
	int indexAttr = attributes.indexOfCurrentAttribute(attrName);
	if (indexAttr == -1)
		return Attribute();
	return attributes.getAttribute(indexAttr);
}

void Rectangle::init(const String& text) {
	try {
		attributes = MainAttributes(text, "rect");
		type = "rect";
		long int width = getAttribute("width").getValue().strToInt();
		long int height = getAttribute("height").getValue().strToInt();
		if (!(width >= 1) || !(height >= 1))
			throw String("Height and width can't be less than 1.");
		setText();
	}
	catch (const String& error) {
		throw error;
	}
}

Rectangle::Rectangle(const String& text) {
	try {
		setCommonAttr(text);
		init(text);
	}
	catch (const String& error) {
		throw error;
	}
}

Rectangle::Rectangle(const Rectangle& other) : Shape(other) {
	if (this != &other)
	{
		copy(other);
		type = other.type;
		setText();
	}
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
		setText();
	}
	return *this;
}

void Rectangle::copy(const Rectangle& other) {
	attributes = other.attributes;
}

void Rectangle::translateCoordinates(long int incX, long int incY) {
	unsigned xStr = attributes.indexOfCurrentAttribute("x");
	unsigned yStr = attributes.indexOfCurrentAttribute("y");
	long int x = attributes[xStr].getValue().strToInt();
	long int y = attributes[yStr].getValue().strToInt();
	x += incX;
	y += incY;
	String newX;
	String newY;
	newX = String(std::to_string(x).c_str());
	newY = String(std::to_string(y).c_str());
	attributes.setAttributeValue(xStr, newX);
	attributes.setAttributeValue(yStr, newY);
	setText();
}

void Rectangle::setText() {
	text = ('<' + type + ' ' + attributes.currentAttributesToString() + ' ' + commonAttr.currentAttributesToString() + " />");
}

void Rectangle::print() const {
	std::cout << type;
	int size = attributes.getCurrentAttributes().size();
	for (int i = 0; i < size; i++)
		std::cout << ' ' << attributes[i].getValue();
	std::cout << ' ';
	commonAttr.printCurrentAttributes();
	std::cout << std::endl;
}

bool Rectangle::fitsInRect(const Rectangle& other) const {
	long int currX = getAttribute("x").getValue().strToInt();
	long int currY = getAttribute("y").getValue().strToInt();
	long int currWidth = getAttribute("width").getValue().strToInt();
	long int currHeight = getAttribute("height").getValue().strToInt();
	
	long int otherX = other.getAttribute("x").getValue().strToInt();
	long int otherY = other.getAttribute("y").getValue().strToInt();
	long int otherWidth = other.getAttribute("width").getValue().strToInt();
	long int otherHeight = other.getAttribute("height").getValue().strToInt();

	if ((((currX >= otherX) && (currX + currWidth <= otherX + otherWidth)) && ((currY >= otherY) && (currY + currHeight <= otherY + otherHeight))))
		return true;
	return false;
}

bool Rectangle::fitsInCircle(const Circle& other) const {
	long int currX = getAttribute("x").getValue().strToInt();;
	long int currY = getAttribute("y").getValue().strToInt();;
	long int width = getAttribute("width").getValue().strToInt();;
	long int height = getAttribute("height").getValue().strToInt();;

	long int cx = other.getAttribute("cx").getValue().strToInt();;
	long int cy = other.getAttribute("cy").getValue().strToInt();;
	long int radius = other.getAttribute("r").getValue().strToInt();;

	bool rectPointInCircle1 = ( ((cx - currX) * (cx - currX))
							+ ((cy - currY) * (cy - currY)) ) <= (radius * radius);
	bool rectPointInCircle2 = ( ((cx  - currX) * (cx - currX))
							+ ( (cy - (currY + height)) * (cy - (currY + height)) ) ) <= (radius * radius);
	bool rectPointInCircle3 = ( ( (cx - (currX + width)) * (cx - (currX + width)) ) 
							+ ((cy - currY) * (cy - currY)) ) <= (radius * radius);
	bool rectPointInCircle4 = ( ( (cx - (currX + width)) * (cx - (currX + width)) ) 
							+ ( (cy - (currY + height)) * (cy - (currY + height)) ) ) <= (radius * radius);

	if (rectPointInCircle1 && rectPointInCircle2 && rectPointInCircle3 && rectPointInCircle4)
		return true;
	return false;
}