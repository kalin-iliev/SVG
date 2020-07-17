#ifndef RECTANGLE_HEADER_INCLUDED
#define RECTANGLE_HEADER_INCLUDED

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Shape* clone() const;
	Rectangle(const Vector<Attribute>& attributes);

	bool fitsInRectangle(const Rectangle&) const;
	bool fitsInCircle(const Circle&) const;
	void translateCoordinates(int x, int y);

	String getSVGDefinition() const;
	void print() const;

private:
	Rectangle(const Rectangle&);
};

#endif