#include "SVGShapesManager.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

void SVGShapesManager::printAttributes(const AttributeInfo currentAttributes[], int size) const {
	for (int i = 0; i < size; i++)
	{
		std::cout << currentAttributes[i].attributeName;
		if (i != size - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

void SVGShapesManager::printAllowedShapes() const {
	std::cout << "Allowed shapes: circle, rectangle, line" << std::endl;
}

void SVGShapesManager::printAllowedAttributes() const {
	std::cout << "Allowed attributes: " << std::endl;
	std::cout << "Common attributes: ";
	printAttributes(commonAttributes, commonAttrSize);
	std::cout << std::endl;
	std::cout << "Main attributes: " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "circle: ";
	printAttributes(circleAttributes, circleAttrSize);
	std::cout << "rectangle: ";
	printAttributes(rectAttributes, rectAttrSize);
	std::cout << "line: ";
	printAttributes(lineAttributes, lineAttrSize);
}

void SVGShapesManager::printCommands() const {
	std::cout << "Svg shapes command: " << std::endl;
	std::cout << "shapes   prints all allowed shapes" << std::endl;
	std::cout << "attributes prints all allowed attributes" << std::endl;
	std::cout << "print   prints all currently read shapes" << std::endl;
	std::cout << "create <option> - circle, rectangle, line   creates shapes from the ones allowed" << std::endl;
	std::cout << "within <option> - circle or rectangle   check if any shape is in the <option>" << std::endl;
	std::cout << "erase <n>  erase shape on position n" << std::endl;
	std::cout << "translate [<n>]  translate shape <n> or all shapes if <n> is empty" << std::endl;
}

void SVGShapesManager::appendString(String& dest, const String& buffer, int appendSize) {
	if (!appendSize) return;
	String newString(appendSize);
	for (int i = 0; i < appendSize; i++)
		newString[i] = buffer[i];
	dest += newString;
}

bool SVGShapesManager::isLetter(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int SVGShapesManager::attributesCount(const String& text) {
	int cnt = 0;
	int length = 0;
	while (text[length]) {
		while (text[length] && !isLetter(text[length])) {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length]) {
			++cnt;                              // if there is a word, count it
		}
		while (text[length] && (isLetter(text[length]) || text[length] == '-')) {           // skip to the end of the word
			++length;
		}
		while (text[length] && !isLetter(text[length]))
		{
			if (text[length] == '-')
			{
				++length;
				while (text[length] && text[length] != '=')
				{
					++length;
				}
				++length;
			}
			if (text[length] == '=')
			{
				++length;
				while (text[length] && text[length] != '"')
					++length;
			}
			else if (text[length] == '"')
			{
				++length;
				while (text[length] && text[length] != '"')
				{
					++length;
				}
				++length;
			}
			else {
				++length;
			}
		}
	}
	return cnt;
}

int SVGShapesManager::extractAttributes(const String& text, Vector<String>& attributes) {
	int countAttr = attributesCount(text);
	int length = 0;
	for (int i = 0; i < countAttr; i++)
	{
		while (text[length] && !isLetter(text[length])) {  // skip letters to the beginning of a word
			++length;
		}
		if (text[length]) {                            // if there is a word, count it
			int start = length;
			int attrSize = 0;
			int currentSize = 0;
			while (text[length] && (isLetter(text[length]) || text[length] == '-')) {         // skip to the end of the word
				++attrSize;
				++length;
			}

			while (text[length] && !isLetter(text[length]))
			{
				if (text[length] == '-')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '=')
					{
						++attrSize;
						++length;
					}
					++length;
				}
				if (text[length] == '=')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '"')
						++length;
				}
				else if (text[length] == '"')
				{
					++attrSize;
					++length;
					while (text[length] && text[length] != '"')
					{

						if (text[length] != ' ' && text[length] != '\n' && text[length] != '\t')
							++attrSize;
						++length;
					}
					++attrSize;
					++length;
				}
				else {
					++length;
				}
			}

			char* attr = new char[attrSize + 1];
			bool hasAssignmentChar = false;
			for (int p = start; p < length && currentSize < attrSize; p++) {
				if ((isLetter(text[p]) || (text[p] != ' ' && text[p] != '\n' && text[p] != '\t')) && currentSize < attrSize + 1)
				{
					if (hasAssignmentChar) {
						if (text[p] != '"')
							continue;
						hasAssignmentChar = false;
					}
					if (text[p] == '=')
						hasAssignmentChar = true;

					attr[currentSize++] = text[p];
				}
			}

			attr[attrSize] = '\0';
			String newString(attr);
			attributes.push_back(newString);
			delete[] attr;
		}
	}

	return countAttr;
}

