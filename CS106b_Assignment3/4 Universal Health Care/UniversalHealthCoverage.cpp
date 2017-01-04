/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

Set<string> generateTestCities();
Vector< Set<string> > generateTestLocations();
bool canOffer = false;
Vector< Set<string> > finalResult;


int main() {
    Set<string> cities = generateTestCities();
    Vector< Set<string> > locations = generateTestLocations();
    cout << "Number of locations: " << integerToString(locations.size()) << endl;
    Vector< Set<string> > result;
    int numHospitals = 3;
    
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << integerToString(numHospitals) + " are sufficient to cover all cities" << endl;
        //for (int i = 0; i < finalResult.size(); i++)  {
        //    for (string s : finalResult.get(i))
        //        cout << s << endl;
        //    cout << "new hospital" << endl;
        //}
    }
    else
        cout << integerToString(numHospitals) + " hospitals are NOT sufficient to cover all cities" << endl;
    
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result)   {
    
    if (result.size() == numHospitals)  {
        cout << "here" << endl;
        Set<string> citiesCovered;
        for (int i = 0; i < numHospitals; i++)  {
            for (string s : result.get(i))
                citiesCovered.add(s);
        }
        if (cities.size() == citiesCovered.size())  {
            finalResult = result;
            return true;
        }
        else    {
            result.clear();
            return false;
        }
        
    }
    else    {
        for (int i = 0; i < locations.size(); i++)  {
            cout << integerToString(i) << endl;
            Vector< Set<string> > tempResult = result;
            tempResult.add(locations.get(i));
            Vector< Set<string> > tempLocations = locations;
            tempLocations.remove(i);
            canOffer = canOffer || canOfferUniversalCoverage(cities,tempLocations, numHospitals,tempResult);
        }
        return canOffer;
    }
}

Set<string> generateTestCities()    {
    Set<string> cities;
    cities.add("A");
    cities.add("B");
    cities.add("C");
    cities.add("D");
    cities.add("E");
    cities.add("F");
    return cities;
}

Vector< Set<string> > generateTestLocations()   {
    Vector< Set<string> > locations;
    Set<string> location;
    location.add("A");
    location.add("B");
    location.add("C");
    locations.add(location);
    location.clear();
    location.add("A");
    location.add("C");
    location.add("D");
    locations.add(location);
    location.clear();
    location.add("B");
    location.add("F");
    locations.add(location);
    location.clear();
    location.add("C");
    location.add("E");
    location.add("F");
    locations.add(location);
    return locations;
}