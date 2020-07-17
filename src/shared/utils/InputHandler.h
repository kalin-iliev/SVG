#ifndef INPUT_HANDLER_HEADER_INCLUDED
#define INPUT_HANDLER_HEADER_INCLUDED

#include "SVGShapesManager.h"
#include "Constants.h"
#include "Attribute.h"

//filter for the input and connection between ConsoleHelpers and ShapesManager
class InputHandler
{
public:
	void loadFile(SVGShapesManager& currentManager, const String& path);
	void saveFile(SVGShapesManager& currentManager);
	void saveFileAs(SVGShapesManager& currentManager, const String& path);
	void closeFile();

	bool isFileOpen() const;

	void isWithin(const SVGShapesManager& currentManager, const Vector<String>& shapeAttributes);
	void translate(SVGShapesManager& currentManager, const Vector<String>& translateParameters);

	void createShape(SVGShapesManager& currentManager, const Vector<String>& currentShapeAttributes);
	void eraseShape(SVGShapesManager& currentManager, String indexParameter);
	bool hasShapes(const SVGShapesManager&);
private:
	String currentOpenFile;

	Shape* getShapeFromAttributes(const Shape::ShapeType shapeType, const Vector<String>& attributes);

	Vector<Attribute> parseShapeAttributes(const Shape::ShapeType shapeType, const AttributeInfo currentAttributes[], int attributeInfoSize, const Vector<String>& attributes);
	
	void isWithinRectangle(const SVGShapesManager& currentManager, const Rectangle& exampleRectangle) const;
	void isWithinCircle(const SVGShapesManager& currentManager, const Circle& exampleCircle) const;
	void translateShapes(SVGShapesManager& currentManager, const String& xCoord, const String& yCoord, const String& index);
	
	bool isPathValid(const String& path, const String& extension);
	bool isFilenameValid(const String& filename, const String& extension = "svg");
	String getFileName(const String& path);
	
	String getRealParamValue(const String& parameter);
	int findParameterIndex(const String& paramName, const Vector<String>& parameters);
	unsigned parameterOccurences(const String& paramName, const Vector<String>& parameters);
};

#endif
