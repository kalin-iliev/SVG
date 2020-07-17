#include "Helpers.h"

bool isLetter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isLetterOrNumber(char c)
{
    return isLetter(c) || (c >= '0' && c <= '9');
}

int numberOfDigits(int x)
{
    if (x >= 0 && x < 10)
    {
        return 1;
    }
    int number = 0;
    while(x)
    {
        ++number;
        x /= 10;
    }
}

String intToString(int x)
{
    int stringSize = numberOfDigits(x);
    String result(stringSize + 1);
    for (int i = stringSize-1; i >= 0; --i)
    {
        result[i] = '0' + x % 10;
        x /= 10;
    }

    result[stringSize] = '\0';
    return result;
}


bool isInt(char c)
{
    return c >= '0' && c <= '9';
}

bool isInt(const String& string)
{
    int startIndex = 0;
    if (string[0] == '-')
    {
        startIndex = 1;
    }
    for (int i = startIndex; i < string.size(); ++i)
    {
        if (!isInt(string[i]))
        {
            return false;
        }
    }
    return true;
}