#pragma once
#include "SVGShapesManager.h"
#include "Constants.h"
#include "Attribute.h"

//filter for the input and connection between ConsoleHelpers and ShapesManager
class InputHandler
{
private:
	String currentOpenFile;
public:
	void loadFile(SVGShapesManager& currentManager, const String& path);
	void saveFile(SVGShapesManager& currentManager);
	void saveFileAs(SVGShapesManager& currentManager, const String& path);
	void isWithin(const SVGShapesManager& currentManager, const Vector<String>& shapeAttributes);
	void translate(SVGShapesManager& currentManager, const Vector<String>& translateParameters);
	void createShape(SVGShapesManager& currentManager, const Vector<String>& currentShapeAttributes);
	void eraseShape(SVGShapesManager& currentManager, String indexParameter);
	void closeFile();
private:
	String createShapeText(const String& shapeType, const Vector<String>& attributes);
	String createShapeText(const String& shapeType, const AttributeInfo currentAttributes[], int attributeInfoSize, const Vector<String>& attributes);
	void isWithinRectangle(const SVGShapesManager& currentManager, const Rectangle& exampleRectangle) const;
	void isWithinCircle(const SVGShapesManager& currentManager, const Circle& exampleCircle) const;
	void translateShapes(SVGShapesManager& currentManager, const String& xCoord, const String& yCoord, const String& index);
	bool isPathValid(const String& path, const String& extension);
	String getFileName(const String& path);
	bool isFilenameValid(const String& filename, const String& extension = "svg");
	bool isInt(const String& text);
	bool isCharInt(char c);
	String getRealParamValue(const String& parameter);
	int findParameter(const String& paramName, const Vector<String>& parameters);
	unsigned parameterOccurence(const String& paramName, const Vector<String>& parameters);
public:
	bool hasShapes(const SVGShapesManager&);
	bool isFileOpen() const { return currentOpenFile; }
};

