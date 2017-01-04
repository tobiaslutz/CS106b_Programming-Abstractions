/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
//#include "console.h"
#include "random.h"

using namespace std;

int main() {
    
    int count_heads = 0;
    int count_trails = 0;
    
    while(true) {
        
        if(randomChance(0.5) == true)   {
            cout << "heads" << endl;
            count_heads++;
            count_trails++;
            
            if(count_heads == 5)    {
                cout << "It took " << count_trails << " flips to get " << count_heads << " consecutive heads." << endl;
                break;
            }
        }
        else    {
            cout << "tails" << endl;
            count_heads = 0;
            count_trails++;
        }
    }
    return 0;
}
