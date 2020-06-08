#pragma once
#include "Point2D.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "MainAttributes.h"
class Rectangle;
class Circle;

class Line : public Shape
{
	MainAttributes attributes;
	String type;
	void copy(const Line&);
	void init(const String& text);
	void setText();
public:
	Shape* clone();
	Line(const String& text);
	Line(const Line&);
	Line& operator=(const Line&);

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

