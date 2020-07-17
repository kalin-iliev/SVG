#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

#include "SVGShapesManager.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "Helpers.h"

void SVGShapesManager::printAttributes(const AttributeInfo currentAttributes[], int size) const
{
	for (int i = 0; i < size; i++)
	{
		std::cout << currentAttributes[i].attributeName;
		if (i != size - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

void SVGShapesManager::printAllowedShapes() const
{
	std::cout << "Allowed shapes: circle, rectangle, line" << std::endl;
}

void SVGShapesManager::printAllowedAttributes() const
{
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

void SVGShapesManager::printCommands() const
{
	std::cout << "Svg shapes command: " << std::endl;
	std::cout << "shapes   prints all allowed shapes" << std::endl;
	std::cout << "attributes prints all allowed attributes" << std::endl;
	std::cout << "print   prints all currently read shapes" << std::endl;
	std::cout << "create <option> - circle, rectangle, line   creates shapes from the ones allowed" << std::endl;
	std::cout << "within <option> - circle or rectangle   check if any shape is in the <option>" << std::endl;
	std::cout << "erase <n>  erase shape on position n" << std::endl;
	std::cout << "translate [<n>]  translate shape <n> or all shapes if <n> is empty" << std::endl;
}

int SVGShapesManager::extractAttributes(const String& text, Vector<Attribute>& attributes)
{
	int textIndex = 0;
	int attributesCount = 0;
	while(text[textIndex])
	{
		while (text[textIndex] && !isLetterOrNumber(text[textIndex]))
		{
			++textIndex;
		}
		if (text[textIndex])
		{
			++attributesCount;
			int attributeStart = textIndex;
			while (text[textIndex] && isLetter(text[textIndex]))
			{
				++textIndex;
			}

			if (text[textIndex] == '=' && text[textIndex+1] == '\"')
			{
				textIndex += 2;
				do
				{
					++textIndex;					
				}while(text[textIndex] && isLetterOrNumber(text[textIndex]));
				++textIndex;
			}

			int attributeSize = textIndex - attributeStart;
			char* attributeText = new char[attributeSize+1];
			strncpy(attributeText, text.toCharArray() + attributeStart, attributeSize);
			attributeText[attributeSize] = '\0';

			Attribute newAttribute(attributeText);
			attributes.push_back(newAttribute);
			delete[] attributeText;
		}
	}

	return attributesCount;
}

int SVGShapesManager::findAttributeNameIndex(const String& attrName, const Vector<Attribute>& attributes)
{
	unsigned size = attributes.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (attributes[i].getName() == attrName)
		{
			return i;
		}
	}
	return -1;
}

Shape* SVGShapesManager::createShapeFromText(const String& text)
{
	Vector<Attribute> attributes;
	extractAttributes(text, attributes);

	Shape* newShape = nullptr;
	if (findAttributeNameIndex("circle", attributes) > -1)
	{
		newShape = new Circle(attributes);
	}
	else if (findAttributeNameIndex("rect", attributes) > -1)
	{
		newShape = new Rectangle(attributes);
	}
	else if (findAttributeNameIndex("line", attributes) > -1)
	{
		newShape = new Line(attributes);
	}

	return newShape;
}

void SVGShapesManager::saveFile(std::ofstream& svgFile)
{
	String xmlTag = "<?xml version=\"1.0\" standalone=\"no\"?>";
	String doctypeTag = "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
	String openSvgTag = "<svg>";
	String closingSvgTag = "</svg>";
	svgFile << xmlTag << '\n';
	svgFile << doctypeTag << '\n';
	svgFile << openSvgTag << '\n';
	for (int i = 0; i < shapes.size(); i++)
	{
		svgFile << shapes[i]->getSVGDefinition() << '\n';
	}
	svgFile << closingSvgTag << '\n';
}

bool SVGShapesManager::validateContent(std::ifstream& svgFile)
{
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

bool SVGShapesManager::readFile(std::ifstream& svgFile)
{
	if (svgFile.is_open())
	{
		char c;
		String fileLine;
		bool foundOpenBrace = false;
		bool foundFirstSvg = false;
		while ((c = svgFile.get()) && !svgFile.eof())
		{
			if (c == '<' && c != '>')
			{
				foundOpenBrace = true;
			}
			if (foundOpenBrace)
			{
				fileLine += c;
			}

			if (c == '>')
			{
				if (fileLine.contains("svg") && !fileLine.contains('!'))
				{
					if (!foundFirstSvg)
					{
						foundFirstSvg = true;
					}
					else
					{
						foundFirstSvg = false;
					}
				}
				else
				{
					if (foundFirstSvg)
					{
						Shape* newShape = createShapeFromText(fileLine);
						if(newShape)
						{
							addShape(newShape);
							delete newShape;
						}
					}
				}
				foundOpenBrace = false;
				fileLine = String();
			}
		}
	}
	svgFile.close();
	return true;
}

void SVGShapesManager::clean()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
}

bool SVGShapesManager::addShape(const Shape* shape)
{
	shapes.push_back(shape->clone());
	return true;
}

bool SVGShapesManager::removeShape(unsigned index)
{
	try
	{
		shapes.remove(index);
		return true;
	}
	catch (const String& error)
	{
		return false;
	}
}

void SVGShapesManager::translateShapes(int x, int y, unsigned id)
{
	if (!(id >= 1 && id <= shapes.size()))
	{
		std::cout << "You must choose a shape with valid id number." << std::endl;
		return;
	}
	
	shapes[id - 1]->translateCoordinates(x, y);
	std::cout << "Successfully translated shape at index " << id << std::endl;
}

void SVGShapesManager::translateShapes(int x, int y)
{
	for(int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->translateCoordinates(x, y);
	}

	std::cout << "Successfully translated all shapes." << std::endl;
}

void SVGShapesManager::containedInCircle(const Circle& other) const
{
	bool containedShapes = false;
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->fitsInCircle(other))
		{
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

void SVGShapesManager::containedInRect(const Rectangle& other) const
{
	bool containedShapes = false;
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->fitsInRectangle(other))
		{
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

void SVGShapesManager::printShapes() const
{
	for (int i = 0; i < shapes.size(); i++)
	{
		std::cout << i + 1 << ". ";
		shapes[i]->print();
	}
}

void SVGShapesManager::loadSVGFile(const String& path)
{
	try
	{
		std::ifstream svgFile(path.toCharArray());
		std::ifstream svgIsCorrect(path.toCharArray());
		validateContent(svgIsCorrect);
		
		readFile(svgFile);
	}
	catch (std::bad_alloc& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}
}

SVGShapesManager::SVGShapesManager() {}

SVGShapesManager::~SVGShapesManager()
{
	this->clean();
}

void SVGShapesManager::removeShapes()
{
	if (shapes.size() > 0)
	{
		for (int i = 0; i < shapes.size(); i++)
		{
			delete shapes[i];
		}
	}
}

void SVGShapesManager::saveShapes(std::ofstream& svgFile)
{
	saveFile(svgFile);
}

int SVGShapesManager::getSize() const
{
	return shapes.size();
}

SVGShapesManager::operator bool() const 
{ 
	return shapes.size(); 
}

SVGShapesManager::operator int() const 
{ 
	return shapes.size(); 
}