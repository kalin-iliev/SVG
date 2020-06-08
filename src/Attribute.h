#pragma once
#include "String.h"
class Attribute
{
private:
	String name;
	String value;
	bool isValid;
	bool isInt;
private:
	bool isAttributeLetter(char c);
	String getAttrValue(const String& attribute);
	String getAttrName(const String& attribute);
	bool isLetterInt(char c);
	bool isStringInt(const String& currentStr);
public:
	Attribute();
	Attribute(const String& attrName, const String& value, bool valueIsInt = false);
	Attribute(const String& attribute, bool valueIsInt = false);
	Attribute(const Attribute& secondAttr);
	Attribute& operator=(const Attribute& secondAttr);
	Attribute& operator=(const String& attrValue);

	String getName() const { return name; }
	String getValue() const { return value; }
	bool isAttrInt() const { return isInt; }

	void setValue(const String& attrValue);
	String toString() const { return (name.size() > 0 && value.size() > 0) ? getName() + '=' + '"' + getValue() + '"' : ""; }

	friend std::ostream& operator << (std::ostream& out, const Attribute& currentAttr);
	friend std::istream& operator >> (std::istream& in, Attribute& currentAttr);
	bool operator==(const Attribute& other) const { return name == other.name && value == other.value; }
	bool operator!=(const Attribute& other) const { return !(*this == other); }

	operator bool() const { return isValid; }
};

