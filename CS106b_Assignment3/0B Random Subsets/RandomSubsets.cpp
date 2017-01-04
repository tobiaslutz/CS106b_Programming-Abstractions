/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s);
Set<int> randomSubset;

int main() {
    Set<int> startSet;
    for (int i = 0; i < 100; i++)    {
        startSet.add(i);
    }
    
    startSet = randomSubsetOf(startSet);
    foreach(int value in startSet)  {
        cout << value << endl;
    }
    
    return 0;
}

Set<int> randomSubsetOf(Set<int>& s)    {
    
    if (s.isEmpty())
        return s;
    
    bool r = randomChance(0.5);
    int newEl = s.first();
    s-= newEl;
    if(r == true)   {
        Set<int> auxSet;
        auxSet += newEl;
        return auxSet + randomSubsetOf(s);
    }
    else
        return randomSubsetOf(s);
}