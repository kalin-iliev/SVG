#include "Line.h"
#include <iostream>
#include <cstring>

Shape* Line::clone() {
	return new Line(*this);
}

void Line::copy(const Line& other) {
	attributes = other.attributes;
}

Attribute Line::getAttribute(const String& attrName) const {
	int indexAttr = attributes.findCurrentAttribute(attrName);
	if (indexAttr == -1)
		return Attribute();
	return attributes.getAttribute(indexAttr);
}

void Line::init(const String& text) {
	try {
		attributes = MainAttributes(text, "line");
		type = "line";
		setText();
	}
	catch (const String& error) {
		throw error;
	}
}

Line::Line(const String& text) {
	try {
		setCommonAttr(text);
		init(text);
	}
	catch (const String& error) {
		throw error;
	}
}

Line::Line(const Line& other) : Shape(other) {
	if (this != &other)
	{
		copy(other);
		type = other.type;
		setText();
	}
}

Line& Line::operator=(const Line& other) {
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
		setText();
	}
	return *this;
}

void Line::translateCoordinates(long int incX, long int incY) {
	unsigned x1Attr = attributes.findCurrentAttribute("x1");
	unsigned y1Attr = attributes.findCurrentAttribute("y1");
	unsigned x2Attr = attributes.findCurrentAttribute("x2");
	unsigned y2Attr = attributes.findCurrentAttribute("y2");
	long int x1 = attributes[x1Attr].getValue().strToInt();
	long int y1 = attributes[y1Attr].getValue().strToInt();
	long int x2 = attributes[x2Attr].getValue().strToInt();
	long int y2 = attributes[y2Attr].getValue().strToInt();
	x1 += incX;
	x2 += incX;
	y1 += incY;
	y2 += incY;

	char bufferX1[20];
	char bufferX2[20];
	char bufferY1[20];
	char bufferY2[20];
	_itoa(x1, bufferX1, 10);
	_itoa(y1, bufferY1, 10);
	_itoa(x2, bufferX2, 10);
	_itoa(y2, bufferY2, 10);
	attributes.setAttrValue(x1Attr, String(bufferX1));
	attributes.setAttrValue(y1Attr, String(bufferY1));
	attributes.setAttrValue(x2Attr, String(bufferX2));
	attributes.setAttrValue(y2Attr, String(bufferY2));
	setText();
}

void Line::setText() {
	text = ('<' + type + ' ' + attributes.getText() + ' ' + commonAttr.getText() + " />");
}

void Line::print() const {
	std::cout << type;
	int size = attributes.getCurrentAttributes().size();
	for (int i = 0; i < size; i++)
		std::cout << ' ' << attributes[i].getValue();
	std::cout << ' ';
	commonAttr.printCurrentAttributes();
	std::cout << std::endl;
}

bool Line::fitsInRect(const Rectangle& other) const {
	long int currX1 = getAttribute("x1").getValue().strToInt();
	long int currY1 = getAttribute("y1").getValue().strToInt();
	long int currX2 = getAttribute("x2").getValue().strToInt();
	long int currY2 = getAttribute("y2").getValue().strToInt();

	long int rectX = other.getAttribute("x").getValue().strToInt();
	long int rectY = other.getAttribute("y").getValue().strToInt();
	long int width = other.getAttribute("width").getValue().strToInt();
	long int height = other.getAttribute("height").getValue().strToInt();

	bool firstPointIsInside = (currX1 >= rectX && currX1 <= rectX + width) && (currY1 >= rectY && currY1 <= rectY + height);
	bool secondPointIsInside = (currX2 >= rectX && currX2 <= rectX + width) && (currY2 >= rectY && currY2 <= rectY + height);
	if (!(firstPointIsInside && secondPointIsInside))
		return false;
	return true;
}

bool Line::fitsInCircle(const Circle& other) const {
	long int currX1 = getAttribute("x1").getValue().strToInt();
	long int currY1 = getAttribute("y1").getValue().strToInt();
	long int currX2 = getAttribute("x2").getValue().strToInt();
	long int currY2 = getAttribute("y2").getValue().strToInt();

	long int cx = other.getAttribute("cx").getValue().strToInt();
	long int cy = other.getAttribute("cy").getValue().strToInt();
	long int radius = other.getAttribute("r").getValue().strToInt();

	bool firstPointIsInside = ( ( (cx - currX1) * (cx - currX1) ) + ( (cy - currY1) * (cy - currY1) ) ) <= radius * radius;
	bool secondPointIsInside = ( ( (cx - currX2) * (cx - currX2) ) + ( (cy - currY2) * (cy - currY2) ) ) <= radius * radius;
	if (!(firstPointIsInside && secondPointIsInside))
		return false;
	return true;
}