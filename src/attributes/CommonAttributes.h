#pragma once
#include "Vector.h"
#include "String.h"
#include "Attribute.h"
#include "Constants.h"

class CommonAttributes
{
protected:
	Vector<String> allowedAttributes;
	Vector<String> allowedIntAttributes;
	Vector<Attribute> currentAttributes;
protected:
	bool isAttributeLetter(char c);
	virtual void setCurrentAttributes(const String& text);
	int attributesCount(const String& text);
	int extractAttributes(const String& text, Vector<String>& attributes);
	int findAttribute(const String& attrName, const Vector<String>& extractedAttributes);
	int findAttributeName(const String& attrName, const Vector<String>& attributeNames);
	void pushInAllowedAttributes(const AttributeInfo elements[], int size);
public:
	CommonAttributes() {}
	CommonAttributes(const String& text);
	CommonAttributes(const CommonAttributes& other);
	CommonAttributes& operator=(const CommonAttributes& other);

	void printAllowedAttributes() const;
	Vector<String> getAllowedAttributes() const;
	
	void printAllowedIntAttributes() const;
	Vector<String> getAllowedIntAttributes() const;

	void printCurrentAttributes() const;
	Vector<Attribute> getCurrentAttributes() const;

	int findAllowedAttribute(const String& attr) const;
	int findAllowedIntAttribute(const String& attr) const;
	int findCurrentAttribute(const String& attr) const;
	Attribute getAttribute(unsigned index) const;
	Attribute operator[](unsigned index) const;
	void setAttrValue(const String& currentAttr, const String& newValue);
	void setAttrValue(unsigned currentAttrIndex, const String& newValue);
	String getText() const;
};

