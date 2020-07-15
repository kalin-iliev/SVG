#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "String.h"
#include <fstream>

const int DEFAULT_CAPACITY = 10;

class SVGShapesManager
{
	Shape** shapes; 
	int size;
	int capacity;
private:
	void clean();
	void appendString(String& dest, const String& buffer, int appendSize);
	bool resizeShapes(unsigned newCapacity);
	bool isLetter(char c);
	int attributesCount(const String&);
	int extractAttributes(const String& text, Vector<String>& attributes);
	int findAttributeNameIndex(const String& attrName, const Vector<String>& attributes);
	bool shiftShapes(unsigned index);
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
	bool addShape(Shape*);
	bool removeShape(unsigned id);
	void translateShapes(long int x, long int y, unsigned id);
	void translateShapes(long int x, long int y);
	void containedInCircle(const Circle&) const;
	void containedInRect(const Rectangle&) const;
	void printShapes() const;
	void printCommands() const;
	void printAllowedShapes() const;
	void printAllowedAttributes() const;

	int getSize() const { return size; }
	int getCapacity() const { return capacity; }

	operator bool() const { return size; }
	operator int() const { return size; }
};

