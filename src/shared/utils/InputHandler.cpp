#include "InputHandler.h"

void InputHandler::loadFile(SVGShapesManager& currentManager, const String& path) {
	try {
		if (currentOpenFile)
			throw String("Currently a file is open.");
		isPathValid(path, "svg");
		currentOpenFile = path;
		currentManager.loadSVGFile(path);
	}
	catch (const String& error) {
		throw error;
	}
}

void InputHandler::saveFile(SVGShapesManager& currentManager) {
	try {
		if (!currentOpenFile)
			throw String("Currently there is no open file to save into.");
		std::ofstream currentFile(currentOpenFile.toCharArray(), std::ios::trunc);
		currentManager.saveShapes(currentFile);
		currentFile.close();
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void InputHandler::saveFileAs(SVGShapesManager& currentManager, const String& path) {
	try {
		isPathValid(path, "svg");
		std::ofstream currentFile(path.toCharArray(), std::ios::trunc);
		currentManager.saveShapes(currentFile);
		currentFile.close();
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

String InputHandler::getRealParamValue(const String& currentParameter) {
	int equalIndex = currentParameter.firstIndexOf('=');
	if (equalIndex > -1)
	{
		int parameterSize = currentParameter.size();
		int parameterValueSize = parameterSize - equalIndex - 1;
		String newString(parameterValueSize);
		int currentSize = 0;
		for (int i = equalIndex + 1; i < parameterSize; i++)
			newString[currentSize++] = currentParameter[i];
		return newString;
	}
	return currentParameter;
}

bool InputHandler::hasShapes(const SVGShapesManager& currentManager) {
	return currentManager.getSize() > 0;
}

String InputHandler::getFileName(const String& path) {
	int pathSize = path.size();
	int rightSlashIndex = path.lastIndexOf('/');
	int leftSlashIndex = path.lastIndexOf('\\');
	int splitSlashIndex = -1;
	if (rightSlashIndex > -1)
		splitSlashIndex = rightSlashIndex + 1;
	else if (leftSlashIndex > -1)
		splitSlashIndex = leftSlashIndex + 1;
	else
		splitSlashIndex = 0;
	int strSize = pathSize - splitSlashIndex;
	if (!strSize)
		return String();
	String newString(pathSize - splitSlashIndex);
	int currentSize = 0;
	for (int i = splitSlashIndex; i < pathSize; i++)
		newString[currentSize++] = path[i];
	return newString;
}

bool InputHandler::isFilenameValid(const String& path, const String& extension) {
	int indexExtension = path.lastIndexOf('.') + 1;
	int pathSize = path.size();
	if (indexExtension == -1)
		return false;
	int strSize = pathSize - indexExtension;
	if (strSize != extension.size())
		return false;
	String newString(strSize);
	int currentSize = 0;
	for (int i = indexExtension; i < pathSize; i++)
		newString[currentSize++] = path[i];
	return newString == extension;
}

bool InputHandler::isPathValid(const String& path, const String& extension) {
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
				throw String("The file is invalid.");
			svgFile.close();
		}
	}
	if(svgFile.is_open())
		svgFile.close();

	if (!isFilenameValid(fileName, extension))
		throw String("The filename is invalid.");

	return true;
}

int InputHandler::findParameter(const String& paramName, const Vector<String>& parameters) {
	int size = parameters.size();
	int index = -1;
	
	for (int i = 0; i < size; i++)
	{
		String currentPar = parameters[i];
		if (currentPar.beginsWith(paramName)) {
			int indexEqual = currentPar.firstIndexOf('=');
			if (indexEqual > -1 && indexEqual != paramName.size())
				return index;
			else
				return i;
			return i;
		}
	}

	return index;
}

unsigned InputHandler::parameterOccurence(const String& paramName, const Vector<String>& parameters) {
	int size = parameters.size();
	int index = -1;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		String currentPar = parameters[i];
		if (currentPar.beginsWith(paramName)) {
			int indexEqual = currentPar.firstIndexOf('=');
			if (indexEqual > -1 && indexEqual == paramName.size())
				count++;
			else if (indexEqual == -1)
				count++;
		}
	}

	return count;
}

void InputHandler::translate(SVGShapesManager& currentManager, const Vector<String>& translateParameters) {
	int size = translateParameters.size();
	if (!(size >= 1 && size <= 3))
		throw String("Not enough parameters for following command.");
	if (parameterOccurence("vertical", translateParameters) > 1)
		throw String("There are repeating parameters.");
	if (parameterOccurence("horizontal", translateParameters) > 1)
		throw String("There are repeating parameters.");

	int xTranslateIndex = findParameter("horizontal", translateParameters);
	int yTranslateIndex = findParameter("vertical", translateParameters);
	int indexShape = -1;

	if (xTranslateIndex == -1 && yTranslateIndex == -1)
		throw String("There are no integers to translate coordinates.");

	if (isInt(translateParameters[size - 1])) indexShape = size - 1;

	String xCoord = (xTranslateIndex > -1) ? getRealParamValue(translateParameters[xTranslateIndex]) : "";
	String yCoord = (yTranslateIndex > -1) ? getRealParamValue(translateParameters[yTranslateIndex]) : "";
	String index = (indexShape > -1) ? getRealParamValue(translateParameters[indexShape]) : "";
	translateShapes(currentManager, xCoord, yCoord, index);
}

void InputHandler::translateShapes(SVGShapesManager& currentManager, const String& xCoord, const String& yCoord, const String& index) {
	if (xCoord)
		if (!isInt(xCoord))
			throw String("Wrong entered value for x translation.");
	if (yCoord)
		if (!isInt(yCoord))
			throw String("Wrong entered value for y translation.");
	if (index)
		if (!isInt(yCoord))
			throw String("Wrong entered value for index.");

	long int xTranslate = (xCoord) ? xCoord.toInt() : 0;
	long int yTranslate = (yCoord) ? yCoord.toInt() : 0;
	int indexShape = (index) ? index.toInt() : -1;
	if (xTranslate != 0 || yTranslate != 0)
	{
		if (indexShape > -1)
			currentManager.translateShapes(xTranslate, yTranslate, indexShape);
		else
			currentManager.translateShapes(xTranslate, yTranslate);
	}
}

void InputHandler::isWithin(const SVGShapesManager& currentManager, const Vector<String>& shapeAttributes) {
	try {
		int size = shapeAttributes.size();
		if (!size)
			throw String("There is no shape provided.");
		String shapeType = shapeAttributes[0];
		String shapeText = shapeType;
		Vector<String> attributes = shapeAttributes;
		attributes.remove(0);
		if (shapeType == "circle") {
			shapeText = createShapeText(shapeType, attributes);
			shapeText = '<' + shapeText + " />";
			Circle exampleCircle = Circle(shapeText);
			isWithinCircle(currentManager, exampleCircle);
		}
		else if (shapeType == "rectangle") {
			shapeText = createShapeText(shapeType, attributes);
			shapeText = '<' + shapeText + " />";
			Rectangle exampleCircle = Rectangle(shapeText);
			isWithinRectangle(currentManager, exampleCircle);
		}
		else {
			throw String("The current shape cannot be compared to.");
		}
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void InputHandler::isWithinCircle(const SVGShapesManager& currentManager, const Circle& exampleCircle) const {
	currentManager.containedInCircle(exampleCircle);
}

void InputHandler::isWithinRectangle(const SVGShapesManager& currentManager, const Rectangle& exampleRectangle) const {
	currentManager.containedInRect(exampleRectangle);
}

String InputHandler::createShapeText(const String& shapeType, const Vector<String>& attributes) {
	String currentType = shapeType;
	if (currentType == "circle")
		return createShapeText(currentType, circleAttributes, circleAttrSize, attributes);
	else if (currentType == "rectangle")
		return createShapeText(currentType = "rect", rectAttributes, rectAttrSize, attributes);
	else if (currentType == "line")
		return createShapeText(currentType, lineAttributes, lineAttrSize, attributes);
	else
		throw String("The shape type is unrecognised.");
}

String InputHandler::createShapeText(const String& shapeType, const AttributeInfo currentAttributes[], int currentAttrSize,
	const Vector<String>& attributes) {
	int size = attributes.size();
	String shapeText = shapeType;
	int currentSize = 0;
	int mainAttrSize = size;
	if (currentAttrSize != mainAttrSize)
		throw String("The shape needs the required attributes.");

	for (int i = 0; i < currentAttrSize; i++) {
		String attrValue = attributes[currentSize++];
		bool attrValueIsInt = currentAttributes[i].isInt;
		Attribute currentAttr = Attribute(currentAttributes[i].attributeName, attrValue, attrValueIsInt);
		shapeText += (' ' + currentAttr.toString());
	}

	return shapeText;
}

void InputHandler::createShape(SVGShapesManager& currentManager, const Vector<String>& shapeAttributes) {
	Shape* newShape = nullptr;
	try {
		int size = shapeAttributes.size();
		if (!size)
			throw String("There is no shape provided.");
		int currentSize = 0;
		String shapeType = shapeAttributes[0];
		Vector<String> attributes = shapeAttributes;
		attributes.remove(0); // we remove the type
		attributes.pop(); // we remove the fill/stroke attribute (the last attribute)
		String shapeText = createShapeText(shapeType, attributes);

		if (shapeType == "circle" || shapeType == "rect")
		{
			Attribute fillAttr = Attribute("fill", shapeAttributes[size - 1]);
			shapeText += (' ' + fillAttr.toString());
		}
		else {
			Attribute strokeAttr = Attribute("stroke", shapeAttributes[size - 1]);
			shapeText += (' ' + strokeAttr.toString());
		}
		shapeText = '<' + shapeText + " />";
		
		if (shapeType == "circle")
			newShape = new Circle(shapeText);
		else if (shapeType == "rectangle")
			newShape = new Rectangle(shapeText);
		else if (shapeType == "line")
			newShape = new Line(shapeText);
		currentManager.addShape(newShape);
		delete newShape;
		std::cout << "Successfully created " << shapeType << " (" << currentManager.getSize() << ")" << std::endl;
 	}
	catch (const String& error) {
		delete newShape;
		std::cout << error << std::endl;
	}
}

void InputHandler::eraseShape(SVGShapesManager& currentManager, String indexParameter) {
	try {
		if (!isInt(indexParameter))
			throw String("The index parameter is invalid.");
		currentManager.removeShape(indexParameter.toInt());
		std::cout << "Successfully removed shape at this index." << std::endl;
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void InputHandler::closeFile() {
	currentOpenFile = String();
}

bool InputHandler::isCharInt(char c) {
	return (c >= '0' && c <= '9');
}

bool InputHandler::isInt(const String& text) {
	int size = text.size();
	int start = 0;
	int dashIndex = text.firstIndexOf('-');
	if (dashIndex > -1 && dashIndex != 0)
		return false;
	if (dashIndex > -1) start++;
	for (int i = start; i < size; i++)
	{
		if (!isCharInt(text[i]))
			return false;
	}

	return true;
}