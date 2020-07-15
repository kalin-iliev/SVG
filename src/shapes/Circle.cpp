#include "Circle.h"
#include <iostream>
#include <cmath>
#include <string>

Shape* Circle::clone() {
	return new Circle(*this);
}

Attribute Circle::getAttribute(const String& attrName) const {
	int indexAttr = attributes.indexOfCurrentAttribute(attrName);
	if (indexAttr == -1)
		return Attribute();
	return attributes.getAttribute(indexAttr);
}

String Circle::getType() const {
	return type;
}

void Circle::init(const String& text) {
	try {
		attributes = MainAttributes(text, "circle");
		type = "circle";
		long int radius = getAttribute("r").getValue().strToInt();
		if (radius < 1)
			throw String("Circle is invalid. Radius can't be less than 1.");
		setText();
	}
	catch (const String& error) {
		throw error;
	}
}

void Circle::copy(const Circle& other) {
	attributes = other.attributes;
	text = other.text;
}

Circle::Circle(const String& text) {
	try {
		setCommonAttr(text);
		init(text);
	}
	catch (const char* error) {
		throw error;
	}
}

Circle::Circle(const Circle& other) : Shape(other) {
	if (this != &other){
		copy(other);
		type = other.type;
		setText();
	}
}

Circle& Circle::operator=(const Circle& other) {
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
		setText();
	}
	return *this;
}

void Circle::translateCoordinates(long int incX, long int incY) {
	unsigned cxStr = attributes.indexOfCurrentAttribute("cx");
	unsigned cyStr = attributes.indexOfCurrentAttribute("cy");
	long int cx = attributes[cxStr].getValue().strToInt();
	long int cy = attributes[cyStr].getValue().strToInt();
	cx += incX;
	cy += incY;
	String newCx;
	String newCy;
	newCx = String(std::to_string(cx).c_str());
	newCy = String(std::to_string(cy).c_str());
	attributes.setAttributeValue(cxStr, String(newCx));
	attributes.setAttributeValue(cyStr, String(newCy));
	setText();
}

String Circle::getText() const {
	return text;
}

void Circle::print() const {
	std::cout << type;
	int size = attributes.getCurrentAttributes().size();
	for (int i = 0; i < size; i++)
		std::cout << ' ' << attributes[i].getValue();
	std::cout << ' ';
	commonAttr.printCurrentAttributes();
	std::cout << std::endl;
}

bool Circle::fitsInCircle(const Circle& other) const {
	long int cx = getAttribute("cx").getValue().strToInt();
	long int cy = getAttribute("cy").getValue().strToInt();
	long int radius = getAttribute("r").getValue().strToInt();
	long int otherCx = other.getAttribute("cx").getValue().strToInt();
	long int otherCy = other.getAttribute("cy").getValue().strToInt();
	long int otherRadius = other.getAttribute("r").getValue().strToInt();
	long int substractRadius = (otherRadius - radius);
	long int distanceRadius = (cx - otherCx) * (cx - otherCx) + (cy - otherCy) * (cy - otherCy);
	if (distanceRadius <= substractRadius)
		return true;
	return false;
}

bool Circle::fitsInRect(const Rectangle& other)  const {
	long int cx = getAttribute("cx").getValue().strToInt();
	long int cy = getAttribute("cy").getValue().strToInt();
	long int radius = getAttribute("r").getValue().strToInt();

	long int rectX = other.getAttribute("x").getValue().strToInt();
	long int rectY = other.getAttribute("y").getValue().strToInt();
	long int rectWidth = other.getAttribute("width").getValue().strToInt();
	long int rectHeight = other.getAttribute("height").getValue().strToInt();

	if (!(cx > rectX && cx < (rectX + rectWidth)))
		return false;
	if (!(cy > rectY && cy < (rectY + rectHeight)))
		return false;

	if ((cx + radius) > (rectX + rectWidth) || (cx - radius) < rectX)
		return false;
	if ((cy + radius) > (rectY + rectWidth) || (cy - radius) < rectY)
		return false;
	return true;
}

void Circle::setText() {
	text = ('<' + getType() + ' ' + attributes.currentAttributesToString() + ' ' + commonAttr.currentAttributesToString() + " />");
}