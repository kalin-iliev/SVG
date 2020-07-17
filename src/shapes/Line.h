#ifndef LINE_HEADER_INCLUDED
#define LINE_HEADER_INCLUDED

#include "Point2D.h"
#include "Shape.h"
class Rectangle;
class Circle;

class Line : public Shape
{
public:
	Shape* clone() const;
	Line(const Vector<Attribute>& attributes);

	bool fitsInRectangle(const Rectangle&) const; 
	bool fitsInCircle(const Circle&) const;

	void translateCoordinates(int x, int y);
	String getSVGDefinition() const;
	void print() const;

private:
	Line(const Line& other);
};

#endif