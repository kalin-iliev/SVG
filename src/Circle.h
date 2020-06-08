#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Attribute.h"
class Rectangle;

class Circle : public Shape
{
	MainAttributes attributes;
	String type;
	void copy(const Circle&);
	void init(const String&);
	void setText();
public:
	Shape* clone();
	Circle(const String&);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	Attribute getAttribute(const String& attrName) const;
	Vector<Attribute> getCommonAttributes() const { return commonAttr.getCurrentAttributes(); }
	Vector<Attribute> getMainAttributes() const { return attributes.getCurrentAttributes(); }

	bool fitsInRect(const Rectangle&) const; 
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(long int, long int);
	String getText() const;
	void print() const;
	String getType() const;
};

