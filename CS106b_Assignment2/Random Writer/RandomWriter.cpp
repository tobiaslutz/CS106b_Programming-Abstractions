/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"

using namespace std;

void parseInputText(ifstream &infile);
void extractSeeds (string &text);
void buildMarkovModel (string seed, char state);
void generateRandomText();
string findStartSeed();
char findNextRandChar(string s);
Map<string,Vector<char> > markovModelTransitions; // key: seed, value: characters which follow a seed
int order; // length of a seed

int main() {
    ifstream infile;
    while(true) {
        cout << "Enter the source text: ";
        string fileName = getLine();
        infile.open(fileName.c_str());
        if (!infile.fail())
            break;
        cout << "Unable to open file. Please try again." << endl;
        infile.clear();
    }
    
    while(true) {
        cout << "Enter the Markov order [1-10]: ";
        order = getInteger();
        if (order >= 1 && order <= 10)
            break;
        cout << "Illegal integer format. Please try again." << endl;
    }
    
    parseInputText(infile);
    infile.close();
    
    /*cout << "Final result: " << endl;
    for (string s: markovModelTransitions)  {
        cout << s << ": " << endl;
        for(int i = 0; i < markovModelTransitions.get(s).size(); i++)  {
            cout << markovModelTransitions.get(s).get(i)<< " " << endl;
        }
        cout << endl;
    }*/
    
    generateRandomText();
    
    
    return 0;
}

void parseInputText (ifstream &infile)  {
    cout << "Analyzing input text..." << endl << endl;
    string text;
    while(infile.good()) {
        text += infile.get();
    }
    cout << "Input text read: " << text << endl;
    extractSeeds(text);
}

void extractSeeds (string &text)    {
    cout << "Building Markov Model..." << endl << endl;
    for(int i = 0; i < text.length() - order - 1; i++)  {
        string seed = text.substr(i,order);
        //cout << "Seed: " << seed << endl;
        char state = text.at(i + order);
        buildMarkovModel(seed, state);
    }
    cout << "Markov Model completed..." << endl << endl;
}

void buildMarkovModel (string seed, char state) {
    Vector<char> stateVector;
    if(markovModelTransitions.containsKey(seed))    {
        
        stateVector = markovModelTransitions.get(seed);
    }
    stateVector.add(state);
    markovModelTransitions.put(seed, stateVector);
}

void generateRandomText()   {
    
    string startSeed = findStartSeed();
    cout << "Start seed: " << startSeed << endl;
    
    for (int i = 0; i < 200 / order; i++)  {
        char nextRandChar = findNextRandChar(startSeed);
        string out = startSeed + nextRandChar;
        cout << out;
        cout.flush();
        if(order == 1)
            startSeed = nextRandChar;
        else
            startSeed = out.substr(1);
    }
}

string findStartSeed()  {
    
    int seedMaxOccurence = 0;
    string startSeed;
    for (string s: markovModelTransitions)    {
        int seedOccurence = markovModelTransitions.get(s).size();
        if(seedOccurence > seedMaxOccurence)    {
            seedMaxOccurence = seedOccurence;
            startSeed = s;
        }
    }
    return startSeed;
}

char findNextRandChar(string s)   {
    int r = randomInteger(0, markovModelTransitions.get(s).size() - 1);
    //cout << "random number: " << r << endl;
    return markovModelTransitions.get(s).get(r);
}