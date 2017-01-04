/*
 * File: WordLadder.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"

using namespace std;

int main() {
    string startWord;
    string destWord;
    cout << "Enter start word (RETURN to quit): ";
    cin >> startWord;
    cout << "Enter destination word (RETURN to quit): ";
    cin >> destWord;
    int startWordLength = startWord.size();
    int destWordLength = destWord.size();
    bool found = false;
    
    if (!startWord.empty() && (startWordLength == destWordLength)) {
        Lexicon english("EnglishWords.dat");
        Queue<Vector<string> > queue;
        Vector<string> startLadder;
        Set<string> usedWordSet;
        usedWordSet.add(startWord);
        startLadder.add(startWord);
        queue.enqueue(startLadder);
        
        Vector<string> dequeuedLadder;
        while (!queue.isEmpty())    {
            dequeuedLadder = queue.dequeue();
            string lastWordInQueue = dequeuedLadder.get(dequeuedLadder.size() - 1);
            if(lastWordInQueue == destWord)   {
                found = true;
                cout << "Found ladder:";
                cout.flush();
                for(string word : dequeuedLadder)   {
                    cout << " " + word;
                    cout.flush();
                }
                break;
            }
            
            for (string word : english) {
                if(word.size() == startWordLength && (!usedWordSet.contains(word)))  {
                    int equalPos = 0;
                    for (int i = 0; i < startWordLength; i++)   {
                        if(word.at(i) == lastWordInQueue.at(i))   {
                            equalPos++;
                        }
                    }
                    
                    if(equalPos == startWordLength - 1) {
                        usedWordSet.add(word);
                        Vector<string> newLadder = dequeuedLadder;
                        newLadder.add(word);
                        queue.enqueue(newLadder);
                    }
                }
            }
        }
    }
    if (!found) cout << "No ladder exists." << endl;
    return 0;
}
