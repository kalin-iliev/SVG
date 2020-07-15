#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include <iostream>
class Rectangle;
class Circle;

class ShapeAsText : public Shape
{
	String type;
	void copy(const ShapeAsText&);
	void init(const String&);
public:
	Shape* clone();
	ShapeAsText(const String& text = "");
	ShapeAsText(const ShapeAsText&);
	ShapeAsText& operator=(const ShapeAsText&);

	bool fitsInRect(const Rectangle&) const { return false; }
	bool fitsInCircle(const Circle&) const { return false; }

	Attribute getAttribute(const String& attrName) const { return Attribute(); }
	Vector<Attribute> getCommonAttributes() const { return Vector<Attribute>(); }
	Vector<Attribute> getMainAttributes() const { return Vector<Attribute>(); }

	void translateCoordinates(long int, long int) override { 
		std::cout << "The shape is invalid. It contains no attributes to translate.";
		return; 
	}

	String getText() const { return text; }
	void print() const { std::cout << text; }
	String getType() const { return type; }
};