int SVGShapesManager::findAttributeNameIndex(const String& attrName, const Vector<String>& attributes) {
	unsigned size = attributes.size();
	for (unsigned i = 0; i < size; i++)
		if (attributes[i] == attrName)
			return i;
	return -1;
}

Shape* SVGShapesManager::createShapeFromText(const String& text) {
	Vector<String> attributes;
	int countWords = extractAttributes(text, attributes);

	Shape* newShape = nullptr;
	if (findAttributeNameIndex("circle", attributes) > -1)
		newShape = new Circle(text);
	else if (findAttributeNameIndex("rect", attributes) > -1)
		newShape = new Rectangle(text);
	else if (findAttributeNameIndex("line", attributes) > -1)
		newShape = new Line(text);

	return newShape;
}

void SVGShapesManager::saveFile(std::ofstream& svgFile) {
	String xmlTag = "<?xml version=\"1.0\" standalone=\"no\"?>";
	String doctypeTag = "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
	String openSvgTag = "<svg>";
	String closingSvgTag = "</svg>";
	svgFile << xmlTag << '\n';
	svgFile << doctypeTag << '\n';
	svgFile << openSvgTag << '\n';
	for (int i = 0; i < size; i++)
	{
		svgFile << shapes[i]->getSVGDefinition() << '\n';
	}
	svgFile << closingSvgTag << '\n';
}

bool SVGShapesManager::validateContent(std::ifstream& svgFile) {
	bool isFileValid = true;

	if (svgFile.is_open())
	{
		char c;
		int countConsequentOpenTags = 0;
		int countConsequentCloseTags = 0;
		while ((c = svgFile.get()) && !svgFile.eof())
		{
			if (c == '<' && c != '>')
			{
				++countConsequentOpenTags;
				countConsequentCloseTags = 0;
			}
			if (c == '>' && c != '<')
			{
				++countConsequentCloseTags;
				if (!countConsequentOpenTags)
				{
					std::cout << "There is a syntax error in the file." << std::endl;
					isFileValid = false;
					break;
				}
				countConsequentOpenTags = 0;
			}

			if (countConsequentCloseTags >= 2 || countConsequentOpenTags >= 2)
			{
				std::cout << "There is a syntax error in the file." << std::endl;
				isFileValid = false;
				break;
			}
		}
	}

	if (!isFileValid)
	{
		svgFile.close();
		throw String("The file content is not valid. Try to edit the content correctly.");
	}
	svgFile.close();
	return true;
}

bool SVGShapesManager::readFile(std::ifstream& svgFile) {
	if (svgFile.is_open())
	{
		char c;
		String fileLine;
		int pos = 0;
		const int BUFFER_SIZE = 30;
		String buffer(BUFFER_SIZE);
		bool foundOpenBrace = false;
		bool foundFirstSvg = false;
		while ((c = svgFile.get()) && !svgFile.eof())
		{
			if (c == '<' && c != '>')
				foundOpenBrace = true;
			if (foundOpenBrace) {
				buffer[pos++] = c;
				if (pos == BUFFER_SIZE)
				{
					fileLine += buffer;
					pos = 0;
				}
			}

			if (c == '>')
			{
				appendString(fileLine, buffer, pos);

				if (fileLine.contains("svg") && !fileLine.contains('!'))
				{
					if (!foundFirstSvg)
						foundFirstSvg = true;
					else
						foundFirstSvg = false;
				}
				else
				{
					if (foundFirstSvg)
					{
						Shape* newShape = createShapeFromText(fileLine);
						if(newShape)
							addShape(newShape);
						delete newShape;
					}
				}
				foundOpenBrace = false;
				fileLine = String();
				pos = 0;
			}
		}
	}
	svgFile.close();
	return true;
}

void SVGShapesManager::clean() {
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
			delete shapes[i];
	}
	delete[] shapes;
	shapes = nullptr;
}

bool SVGShapesManager::resizeShapes(unsigned newCapacity) {
	if (newCapacity <= size) return false;

	Shape** newShapes = new Shape * [newCapacity];
	if (!newShapes)
		return false;

	for (int i = 0; i < size; i++)
		newShapes[i] = shapes[i];
	delete[] shapes;
	shapes = newShapes;
	capacity = newCapacity;
	return true;
}

