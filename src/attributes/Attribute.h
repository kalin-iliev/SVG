#pragma once
#include "String.h"
class Attribute
{
private:
	String name;
	String value;
	bool isValid;
	bool isValueInt;
private:
	String getAttrValue(const String&);
	String getAttrName(const String&);

public:
	Attribute();
	Attribute(const String& attributeName, const String& attributeValue, bool isValueInt = false);
	Attribute(const String& attribute, bool valueIsInt = false);
	Attribute(const Attribute& secondAttr);
	Attribute& operator=(const Attribute& secondAttr);
	Attribute& operator=(const String& attrValue);

	String getName() const { return name; }
	String getValue() const { return value; }
	bool isAttrInt() const { return isValueInt; }

	void setValue(const String& attrValue);
	String toString() const;

	friend std::ostream& operator << (std::ostream& outputStream, const Attribute& currentAttr);
	friend std::istream& operator >> (std::istream& inputStream, Attribute& currentAttr);
	bool operator==(const Attribute& other) const;
	bool operator!=(const Attribute& other) const;

	operator bool() const { return isValid; }
};

