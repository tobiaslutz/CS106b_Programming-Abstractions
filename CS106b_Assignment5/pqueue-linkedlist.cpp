/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {

}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    if(listHead != NULL)    {
        deleteList(listHead);
    }
}

int LinkedListPriorityQueue::size() {
    Entry * cur;
    int c = 0;
    for (cur = listHead; cur != NULL; cur = cur->next)
        c++;
    return c;
}

bool LinkedListPriorityQueue::isEmpty() {
	if (listHead == NULL)
        return true;
    else
        return false;
}

void LinkedListPriorityQueue::enqueue(string value) {
    Entry * newEntry = new Entry;
    newEntry->name = value;
    Entry * prev = NULL;
    Entry * cur = listHead;
    // Empty list
    if (listHead == NULL)   {
        newEntry->next = listHead;
        listHead = newEntry;
    }
    // New Entry goes in front of the list
    else if (value < listHead->name)    {
        newEntry->next = cur;
        listHead = newEntry;
    }
    else    {
        for (cur = listHead; cur != NULL; cur = cur->next)  {
            if (value < cur->name)  {
                newEntry->next = cur;
                prev->next = newEntry;
                return;
            }
                prev = cur;
        }
        // New Entry goes at the end of the list
        prev->next = newEntry;
        newEntry->next = NULL;
    }
}

string LinkedListPriorityQueue::peek() {
	if(listHead == NULL)
        error("Queue is empty!");
    else
        return listHead->name;
}

string LinkedListPriorityQueue::dequeueMin() {
    if(listHead == NULL)
        error("Queue is empty!");
    else    {
        string s = listHead->name;
        listHead = listHead->next;
        return s;
    }
}

void LinkedListPriorityQueue::deleteList(Entry * & l)   {
    Entry * toDelete = l;
    delete toDelete;
    deleteList(l->next);
}

