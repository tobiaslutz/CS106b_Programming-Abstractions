/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
//#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    
    cout << intToString(-12345)<< endl;
    cout << stringToInt("blah") << endl;
    return 0;
}

string intToString(int n)   {
    
    string str = string() + char('0' + abs(n) % 10);
    if (abs(n) / 10 > 0)
        return intToString(n / 10) + str;
    else
        if(n >=0 )
            return str;
        else
            return '-' + str;
    
}

int stringToInt(string str) {
    
    if ((str[0] <= 57) && (str[0] >= 48))   {
        int l = str.length();
    
        if (l > 1)
            return int(char(str[l - 1] - 48)) + 10 * stringToInt(str.substr(0,l - 1));
        else if (l == 1)
            return int(char(str[l - 1] - 48));
    }
    else if(str[0] == '-')  {
        int l = str.length();
    
        if (l > 2)
            return -int(char(str[l - 1] - 48)) + 10 * stringToInt(str.substr(0,l - 1));
        else if (l == 2)
            return -int(char(str[l - 1] - 48));
    }
    else
        cout << "String cannot be converted to an Integer." << endl;
}
