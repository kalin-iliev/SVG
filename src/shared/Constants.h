#pragma once
#include "String.h"

struct AttributeInfo {
	String attributeName;
	bool isInt;
	AttributeInfo(const String& text = "", bool _isInt = false) {
		attributeName = String(text);
		isInt = _isInt;
	};
	String getName() const { return attributeName; };
	bool intValid() const { return isInt; };
};

const int commonAttrSize = 2;
const AttributeInfo commonAttributes[commonAttrSize] = { { "fill" }, { "stroke" } };

const int circleAttrSize = 3;
const AttributeInfo circleAttributes[circleAttrSize] = { {"cx", true}, {"cy", true}, {"r", true} };
//for further extendabiility
//const int extraCircleSize;
//AttributeInfo extraCircleAttributes[extraCircleSize];

const int rectAttrSize = 4;
const AttributeInfo rectAttributes[rectAttrSize] = { {"x", true}, {"y", true}, {"width", true}, {"height", true} };
//for further extendability
//const int extraRectSize;
//AttributeInfo extraRectAttributes[extraRectSize];

const int lineAttrSize = 4;
const AttributeInfo lineAttributes[lineAttrSize] = { {"x1", true}, {"y1", true}, {"x2", true}, {"y2", true} };
//for further extendability
//const int extraLineSize;
//AttributeInfo extraLineAttributes[extraLineSize];
