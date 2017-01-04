/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    string text;
    string subsequence;
    cout << "Enter word: ";
    cin >> text;
    cout << "Enter another word: ";
    cin >> subsequence;
    if(isSubsequence(text, subsequence))
        cout << "Subsequence." << endl;
    else
        cout << "No subsequence. " << endl;
    return 0;
}

bool isSubsequence(string text, string subsequence) {
    if(text.size() < subsequence.size())
        return false;
    else if(text[0] == subsequence[0]) {
        if(subsequence.substr(1).length() == 0)
            return true;
        else
            return isSubsequence(text.substr(1), subsequence.substr(1));
    }
    else
        if((subsequence.substr(1).length() == 0) && (text.length() == 1))
            return false;
        else
            return isSubsequence(text.substr(1), subsequence);
}