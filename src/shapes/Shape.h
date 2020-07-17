#ifndef SHAPE_HEADER_INCLUDED
#define SHAPE_HEADER_INCLUDED

#include "Attribute.h"
#include "AttributesContainer.h"
#include "Point2D.h"

class Circle;
class Rectangle;

class Shape
{
public:
	Shape() {};
	Shape(const Vector<Attribute>& attributes);
	virtual ~Shape() {};
	virtual Shape* clone() const = 0;

	virtual bool fitsInCircle(const Circle&) const = 0;
	virtual bool fitsInRectangle(const Rectangle&) const = 0;
	virtual void translateCoordinates(Point2D translationPoint) = 0;

	Attribute getAttribute(const String& attributeName) const;

	enum ShapeType
	{
		CircleType,
		RectangleType,
		LineType
	};

	virtual String getSVGDefinition() const = 0;
	virtual void print() const = 0;
	ShapeType getType();

protected:
	AttributesContainer attributes;
	ShapeType type;
};

#endif