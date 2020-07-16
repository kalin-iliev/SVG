#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "String.h"
#include "Vector.h"
#include <fstream>

class SVGShapesManager
{
	Vector<Shape*> shapes;
private:
	void clean();
	int extractAttributes(const String& text, Vector<String>& attributes);
	int findAttributeNameIndex(const String& attrName, const Vector<String>& attributes);
	bool validateContent(std::ifstream& svgFile); 
	bool readFile(std::ifstream& svgFile);
	void saveFile(std::ofstream&);
	Shape* createShapeFromText(const String& text);
	void printAttributes(const AttributeInfo currentAttributes[], int size) const;
public:
	SVGShapesManager();
	~SVGShapesManager();
	void loadSVGFile(const String& path);
	void saveShapes(std::ofstream&);
	void removeShapes();
	bool addShape(const Shape*);
	bool removeShape(unsigned id);
	void translateShapes(long int x, long int y, unsigned id);
	void translateShapes(long int x, long int y);
	void containedInCircle(const Circle&) const;
	void containedInRect(const Rectangle&) const;
	void printShapes() const;
	void printCommands() const;
	void printAllowedShapes() const;
	void printAllowedAttributes() const;

	int getSize() const { return shapes.size(); }

	operator bool() const { return shapes.size(); }
	operator int() const { return shapes.size(); }
};

