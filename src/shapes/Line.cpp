#include <iostream>
#include <cstring>

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Helpers.h"

Shape* Line::clone() const
{
	return new Line(*this);
}

Line::Line(const Line& other)
{
	this->attributes = other.attributes;
	this->type = Shape::ShapeType::LineType;
}

Line::Line(const Vector<Attribute>& attributes)
	: Shape(attributes)
{
	this->type = Shape::ShapeType::LineType;
}

void Line::translateCoordinates(Point2D translationPoint)
{
	unsigned x1AttributeIndex = attributes.indexOfAttribute("x1");
	unsigned y1AttributeIndex = attributes.indexOfAttribute("y1");
	unsigned x2AttributeIndex = attributes.indexOfAttribute("x2");
	unsigned y2AttributeIndex = attributes.indexOfAttribute("y2");
	if (x1AttributeIndex < 0 || y1AttributeIndex < 0 || x2AttributeIndex < 0 || y2AttributeIndex < 0)
	{
		throw String("Invalid line object attributes. Cannot translate.");
	}

	int x1 = attributes[x1AttributeIndex].getValue().toInt();
	int y1 = attributes[y1AttributeIndex].getValue().toInt();
	Point2D pointA(x1, y1);

	int x2 = attributes[x2AttributeIndex].getValue().toInt();
	int y2 = attributes[y2AttributeIndex].getValue().toInt();
	Point2D pointB(x2, y2);

	pointA += translationPoint;
	pointB += translationPoint;

	String bufferX1 = intToString(pointA.x);
	String bufferX2 = intToString(pointA.y);
	String bufferY1 = intToString(pointB.x);
	String bufferY2 = intToString(pointB.y);
	attributes.setAttributeValue(x1AttributeIndex, bufferX1);
	attributes.setAttributeValue(y1AttributeIndex, bufferY1);
	attributes.setAttributeValue(x2AttributeIndex, bufferX2);
	attributes.setAttributeValue(y2AttributeIndex, bufferY2);
}

String Line::getSVGDefinition() const
{
	String svg("<line ");
	svg += attributes.toString();
	svg += " />";

	return svg;
}

void Line::print() const
{
	std::cout << "line";
	attributes.printAttributes();
	std::cout << std::endl;
}

bool Line::fitsInRectangle(const Rectangle& other) const
{
	int currX1 = getAttribute("x1").getValue().toInt();
	int currY1 = getAttribute("y1").getValue().toInt();
	Point2D pointA(currX1, currY1);

	int currX2 = getAttribute("x2").getValue().toInt();
	int currY2 = getAttribute("y2").getValue().toInt();
	Point2D pointB(currX2, currY2);

	int rectX = other.getAttribute("x").getValue().toInt();
	int rectY = other.getAttribute("y").getValue().toInt();
	Point2D rectanglePoint(rectX, rectY);

	int width = other.getAttribute("width").getValue().toInt();
	int height = other.getAttribute("height").getValue().toInt();

	bool firstPointIsInside = (pointA.x >= rectanglePoint.x && pointA.x <= rectanglePoint.x + width) && 
							  (pointA.y >= rectanglePoint.y && pointA.y <= rectanglePoint.y + height);
	bool secondPointIsInside = (pointB.x >= rectanglePoint.x && pointB.x <= rectanglePoint.x + width) &&
							   (pointB.y >= rectanglePoint.y && pointB.y <= rectanglePoint.y + height);

	return firstPointIsInside && secondPointIsInside;
}

bool Line::fitsInCircle(const Circle& other) const
{
	int currX1 = getAttribute("x1").getValue().toInt();
	int currY1 = getAttribute("y1").getValue().toInt();
	Point2D pointA(currX1, currY1);

	int currX2 = getAttribute("x2").getValue().toInt();
	int currY2 = getAttribute("y2").getValue().toInt();
	Point2D pointB(currX2, currY2);

	int cx = other.getAttribute("cx").getValue().toInt();
	int cy = other.getAttribute("cy").getValue().toInt();
	Point2D center(cx, cy);

	int radius = other.getAttribute("r").getValue().toInt();

	int pointOneDistanceSquared = center.squaredDistanceTo(pointA);
	int pointTwoDistanceSquared = center.squaredDistanceTo(pointB);
	bool firstPointIsInside = pointOneDistanceSquared <= radius * radius;
	bool secondPointIsInside = pointTwoDistanceSquared <= radius * radius;

	return firstPointIsInside && secondPointIsInside;
}