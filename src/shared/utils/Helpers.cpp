#include "Helpers.h"

bool isLetter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isLetterOrNumber(char c)
{
    return isLetter(c) || (c >= '0' && c <= '9');
}