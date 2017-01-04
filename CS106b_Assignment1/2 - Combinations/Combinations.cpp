/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
//2#include "simpio.h"

using namespace std;

int combinationFunction(int n, int k);

int main() {
    
    int n,k;
    cout << "Integer value for n: " << endl;
    cin >> n;
    cout << "Integer value for k: " << endl;
    cin >> k;
    cout << "The combination function evaluates to: " << combinationFunction(n, k) << endl;
    
    return 0;
}

int combinationFunction(int n, int k)   {
    if(k == 0)
        return 1;
    else if (n < k)
        return 0;
    else
        return combinationFunction(n-1, k-1) + combinationFunction(n-1,k);
}