#include "InputHandler.h"

void InputHandler::loadFile(SVGShapesManager& currentManager, const String& filePath)
{
	if (currentOpenFile)
	{
		throw String("Currently a file is open.");
	}
	if (!isPathValid(filePath, "svg"))
	{
		throw String("Invalid file format.");
	}

	currentOpenFile = filePath;
	currentManager.loadSVGFile(filePath);
}

void InputHandler::saveFile(SVGShapesManager& currentManager)
{
	if (!currentOpenFile)
	{
		throw String("Currently there is no open file to save into.");
	}

	std::ofstream currentFile(currentOpenFile.toCharArray(), std::ios::trunc);
	currentManager.saveShapes(currentFile);
	currentFile.close();
}

void InputHandler::saveFileAs(SVGShapesManager& currentManager, const String& filePath)
{
	if (!currentOpenFile)
	{
		throw String("There are currently no shapes to save.");
	}
	if (!isPathValid(filePath, "svg"))
	{
		throw String("File name should be in valid format.");
	}

	std::ofstream currentFile(filePath.toCharArray(), std::ios::trunc);
	currentManager.saveShapes(currentFile);
	currentFile.close();
}

String InputHandler::getRealParamValue(const String& parameter)
{
	int equalIndex = parameter.firstIndexOf('=');
	if (equalIndex > -1)
	{
		int parameterSize = parameter.size();
		int parameterValueSize = parameterSize - equalIndex - 1;
		String newString(parameterValueSize);
		int currentSize = 0;
		for (int i = equalIndex + 1; i < parameterSize; i++)
		{
			newString[currentSize++] = parameter[i];
		}
		return newString;
	}
	return parameter;
}

bool InputHandler::hasShapes(const SVGShapesManager& currentManager)
{
	return currentManager.getSize() > 0;
}

String InputHandler::getFileName(const String& path)
{
	int pathSize = path.size();
	int rightSlashIndex = path.lastIndexOf('/');
	int leftSlashIndex = path.lastIndexOf('\\');
	int splitSlashIndex = 0;
	if (rightSlashIndex > -1)
	{
		splitSlashIndex = rightSlashIndex + 1;
	}
	else if (leftSlashIndex > -1)
	{
		splitSlashIndex = leftSlashIndex + 1;
	}

	int strSize = pathSize - splitSlashIndex;
	if (!strSize)
	{
		return String();
	}

	String newString(pathSize - splitSlashIndex);
	int currentSize = 0;
	for (int i = splitSlashIndex; i < pathSize; i++)
	{
		newString[currentSize++] = path[i];
	}

	return newString;
}

bool InputHandler::isFilenameValid(const String& filePath, const String& extension)
{
	int indexExtension = filePath.lastIndexOf('.') + 1;
	int pathSize = filePath.size();
	if (indexExtension == -1)
	{
		return false;
	}

	int strSize = pathSize - indexExtension;
	if (strSize != extension.size())
	{
		return false;
	}

	String newString(strSize);
	int currentSize = 0;
	for (int i = indexExtension; i < pathSize; i++)
	{
		newString[currentSize++] = filePath[i];
	}
	return newString == extension;
}

bool InputHandler::isPathValid(const String& path, const String& extension)
{
	std::ifstream svgFile(path.toCharArray());
	String fileName = getFileName(path);
	if (!svgFile.is_open())
	{
		svgFile.close();
		if (isFilenameValid(fileName, extension))
		{
			std::fstream createFile(path.toCharArray(), std::ios::out);
			createFile.close();
			svgFile.open(path.toCharArray());
			if (!svgFile.is_open())
			{
				throw String("The file is invalid.");
			}
			svgFile.close();
		}
	}
	if(svgFile.is_open())
	{
		svgFile.close();
	}

	if (!isFilenameValid(fileName, extension))
	{
		throw String("The filename is invalid.");
	}

	return true;
}

