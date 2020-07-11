#pragma once
#include "SVGShapesManager.h"
#include <cassert>

class SVGTest
{
public:
	SVGTest() = delete;

	static void testPrintShapes();
	static void testCreateValidShape();
	static void testCreateInvalidShapeWithInvalidName();
	static void testCreateInvalidShapeWithInvalidAttributes();
	static void testEraseValidShape();
	static void testEraseInvalidShape();
	static void testTranslateAll();
	static void testTranslateValidIndex();
	static void testTranslateInvalidIndex();
	static void testWithinShape();
	static void testAllFunctions();
};

