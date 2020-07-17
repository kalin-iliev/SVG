#ifndef SVG_SHAPES_MANAGER_HEADER_INCLUDED
#define SVG_SHAPES_MANAGER_HEADER_INCLUDED

#include <fstream>

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "String.h"
#include "Vector.h"
#include "Point2D.h"

class SVGShapesManager
{
public:
	SVGShapesManager();
	~SVGShapesManager();

	void loadSVGFile(const String& path);
	void saveShapes(std::ofstream&);

	void removeShapes();
	bool addShape(const Shape*);
	bool removeShape(unsigned id);

	void translateShapes(Point2D point, unsigned id);
	void translateShapes(Point2D point);

	void containedInCircle(const Circle&) const;
	void containedInRect(const Rectangle&) const;

	void printShapes() const;
	void printCommands() const;
	void printAllowedShapes() const;
	void printAllowedAttributes() const;

	int getSize() const;

	operator bool() const;
	operator int() const;

private:
	Vector<Shape*> shapes;

	void clean();

	int extractAttributes(const String& text, Vector<Attribute>& attributes);
	int findAttributeNameIndex(const String& attrName, const Vector<Attribute>& attributes);

	bool validateContent(std::ifstream& svgFile);

	bool readFile(std::ifstream& svgFile);
	void saveFile(std::ofstream&);

	Shape* createShapeFromText(const String& text);

	void printAttributes(const AttributeInfo currentAttributes[], int size) const;
};

#endif
