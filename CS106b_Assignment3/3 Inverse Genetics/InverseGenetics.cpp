/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string rnaStrain, string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();
int counter = 0;

int main() {
    /* Load the codon map. */
    string protein;
    Map<char, Set<string> > codons = loadCodonMap();
    cout << "Enter a protein (string of aminoacids): ";
    getline(cin, protein);
    listAllRNAStrandsFor("", protein, codons);
    cout << counter <<" different ways to encode " << protein << " exist" << endl;
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;
    
    /* The current codon / protein combination. */
    string codon;
    char protein;
    
    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        //cout << codon << endl;
        //cout << protein << endl;
        result[protein] += codon;
    }
    
    return result;
}

void listAllRNAStrandsFor(string rna_strain, string protein, Map<char, Set<string> >& codons)  {
    Set<string> codon = codons[protein.at(0)];
    if (protein.length() == 1)  {
        for (string ac : codon) {
            cout << rna_strain << ac << endl;
            counter++;
        }
        
    }
    else if (protein.length() > 1)  {
        string rna_strain_temp = rna_strain;
        for (string ac: codon)  {
            rna_strain_temp += ac +  ", ";
            listAllRNAStrandsFor(rna_strain_temp, protein.substr(1), codons);
            rna_strain_temp = rna_strain;
        }
    }
}
