/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    if(listHead != NULL)    {
        deleteList(listHead);
    }
}

int DoublyLinkedListPriorityQueue::size() {
    Entry * cur;
    int c = 0;
    for (cur = listHead; cur != NULL; cur = cur->next)
        c++;
    return c;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	if(listHead == NULL)
        return true;
    else
        return false;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    Entry * newEntry = new Entry;
    newEntry->name = value;
    if(listHead == NULL)    {
        listHead = newEntry;
        newEntry->next = NULL;
        newEntry->prev = NULL;
    }
    else    {
        newEntry->next = listHead;
        newEntry->prev = NULL;
        listHead = newEntry;
    }
}

string DoublyLinkedListPriorityQueue::peek() {
    
    if (listHead == NULL)
        error("List is empty!");
    else    {
        string min = listHead->name;
        Entry * minP;
        for(Entry * cur = listHead->next; cur != NULL; cur = cur->next)   {
            if(cur->name < min) {
                min = cur->name;
                minP = cur;
            }
        }
        return min;
    }
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (listHead == NULL)
        error("List is empty!");
    else    {
        string min = listHead->name;
        Entry * minP = listHead;
        for(Entry * cur = listHead->next; cur != NULL; cur = cur->next)   {
            if(cur->name < min) {
                min = cur->name;
                minP = cur;
            }
        }
        // First element dequeued
        if (minP == listHead)   {
            int s = size();
            if (s > 1)   {
                listHead = minP->next;
                (minP->next)->prev = NULL;
            }
            else
                listHead = NULL;
        }
        // Last element dequeued
        else if (minP->next == NULL)    {
            (minP->prev)->next = NULL;
        }
        // Element in the middle dequeued
        else    {
            (minP->prev)->next = minP->next;
            (minP->next)->prev = minP->prev;
        }
        delete minP;
        return min;
    }
}

void DoublyLinkedListPriorityQueue::deleteList(Entry * & l)   {
    Entry * toDelete = l;
    delete toDelete;
    deleteList(l->next);
}

