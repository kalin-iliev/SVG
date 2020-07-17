#include "Attribute.h"
#include "Helpers.h"

String Attribute::getAttrValue(const String& attribute)
{
	int equalSignIndex = attribute.firstIndexOf('=');
	if (attribute.numberOfOccurrences('"') != 2 || equalSignIndex < 0)
	{
		return String("");
	}

	int attributeIndex = equalSignIndex + 1;
	while(attributeIndex < attribute.size() && !isLetterOrNumber(attribute[attributeIndex]))
	{
		++attributeIndex;
	}

	String attributeValue;
	for (; attributeIndex < attribute.size() && isLetterOrNumber(attribute[attributeIndex]); ++attributeIndex)
	{
		attributeValue += attribute[attributeIndex];
	}

	return attributeValue;
}

String Attribute::getAttrName(const String& attribute)
{
	if (!attribute.contains('='))
	{
		return String(attribute);
	}

	int attributeIndex = 0;
	while(attributeIndex < attribute.size() && !isLetter(attribute[attributeIndex]))
	{
		++attributeIndex;
	}

	String attributeName;
	for (; attributeIndex < attribute.size() && isLetter(attribute[attributeIndex]); ++attributeIndex)
	{
		attributeName += attribute[attributeIndex];
	}

	return attributeName;
}

Attribute::Attribute() {
	name = value = "";
	isValid = false;
	isValueInt = false;
}

Attribute::Attribute(const String& attrName, const String& attrValue, bool valueIsInt) {
	if (valueIsInt && !isInt(attrValue))
	{
		name = value = String();
		isValueInt = isValid = false;
	}
	else {
		name = attrName;
		value = attrValue;
		if (!name.size())
		{
			name = value = String();
			isValueInt = isValid = false;
		}
		else
		{
			isValid = true;
			isValueInt = valueIsInt;
		}
	}
}

Attribute::Attribute(const String& attribute, bool valueIsInt)
{
	if (!attribute.size())
	{
		name = value = "";
		isValid = true;
		isValueInt = false;
	}
	else {
		name = getAttrName(attribute);
		value = getAttrValue(attribute);
		if (!name.size())
		{
			name = value = String();
			isValid = false;
			isValueInt = false;
		}
		else
		{
			if (valueIsInt && !isInt(value))
			{
				name = value = String();
				isValid = false;
			}
			else
			{
				isValid = true;
				isValueInt = true;
			}
		}
	}
}

Attribute::Attribute(const Attribute& attribute) {
	if (this != &attribute)
	{
		name = attribute.name;
		value = attribute.value;
		isValid = attribute.isValid;
	}
}

Attribute& Attribute::operator=(const Attribute& attribute) {
	if (this != &attribute)
	{
		name = attribute.name;
		value = attribute.value;
		isValid = attribute.isValid;
	}
	return *this;
}

Attribute& Attribute::operator=(const String& attrValue) {
	if (!(value == attrValue))
		value = attrValue;
	return *this;
}

void Attribute::setValue(const String& newValue) {
	if (isValueInt && !isInt(newValue))
		return;
	value = newValue;
}

std::ostream& operator << (std::ostream& out, const Attribute& currentAttr)
{
	out << (currentAttr.name + '=' + '"' + currentAttr.value + '"');
	return out;
}

std::istream& operator >> (std::istream& in, Attribute& currentAttr)
{
	String currentName;
	String currentValue;
	in >> currentName >> currentValue;
	String attr = (currentName + '=' + '"' + currentValue + '"');
	currentAttr = attr;
	return in;
}

String Attribute::toString() const
{
	if (name.size() > 0 && value.size() > 0)
	{
		return getName() + "=\"" + getValue() + "\"";
	}
	else
	{
		return "";
	}
}

bool Attribute::operator==(const Attribute& other) const
{
	return this->name == other.name && this->value == other.value;
}

bool Attribute::operator!=(const Attribute& other) const 
{
	return !(*this == other);
}
