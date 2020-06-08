#include "SVGTest.h"

void SVGTest::testPrintShapes()
{
	try {
		std::cout << "Testing print of shapes...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		currentManager.printShapes();
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testCreateValidShape()
{
	try {
		std::cout << "Testing create shape circle 10 10 10 yellow ...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		String currentShapeText = "<circle cx=\"10\" cy=\"10\" r=\"10\" fill=\"yellow\" />";
		Shape* currentShape = new Circle(currentShapeText);
		currentManager.addShape(currentShape);
		delete currentShape;
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testCreateInvalidShapeWithInvalidName()
{
	Shape* currentShape = nullptr;
	try {
		std::cout << "Testing create shape circless 10 10 10 yellow with unknown name...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		String currentShapeText = "<circless cx=\"10\" cy=\"10\" r=\"10\" fill=\"yellow\" />";
		currentShape = new Circle(currentShapeText);
		currentManager.addShape(currentShape);
		delete currentShape;
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		std::cout << "Test passed successfully." << std::endl;
	}
}

void SVGTest::testCreateInvalidShapeWithInvalidAttributes()
{
	Shape* currentShape = nullptr;
	try {
		std::cout << "Testing create shape circle 10 10 yellow without radius...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		String currentShapeText = "<circless cx=\"10\" cy=\"10\" fill=\"yellow\" />";
		currentShape = new Circle(currentShapeText);
		currentManager.addShape(currentShape);
		delete currentShape;
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		std::cout << "Test passed successfully." << std::endl;
	}
}

void SVGTest::testEraseValidShape()
{
	try {
		std::cout << "Testing erase shape with valid index...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		std::cout << "Removing shape with index 1 ...." << std::endl;
		currentManager.removeShape(1);
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testEraseInvalidShape()
{
	try {
		std::cout << "Testing erase shape with invalid index...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		std::cout << "Removing shape with index 100 ...." << std::endl;
		currentManager.removeShape(100);
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		std::cout << "Test passed successfully." << std::endl;
	}
}

void SVGTest::testTranslateAll()
{
	try {
		std::cout << "Testing translate all shapes with x = 10 and y = 10...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		currentManager.translateShapes(10, 10);
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testTranslateValidIndex()
{
	try {
		std::cout << "Testing translate shape with index 1 with x = 10 and y = 10...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		currentManager.translateShapes(10, 10, 1);
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testTranslateInvalidIndex()
{
	try {
		std::cout << "Testing translate shape with invalid index 100 with x = 10 and y = 10...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		currentManager.translateShapes(10, 10, 100);
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testWithinShape()
{
	try {
		std::cout << "Testing within shape circle 10 10 10...." << std::endl;
		SVGShapesManager currentManager;
		currentManager.loadSVGFile("figures.svg");
		String currentShapeText = "<circle cx=\"10\" cy=\"10\" r=\"10\" />";
		Circle currentCircle(currentShapeText);
		currentManager.containedInCircle(currentCircle);
		std::cout << "Test passed successfully." << std::endl;
	}
	catch (const String& error) {
		assert(false);
	}
}

void SVGTest::testAllFunctions()
{
	std::cout << "Testing all supported functions...." << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	testPrintShapes();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testCreateValidShape();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testCreateInvalidShapeWithInvalidName();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testCreateInvalidShapeWithInvalidAttributes();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testEraseValidShape();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testEraseInvalidShape();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testTranslateAll();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testTranslateValidIndex();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testTranslateInvalidIndex();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
	testWithinShape();
	std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
}
