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
	void init(const String& svgDefinition);
	void setSVGDefinition();
public:
	Shape* clone() const;
	Line(const String& svgDefinition);
	Line(const Line&);
	Line& operator=(const Line&);

	Attribute getAttribute(const String& attributeName) const;
	Vector<Attribute> getCommonAttributes() const;
	Vector<Attribute> getMainAttributes() const;

	bool fitsInRect(const Rectangle&) const; 
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(int x, int y);
	String getSVGDefinition() const { return svgDefinition; }
	void print() const;
	String getType() const { return type; }
};

