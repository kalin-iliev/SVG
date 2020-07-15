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
	int indexAttr = attributes.indexOfCurrentAttribute(attrName);
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
	unsigned x1Attr = attributes.indexOfCurrentAttribute("x1");
	unsigned y1Attr = attributes.indexOfCurrentAttribute("y1");
	unsigned x2Attr = attributes.indexOfCurrentAttribute("x2");
	unsigned y2Attr = attributes.indexOfCurrentAttribute("y2");
	long int x1 = attributes[x1Attr].getValue().toInt();
	long int y1 = attributes[y1Attr].getValue().toInt();
	long int x2 = attributes[x2Attr].getValue().toInt();
	long int y2 = attributes[y2Attr].getValue().toInt();
	x1 += incX;
	x2 += incX;
	y1 += incY;
	y2 += incY;

	String bufferX1;
	String bufferX2;
	String bufferY1;
	String bufferY2;
	bufferX1 = String(std::to_string(x1).c_str());
	bufferY1 = String(std::to_string(y1).c_str());
	bufferX2 = String(std::to_string(x2).c_str());
	bufferY2 = String(std::to_string(y2).c_str());
	attributes.setAttributeValue(x1Attr, bufferX1);
	attributes.setAttributeValue(y1Attr, bufferY1);
	attributes.setAttributeValue(x2Attr, bufferX2);
	attributes.setAttributeValue(y2Attr, bufferY2);
	setText();
}

void Line::setText() {
	text = ('<' + type + ' ' + attributes.currentAttributesToString() + ' ' + commonAttr.currentAttributesToString() + " />");
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
	if (!(firstPointIsInside && secondPointIsInside))
		return false;
	return true;
}

bool Line::fitsInCircle(const Circle& other) const {
	long int currX1 = getAttribute("x1").getValue().toInt();
	long int currY1 = getAttribute("y1").getValue().toInt();
	long int currX2 = getAttribute("x2").getValue().toInt();
	long int currY2 = getAttribute("y2").getValue().toInt();

	long int cx = other.getAttribute("cx").getValue().toInt();
	long int cy = other.getAttribute("cy").getValue().toInt();
	long int radius = other.getAttribute("r").getValue().toInt();

	bool firstPointIsInside = ( ( (cx - currX1) * (cx - currX1) ) + ( (cy - currY1) * (cy - currY1) ) ) <= radius * radius;
	bool secondPointIsInside = ( ( (cx - currX2) * (cx - currX2) ) + ( (cy - currY2) * (cy - currY2) ) ) <= radius * radius;
	if (!(firstPointIsInside && secondPointIsInside))
		return false;
	return true;
}