int InputHandler::findParameterIndex(const String& parameterName, const Vector<String>& parameters)
{
	int size = parameters.size();
	int index = -1;
	
	for (int i = 0; i < size; i++)
	{
		String currentParameter = parameters[i];
		if (currentParameter.beginsWith(parameterName))
		{
			int indexEqual = currentParameter.firstIndexOf('=');
			if (indexEqual > -1 && indexEqual != parameterName.size())
			{
				return index;
			}
			else
			{
				return i;
			}
		}
	}

	return -1;
}

unsigned InputHandler::parameterOccurences(const String& paramName, const Vector<String>& parameters)
{
	int index = -1;
	int count = 0;
	for (int i = 0; i < parameters.size(); i++)
	{
		String currentPar = parameters[i];
		if (currentPar.beginsWith(paramName))
		{
			int indexEqual = currentPar.firstIndexOf('=');
			if (indexEqual > -1 && indexEqual == paramName.size())
			{
				count++;
			}
			else if (indexEqual == -1)
			{
				count++;
			}
		}
	}

	return count;
}

void InputHandler::translate(SVGShapesManager& currentManager, const Vector<String>& translateParameters)
{
	int size = translateParameters.size();
	if (!(size >= 1 && size <= 3))
	{
		throw String("Not enough parameters for following command.");
	}
	if (parameterOccurences("vertical", translateParameters) > 1)
	{
		throw String("There are repeating parameters.");
	}
	if (parameterOccurences("horizontal", translateParameters) > 1)
	{
		throw String("There are repeating parameters.");
	}

	int xTranslateIndex = findParameterIndex("horizontal", translateParameters);
	int yTranslateIndex = findParameterIndex("vertical", translateParameters);
	int indexShape = -1;

	if (xTranslateIndex == -1 && yTranslateIndex == -1)
	{
		throw String("There are no integers to translate coordinates.");
	}

	if (isInt(translateParameters[size - 1]))
	{
		indexShape = size - 1;
	}

	String xCoord = "", yCoord = "";
	if (xTranslateIndex > -1)
	{
		getRealParamValue(translateParameters[xTranslateIndex]);
	}
	if (yTranslateIndex > -1)
	{
		getRealParamValue(translateParameters[yTranslateIndex]);
	}

	String index = "";
	if (indexShape > -1)
	{
		getRealParamValue(translateParameters[indexShape]);
	}

	translateShapes(currentManager, xCoord, yCoord, index);
}

void InputHandler::translateShapes(SVGShapesManager& currentManager, const String& xCoord, const String& yCoord, const String& index)
{
	if (xCoord)
	{
		if (!isInt(xCoord))
		{
			throw String("Wrong entered value for x translation.");
		}
	}
	if (yCoord)
	{
		if (!isInt(yCoord))
		{
			throw String("Wrong entered value for y translation.");
		}
	}
	if (index)
	{
		if (!isInt(index))
		{
			throw String("Wrong entered value for index.");
		}
	}

	int xTranslate = xCoord.toInt();
	int yTranslate = yCoord.toInt();
	int indexShape = index.toInt();

	if (xTranslate != 0 || yTranslate != 0)
	{
		if (indexShape > -1)
		{
			currentManager.translateShapes(xTranslate, yTranslate, indexShape);
		}
		else
		{
			currentManager.translateShapes(xTranslate, yTranslate);
		}
	}
}

void InputHandler::isWithin(const SVGShapesManager& currentManager, const Vector<String>& shapeAttributes)
{
	if (!currentOpenFile)
	{
		throw String("Currently there is no open file.");
	}

	int size = shapeAttributes.size();
	if (!size)
	{
		throw String("There is no shape provided.");
	}

	String shapeType = shapeAttributes[0];
	Vector<String> attributes;
	attributes.remove(0);
	if (shapeType == "circle")
	{
		Circle* exampleCircle = (Circle*)getShapeFromAttributes(Shape::ShapeType::CircleType, shapeAttributes);
		isWithinCircle(currentManager, *exampleCircle);
	}
	else if (shapeType == "rect")
	{
		Rectangle* exampleCircle = (Rectangle*)getShapeFromAttributes(Shape::ShapeType::RectangleType, shapeAttributes);
		isWithinRectangle(currentManager, *exampleCircle);
	}
	else
	{
		throw String("The current shape cannot be compared to.");
	}
}

