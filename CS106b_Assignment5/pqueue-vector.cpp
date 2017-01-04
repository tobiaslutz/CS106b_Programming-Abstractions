/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {
    vec.clear();
}

int VectorPriorityQueue::size() {
	
    return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
    return (size() == 0 ? true : false);
}

void VectorPriorityQueue::enqueue(string value) {
    vec.insert(size(), value);
}

int VectorPriorityQueue::minIndex()  {
    if (size() == 0)
        error("Priority Queue is empty.");
    else    {
        int min = 0;
        for(int i = 1; i < size(); i++) {
            if (vec.get(i) < vec.get(min))
                min = i;
        }
        return min;
    }
}

string VectorPriorityQueue::peek() {
    return vec.get(minIndex());
}

string VectorPriorityQueue::dequeueMin() {
    string min = vec.get(minIndex());
    vec.remove(minIndex());
    return min;
}

