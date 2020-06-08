#pragma once
#include "String.h"
#include "Vector.h"
#include "Attribute.h"
#include "CommonAttributes.h"

class MainAttributes : public CommonAttributes
{
private:
	void setCurrentAttributes(const String& text, const String& shapeType);
public:
	MainAttributes() {}
	MainAttributes(const String& text, const String& shapeType);
	MainAttributes(const MainAttributes& other);
	MainAttributes& operator=(const MainAttributes& other);
};