bool SVGShapesManager::shiftShapes(unsigned index)
{
	if (!(index >= 1 && index <= size))
		return false;
	for (int i = index - 1; i < size - 1; i++)
	{
		delete shapes[i];
		shapes[i] = shapes[i + 1]->clone();
	}
	return true;
}

bool SVGShapesManager::addShape(Shape* shape)
{
	if(size >= capacity - 1) {
		if (!resizeShapes(capacity * 2))
		{
			std::cout << "Unsuccessful adding of shape. Try again." << std::endl;
			return false;
		}
	}
	shapes[size++] = shape->clone();
	return true;
}

bool SVGShapesManager::removeShape(unsigned index) {
	try {
		if (!shiftShapes(index))
		{
			throw (String("There is no figure at index ") + String(std::to_string(index).c_str()));
		}
		int middleCapacity = (capacity / 2) + (capacity % 2);
		Shape* currentShape = shapes[index - 1]->clone();
		if (size - 1 < middleCapacity - 1)
		{
			if (!resizeShapes(capacity / 2))
			{
				//reversing shapes back to previous state
				for (int i = size - 1; i > index - 1; i--) {
					delete shapes[i];
					shapes[i] = shapes[i - 1]->clone();
				}
				delete shapes[index - 1];
				shapes[index - 1] = currentShape->clone();
				delete currentShape;
				throw String("The figure couldn't be removed.");
			}
		}
		size--;
		delete currentShape;
		return true;
	}
	catch (const String& error) {
		throw error;
	}
}

void SVGShapesManager::translateShapes(long int x, long int y, unsigned id) {
	if (!(id >= 1 && id <= size))
	{
		std::cout << "You must choose a shape with valid id number." << std::endl;
		return;
	}
	std::cout << "Successfully translated shape at index " << id << std::endl;
	shapes[id - 1]->translateCoordinates(x, y);
}

void SVGShapesManager::translateShapes(long int x, long int y) {
	for(int i = 0; i < size; i++)
		shapes[i]->translateCoordinates(x, y);
	std::cout << "Successfully translated all shapes." << std::endl;
}

void SVGShapesManager::containedInCircle(const Circle& other) const {
	bool containedShapes = false;
	for (int i = 0; i < size; i++)
	{
		if (shapes[i]->fitsInCircle(other)) {
			containedShapes = true;
			std::cout << i + 1 << ". ";
			shapes[i]->print();
		}
	}
	if (!containedShapes)
	{
		std::cout << "There are no shapes contained within ";
		other.print();
	}	
}

void SVGShapesManager::containedInRect(const Rectangle& other) const {
	bool containedShapes = false;
	for (int i = 0; i < size; i++)
	{
		if (shapes[i]->fitsInRect(other)) {
			containedShapes = true;
			std::cout << i + 1 << ". ";
			shapes[i]->print();
		}
	}
	if (!containedShapes)
	{
		std::cout << "There are no shapes contained within ";
		other.print();
	}
}

void SVGShapesManager::printShapes() const {
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1 << ". ";
		shapes[i]->print();
	}
}

void SVGShapesManager::loadSVGFile(const String& path) {
	try {
		std::ifstream svgFile(path.toCharArray());
		std::ifstream svgIsCorrect(path.toCharArray());
		validateContent(svgIsCorrect);
		
		shapes = new Shape * [DEFAULT_CAPACITY];
		capacity = DEFAULT_CAPACITY;
		size = 0;
		readFile(svgFile);
	}
	catch (std::bad_alloc& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const char* error) {
		std::cout << error << std::endl;
	}
}

SVGShapesManager::SVGShapesManager() {
	shapes = new Shape * [DEFAULT_CAPACITY];
	size = 0;
	capacity = DEFAULT_CAPACITY;
}

SVGShapesManager::~SVGShapesManager() {
	this->clean();
}

void SVGShapesManager::removeShapes() {
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
			delete shapes[i];
		delete[] shapes;
		shapes = new Shape * [DEFAULT_CAPACITY];
		size = 0;
		capacity = DEFAULT_CAPACITY;
	}
}

void SVGShapesManager::saveShapes(std::ofstream& svgFile) {
	saveFile(svgFile);
}
