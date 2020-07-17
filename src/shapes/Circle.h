#ifndef CIRCLE_HEADER_INCLUDED
#define CIRCLE_HEADER_INCLUDED

#include "Shape.h"
#include "Attribute.h"
#include "Helpers.h"
#include "Point2D.h"

class Circle : public Shape
{
public:
	Shape* clone() const;
	Circle(const Vector<Attribute>& attributes);

	bool fitsInRectangle(const Rectangle&) const;
	bool fitsInCircle(const Circle&) const;
	void translateCoordinates(Point2D translationPoint);

	String getSVGDefinition() const;
	void print() const;

private:
	Circle(const Circle&);
};

#endif