/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "tokenscanner.h"
#include "console.h"
#include "simpio.h"
using namespace std;

bool isWord(string token);
bool isEndOfSentence(string token);
int numberOfSyllables(string token);

int main() {
    
    ifstream infile;
    string token;
    string prevToken;
    int wordCounter = 0;
    int sentenceCounter = 0;
    int syllableCounter = 0;
    
    while(true) {
        cout << "Enter name: ";
        string s = getLine();
        infile.open(s.c_str());
        if (!infile.fail())
            break;
        cout << "Could not open file. Please try again." << endl;
        infile.clear();
    }
    
    TokenScanner scanner(infile);
    scanner.ignoreWhitespace();
    
    while (scanner.hasMoreTokens()) {
        prevToken = scanner.nextToken();
        token = scanner.nextToken();
        if(token == "'")    {
            string str = prevToken + "'" + scanner.nextToken();
            
            if (isWord(prevToken)){
                wordCounter++;
                syllableCounter += numberOfSyllables(str);
            }
        }
        else    {
            if (isWord(prevToken))  {
                wordCounter++;
                syllableCounter += numberOfSyllables(prevToken);
            }
            if (isWord(token)) {
                wordCounter++;
                syllableCounter += numberOfSyllables(token);
            }
            if (isEndOfSentence(prevToken) || isEndOfSentence(token))
                sentenceCounter++;
        }
    }
    infile.close();
    
    // If a file does not have any words, pretend that it is one word to avoid division by zero
    if (wordCounter == 0)   wordCounter = 1;
    // If a file does not have any sentences, pretend that it is one sentence to avoid division by zero
    if (sentenceCounter == 0)   sentenceCounter = 1;
    
    //Final Flesch-Kincaid Score
    double grade = -15.59 + (0.39 * wordCounter / sentenceCounter) + (11.8 * syllableCounter / wordCounter);
    cout << "Anzahl an Silben: " << syllableCounter << endl;
    cout << "Anzahl an Woerter: " << wordCounter << endl;
    cout << "Anzahl an Saetze: " << sentenceCounter << endl;
    cout << "Flesch-Kincaid Grade Level: " << grade << endl;
    
    return 0;
}

bool isWord(string token)   {

    if(("a" <= token && "z" >= token) || ("A" <= token && "Z" >= token))
        return true;
    else
        return false;
}

bool isEndOfSentence(string token)   {
    
    if(token == "." || token == "!" || token == "?")
        return true;
    else
        return false;
}

int numberOfSyllables(string token) {
    
    int syl = 0;
    
    for (int i = 0; i < token.length() - 1; i++)    {
            
        if ((token.at(i) == 'a' || token.at(i) == 'e' || token.at(i) == 'i' || token.at(i) == 'o' || token.at(i) == 'u') && (token.at(i+1) != 'a' || token.at(i+1) != 'e' || token.at(i+1) != 'i' || token.at(i+1) != 'o' || token.at(i+1) != 'u')) {
            
             syl++;
            
        }
        
    }
    
    if (syl > 0) return syl;
    else return 1;
}
