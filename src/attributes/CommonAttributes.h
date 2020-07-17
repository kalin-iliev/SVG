#pragma once
#include "Vector.h"
#include "String.h"
#include "Attribute.h"
#include "Constants.h"

class CommonAttributes
{
protected:
	Vector<String> allowedAttributes;
	Vector<Attribute> currentAttributes;

	bool isLetter(char c); // TODO extract to utils
	virtual void setCurrentAttributes(const String& text);
	int extractAttributes(const String& text, Vector<String>& attributes);
	int findAttributeIndex(const String& attrName, const Vector<String>& extractedAttributes); // TODO extract to utils & change extractedAttributes to array of attributes?
	int findAttributeNameIndex(const String& attrName, const Vector<String>& attributeNames); // TODO extract to utils
	void addAllowedAttributes(const AttributeInfo allowedAttributes[], int allowedAttributesCount);

public:	// TODO move public before protected
	CommonAttributes() {}
	CommonAttributes(const String& text);
	CommonAttributes(const CommonAttributes& other);
	CommonAttributes& operator=(const CommonAttributes& other);

	void printAllowedAttributes() const;
	Vector<String> getAllowedAttributes() const;
	

	void printCurrentAttributes() const;
	Vector<Attribute> getCurrentAttributes() const;

	int indexOfAllowedAttribute(const String& attr) const;
	int indexOfCurrentAttribute(const String& attr) const;
	Attribute getAttribute(unsigned index) const;
	Attribute operator[](unsigned index) const;
	Attribute& operator[](unsigned index);
	void setAttributeValue(const String& currentAttr, const String& newValue);
	void setAttributeValue(unsigned currentAttrIndex, const String& newValue);
	String currentAttributesToString() const;
};

