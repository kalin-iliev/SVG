#ifndef HELPERS_HEADER_INCLUDED
#define HELPERS_HEADER_INCLUDED

#include "String.h"

bool isLetter(char c);
bool isLetterOrNumber(char c);
bool isUpperCase(char c);
bool isLowerCase(char c);

int numberOfDigits(int x);
bool isInt(char c);
bool isInt(const String&);

String intToString(int x);

#endif