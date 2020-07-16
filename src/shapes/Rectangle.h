#pragma once
#include "Shape.h"
#include "Circle.h"
#include "MainAttributes.h"
class Circle;

class Rectangle : public Shape
{
	MainAttributes attributes;
	String type;
	void copy(const Rectangle& other);
	void init(const String& svgDefinition);
	void setSVGDefinition();
public:
	Shape* clone() const;
	Rectangle(const String&);
	Rectangle(const Rectangle&);
	Rectangle& operator=(const Rectangle&);

	Attribute getAttribute(const String& attrName) const;
	Vector<Attribute> getCommonAttributes() const;
	Vector<Attribute> getMainAttributes() const;

	bool fitsInRect(const Rectangle&) const;
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(int x, int y);
	String getSVGDefinition() const { return svgDefinition; } // TODO remove - should be in base class
	void print() const;
	String getType() const { return type; } // TODO remove - should be in base class
};

