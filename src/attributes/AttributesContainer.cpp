#include "AttributesContainer.h"

AttributesContainer::AttributesContainer(const Vector<Attribute>& attributes)
{
    this->attributes = attributes;
}

void AttributesContainer::printAllowedAttributes() const
{
    for (int i = 0; i < this->allowedAttributes.size(); i++)
    {
        std::cout << this->allowedAttributes[i];
        if (i != this->allowedAttributes.size() - 1)
        {
            std::cout << ", ";
        }
    }
}

void AttributesContainer::printAttributes() const
{
    for (int i = 0; i < this->attributes.size(); i++)
    {
        std::cout << this->attributes[i].getValue();
        if (i != this->attributes.size() - 1)
        {
            std::cout << ' ';
        }
    }
}

int AttributesContainer::indexOfAllowedAttribute(const String& attributeName) const
{
    for (int i = 0; i < this->allowedAttributes.size(); i++)
    {
        if (this->allowedAttributes[i].getName() == attributeName)
        {
            return i;
        }
    }
    return -1;
}

int AttributesContainer::indexOfAttribute(const String& attributeName) const
{
    for (int i = 0; i < this->attributes.size(); i++)
    {
        if (this->attributes[i].getName() == attributeName)
        {
            return i;
        }
    }
    return -1;
}

Attribute AttributesContainer::getAttributeByIndex(unsigned index) const
{
    if (index >= this->attributes.size())
    {
        throw String("The index is out of the range of the attributes.");
    }

    return this->attributes[index];
}

Attribute AttributesContainer::operator[](unsigned index) const
{
    if (index >= this->attributes.size())
    {
        throw String("The index is out of the range of the attributes.");
    }
    return this->attributes[index];
}

Attribute& AttributesContainer::operator[](unsigned index)
{
    if (index >= this->attributes.size())
    {
        throw String("The index is out of the range of the attributes.");
    }
    return this->attributes[index];
}

void AttributesContainer::setAttributeValue(const String& attribute, const String& newValue)
{
    int attributeIndex = indexOfAttribute(attribute);
    if (attributeIndex == -1)
    {
        throw String("No attribute found.");
    }
    
    this->attributes[attributeIndex].setValue(newValue);
}

void AttributesContainer::setAttributeValueByIndex(unsigned attributeIndex, const String& newValue)
{
    if (attributeIndex < 0 || attributeIndex >= this->attributes.size())
    {
        throw String("Invalid attribute index.");
    }

    this->attributes[attributeIndex].setValue(newValue);
}

String AttributesContainer::toString() const
{
    String result;
    for (int i = 0; i < this->attributes.size(); i++)
    {
        result += this->attributes[i].toString();
        if (i != this->attributes.size() - 1)
            result += ' ';
    }
    return result;
}