#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Attribute.h"
class Rectangle;

class Circle : public Shape
{
	MainAttributes attributes;
	String type;	// TODO change type to enum - should be in base class
	void copy(const Circle&);
	void init(const String&);
	void setSVGDefinition();
public:
	Shape* clone() const;
	Circle(const String&);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	Attribute getAttribute(const String& attrName) const;
	Vector<Attribute> getCommonAttributes() const;
	Vector<Attribute> getMainAttributes() const;

	bool fitsInRect(const Rectangle&) const;
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(int x, int y);
	String getSVGDefinition() const;
	void print() const;
	String getType() const;
};

