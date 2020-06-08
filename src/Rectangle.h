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
	void init(const String& text);
	void setText();
public:
	Shape* clone();
	Rectangle(const String&);
	Rectangle(const Rectangle&);
	Rectangle& operator=(const Rectangle&);

	Attribute getAttribute(const String& attrName) const;
	Vector<Attribute> getCommonAttributes() const { return commonAttr.getCurrentAttributes(); }
	Vector<Attribute> getMainAttributes() const { return attributes.getCurrentAttributes(); }

	bool fitsInRect(const Rectangle&) const;
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(long int, long int);
	String getText() const { return text; }
	void print() const;
	String getType() const { return type; }
};

