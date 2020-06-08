#pragma once
#include "CommonAttributes.h"
#include "MainAttributes.h"
class Circle;
class Rectangle;

class Shape
{
private:
	void copy(const Shape&);
protected:
	CommonAttributes commonAttr;
	String text;
	void setCommonAttr(const String& text);
public:
	Shape(const String& text = "");
	Shape(const Shape&);
	virtual Shape* clone();
	virtual Shape& operator=(const Shape&); 

	virtual bool fitsInCircle(const Circle&) const = 0;
	virtual bool fitsInRect(const Rectangle&) const = 0;
	virtual void translateCoordinates(long int, long int) = 0;

	virtual Attribute getAttribute(const String&) const = 0;
	virtual Vector<Attribute> getCommonAttributes() const = 0;
	virtual Vector<Attribute> getMainAttributes() const = 0;

	virtual String getText() const = 0;
	virtual void print() const = 0;
	virtual String getType() const = 0;
};

