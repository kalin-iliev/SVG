#ifndef ATTRIBUTE_INFO_HEADER_INCLUDED
#define ATTRIBUTE_INFO_HEADER_INCLUDED

struct AttributeInfo
{
    String attributeName;
    bool isInt;
    String getName() const { return attributeName; };
    bool intValid() const { return isInt; };
};

#endif