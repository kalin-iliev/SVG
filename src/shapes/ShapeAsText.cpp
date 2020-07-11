#include "ShapeAsText.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include <iostream>
#include <cstring>

Shape* ShapeAsText::clone() {
	return new ShapeAsText(*this);
}

void ShapeAsText::init(const String& text) {
	this->text = text;
	type = "unknown";
}

void ShapeAsText::copy(const ShapeAsText& other) {
	init(other.text);
}

ShapeAsText::ShapeAsText(const String& text) {
	init(text);
}

ShapeAsText::ShapeAsText(const ShapeAsText& other) : Shape(other) {
	if (this != &other)
		copy(other);
}

ShapeAsText& ShapeAsText::operator=(const ShapeAsText& other) {
	if (this != &other)
	{
		Shape::operator=(other);
		copy(other);
	}
	return *this;
}
