#ifndef ATTRIBUTES_CONTAINER_HEADER_INCLUDED
#define ATTRIBUTES_CONTAINER_HEADER_INCLUDED

#include "Vector.h"
#include "String.h"
#include "Attribute.h"
#include "Constants.h"

class AttributesContainer
{
public:
    AttributesContainer() {}
    AttributesContainer(const Vector<Attribute>& attributes);

    void printAllowedAttributes() const;
    void printAttributes() const;

    int indexOfAllowedAttribute(const String& attribute) const;
    int indexOfAttribute(const String& attribute) const;

    Attribute getAttributeByIndex(unsigned index) const;
    Attribute operator[](unsigned index) const;
    Attribute& operator[](unsigned index);

    void setAttributeValue(const String& attribute, const String& newValue);
    void setAttributeValueByIndex(unsigned currentAttrIndex, const String& newValue);

    String toString() const;

private:
    Vector<Attribute> allowedAttributes;
    Vector<Attribute> attributes;

    void setAttributes(const Vector<String>& attributes);
    int findAttributeIndex(const String& attributeName, const Vector<String>& extractedAttributes); // TODO extract to utils & change extractedAttributes to array of attributes?
    int findAttributeNameIndex(const String& attributeName, const Vector<String>& attributeNames); // TODO extract to utils
    void addAllowedAttributes(const AttributeInfo allowedAttributes[], int allowedAttributesCount);
};

#endif