/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);

int main() {
    int street = getInteger("Enter the street number: ");
    int avenue = getInteger("Enter the avenue number: ");
    
    cout << "Number of ways: " << numPathsHome(street, avenue) << endl;
    return 0;
}

int numPathsHome(int street, int avenue)    {
    
    if (street >  1 && avenue > 1)  {
        return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
    }
    else if (street > 1 && avenue == 1) {
        return numPathsHome(street - 1, avenue);
    }
    else if (street == 1 && avenue > 1) {
        return numPathsHome(street, avenue - 1);
    }
    else if (street == 1 && avenue == 1)
        return 1;
}
