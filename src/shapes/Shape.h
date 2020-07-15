#pragma once
#include "CommonAttributes.h"
#include "MainAttributes.h"
class Circle;
class Rectangle;

class Shape
{
	// TODO move public methods first
	// TODO probably remove common and main attributes - use one to rule them all
private:
	void copy(const Shape&);
protected:
	CommonAttributes commonAttributes;
	String svgDefinition;
	void setCommonAttributes(const String& svgDefinition);
public:
	Shape(const String& svgDefinition = "");
	Shape(const Shape&);
	virtual Shape* clone();
	virtual Shape& operator=(const Shape&);

	virtual bool fitsInCircle(const Circle&) const = 0;
	virtual bool fitsInRect(const Rectangle&) const = 0;
	virtual void translateCoordinates(int x, int y) = 0;

	virtual Attribute getAttribute(const String&) const = 0;
	virtual Vector<Attribute> getCommonAttributes() const = 0;
	virtual Vector<Attribute> getMainAttributes() const = 0;

	virtual String getSVGDefinition() const = 0; // TODO implement it!
	virtual void print() const = 0;
	virtual String getType() const = 0; // TODO change type to enum and put it here
};

