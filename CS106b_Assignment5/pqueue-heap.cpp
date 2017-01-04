/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
    heap =allocMemory(0, arrLen);
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] heap;
}

int HeapPriorityQueue::size() {
    int s = 0;
    for(int i = 0; i < arrLen; i++) {
        if(heap[i] == "")
            break;
        s++;
    }
	
	return s;
}

bool HeapPriorityQueue::isEmpty() {
	if(heap[0] == "")
        return true;
    else
        return false;
}

void HeapPriorityQueue::enqueue(string value) {
    int newSlot = size();
    if(newSlot > arrLen/2)   {
        arrLen = 2 * arrLen;
        heap = allocMemory(newSlot, arrLen);
    }
    heap[newSlot] = value;
    bubbleUp(newSlot);
    
}

string HeapPriorityQueue::peek() {
    if(heap[0] == "")
        error("Heap is empty!");
    else
        return heap[0];
}

string HeapPriorityQueue::dequeueMin() {
    if(heap[0] == "")
        error("Heap is empty!");
    else    {
        swap(0,size()-1);
        string min = heap[size() - 1];
        heap[size() - 1] = "";
        if(size() > 1)
            bubbleDown(0);
        return min;
    }
}

string * HeapPriorityQueue::allocMemory(int oldLen, int newLen)   {
        string * newHeap = new string[newLen];
        for(int i = 0; i < newLen; i++) {
            if(i < oldLen)   {
                string toCopy = heap[i];
                newHeap[i] = toCopy;
            }
            else
                newHeap[i] = "";
        }
    return newHeap;
}

void HeapPriorityQueue::swap(int prior, int later) {
    string temp = heap[prior];
    heap[prior] = heap[later];
    heap[later] = temp;
}

void HeapPriorityQueue::bubbleUp(int up)    {
    up = up + 1;
    while(up > 1)    {
        int parent = up / 2;
        if(heap[up - 1] < heap[parent - 1])
            swap(parent - 1, up - 1);
        else
            break;
        
        up = parent;
    }
}

void HeapPriorityQueue::bubbleDown(int down)    {
    // Simulate that array starts at position 1
    down = down + 1;
    
    // Actual array positions of children nodes (if existant)
    int childOne = 2 * down - 1;
    int childTwo =  2 * down;
    
    // True if down has no children nodes
    if (childOne >= size() && childTwo >= size())
        return;
    else    {
        // childOne is not a children node; therefore treat childOne as childTwo
        if (childOne >= size())
            childOne = childTwo;
        // childTwo is not a children node; therefore treat childTwo as childOne
        else if (childTwo >= size())
            childTwo = childOne;
        
        // Both children nodes carry greater values
        if (heap[down - 1] <= heap[childOne] && heap[down - 1] <= heap[childTwo])
            return;
        else    {
            int smallerChild;
            (heap[childOne] < heap[childTwo] ? smallerChild = childOne : smallerChild = childTwo);
            swap(down - 1, smallerChild);
            bubbleDown(smallerChild);
        }
    }
}