void InputHandler::isWithinCircle(const SVGShapesManager& currentManager, const Circle& exampleCircle) const
{
	currentManager.containedInCircle(exampleCircle);
}

void InputHandler::isWithinRectangle(const SVGShapesManager& currentManager, const Rectangle& exampleRectangle) const
{
	currentManager.containedInRect(exampleRectangle);
}

Shape* InputHandler::getShapeFromAttributes(const Shape::ShapeType shapeType, const Vector<String>& attributes)
{
	Vector<Attribute> parsedAttributes;
	if (shapeType == Shape::ShapeType::CircleType)
	{
		parsedAttributes = parseShapeAttributes(shapeType, circleAttributes, circleAttrSize, attributes);
		return new Circle(parsedAttributes);
	}
	else if (shapeType == Shape::ShapeType::RectangleType)
	{
		parsedAttributes = parseShapeAttributes(shapeType, rectAttributes, rectAttrSize, attributes);
		return new Rectangle(parsedAttributes);
	}
	else if (shapeType == Shape::ShapeType::LineType)
	{
		parsedAttributes = parseShapeAttributes(shapeType, lineAttributes, lineAttrSize, attributes);
		return new Line(parsedAttributes);
	}
	else
	{
		throw String("The shape type is unrecognised.");
	}
}

Vector<Attribute> InputHandler::parseShapeAttributes(const Shape::ShapeType shapeType, const AttributeInfo currentAttributes[], int currentAttrSize,
									 const Vector<String>& attributes)
{
	if (attributes.size() != currentAttrSize)
	{
		throw String("The shape needs the required attributes.");
	}

	Vector<Attribute> parsedAttributes;

	for (int i = 0; i < currentAttrSize; i++)
	{
		String attrValue = attributes[i];
		bool attrValueIsInt = currentAttributes[i].isInt;
		Attribute currentAttr = Attribute(currentAttributes[i].attributeName, attrValue, attrValueIsInt);
		parsedAttributes.push_back(currentAttr);
	}

	return parsedAttributes;
}

void InputHandler::createShape(SVGShapesManager& currentManager, const Vector<String>& shapeAttributes)
{
	if (!currentOpenFile)
	{
		throw String("Currently there is no open file.");
	}

	Shape* newShape = nullptr;
	int size = shapeAttributes.size();
	if (!size)
	{
		throw String("There is no shape provided.");
	}

	String shapeType = shapeAttributes[0];
	Vector<String> attributes = shapeAttributes;

	if (shapeType == "circle")
	{
		newShape = getShapeFromAttributes(Shape::ShapeType::CircleType, shapeAttributes);
	}
	else if (shapeType == "rect")
	{
		newShape = getShapeFromAttributes(Shape::ShapeType::RectangleType, shapeAttributes);
	}
	else if (shapeType == "line")
	{
		newShape = getShapeFromAttributes(Shape::ShapeType::LineType, shapeAttributes);
	}
	else
	{
		throw String("Unsupported shape type.");
	}
	
	currentManager.addShape(newShape);

	delete newShape;
}

void InputHandler::eraseShape(SVGShapesManager& currentManager, String indexParameter)
{
	if (!currentOpenFile)
	{
		throw String("Currently there is no open file.");
	}
	if (!isInt(indexParameter))
	{
		throw String("The index parameter is invalid.");
	}

	currentManager.removeShape(indexParameter.toInt());
	std::cout << "Successfully removed shape at this index." << std::endl;
}

void InputHandler::closeFile() 
{
	if (!this->currentOpenFile)
	{
		throw String("Currently there is no file open.");
	}

	this->currentOpenFile = String();
}

bool InputHandler::isFileOpen() const
{
	return this->currentOpenFile;
}