#include "Shape.h"
#include "Constants.h"
#include <iostream>
#include <cstring>
#include <new>

void Shape::setCommonAttr(const String& text) {
	try {
		if(text.size() > 0)
			commonAttr = CommonAttributes(text);
	}
	catch (const String& error) {
		throw error;
	}
}

Shape* Shape::clone() {
	return nullptr;
}

Shape::Shape(const String& text) {
	try {
		setCommonAttr(text);
	}
	catch (const String& error) {
		throw error;
	}
}

void Shape::copy(const Shape& other) {
	commonAttr = other.commonAttr;
	text = other.text;
}

Shape::Shape(const Shape& other) {
	if(this != &other)
		copy(other);
}

Shape& Shape::operator = (const Shape& other) {
	if (this != &other)
		copy(other);

	return *this;
}
