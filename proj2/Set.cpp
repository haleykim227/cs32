//
//  Set.cpp
//  Project 2
//
//  Created by Haley Kim on 1/27/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include <iostream>
#include "Set.h"
using namespace std;

// Default Constructor
Set::Set()
{
    listSize = 0;
    ptrToDummy = new Node; // Have ptrToDummy point to a new Node
    ptrToDummy->next = ptrToDummy; // Have dummy node's next pointer point to itself
    ptrToDummy->prev = ptrToDummy; // Have dummy node's previous pointer point to itself
}

// Destructor
Set::~Set()
{
    Node* position = ptrToDummy->next; // pointer "position" points to the first real Node
    while (position != ptrToDummy) // Loop that stops once we've gone through all relevant Nodes
    {
        Node* temp = position->next; // Stores position's next pointer into temp
        delete position; // deallocate what pointer points to
        position = temp; // assigns pointer's next as pointer
    }
    delete ptrToDummy; // deallocate dummy node
}

// Copy Constructor
Set::Set(const Set& other)
{
    listSize = 0;
    ptrToDummy = new Node;
    ptrToDummy->next = ptrToDummy;
    ptrToDummy->prev = ptrToDummy; // Same as default constructor until here
    
    Node* otherPosition = other.ptrToDummy->next; // otherPosition points to the first real node in Set "other"
    Node* position = ptrToDummy->next; // position points to the first real node in this Set
    while (otherPosition != other.ptrToDummy) // looping through the other Set
    {
        insert(otherPosition->data); // adds what that Node in Set "other" contains to this Set
        position = position->next; // moves position to next Node
        otherPosition = otherPosition->next; // moves otherPosition to next Node
    }
}

// Assignment Operator
Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs) // checking if this Set and rhs points to the same address
    {
        Set temp(rhs); // uses copy constructor to create a copy of rhs
        swap(temp); // uses swap function to have this Set become temp
        // temp will be destroyed outside of these curly braces, no memory leak
    }
    return *this; // returns itself
}

// Checking if Set is empty
bool Set::empty() const
{
    if (listSize == 0)
        return true;
    else
        return false;
}

// Returns Set's size
int Set::size() const
{
    return listSize;
}

// Insert a value into Set
bool Set::insert(const ItemType& value)
{
    // if the Set is currently empty
    if (listSize == 0)
    {
        Node* newPosition = new Node; // newPosition points to a dynamically allocated Node
        newPosition->data = value; // adds value into new Node
        newPosition->prev = ptrToDummy; // has new Node point to dummy node with prev pointer
        newPosition->next = ptrToDummy; // has new Node point to dummy node with next pointer
        ptrToDummy->next = newPosition; // has dummy node point to new Node with next pointer
        ptrToDummy->prev = newPosition; // has dummy node point to new Node with prev pointer
        listSize++; // increment listSize because we added a Node to the Set
        return true;
    }

    Node* position = ptrToDummy->next; // pointer "position" points to first relevant Node
    while (position != ptrToDummy) // looping through every Node
    {
        if (value == position->data) // if value in function is the same as any of the values in the Set
            return false;
        position = position->next; // if not move position to point to the next Node
    }
    
    position = ptrToDummy->next; // reset pointer "position" to the first relevant Node
    while (position != ptrToDummy) // looping through every Node
    {
        if (value < position->data) // assigns position to the first Node that contains data greater than value
            break;
        position = position->next;
    }
    
    Node* newPosition = new Node; // now that we know where to insert, create new Node with pointer "newPosition"
    newPosition->data = value; // add value to newPosition's data
    newPosition->prev = position->prev; // connect new Node's prev pointer to position's prev
    newPosition->next = position; // connect new Node's next pointer to position's next
    position->prev->next = newPosition; // connect the Node before position's to new Node
    position->prev = newPosition; // connect position's prev pointer to new Node
    listSize++; // increment listSize because we just added a new Node to Set
    return true;
}

// Erase a value from Set
bool Set::erase(const ItemType& value)
{
    Node* position = ptrToDummy->next; // position points to first relevant Node
    ItemType temp;
    while (position != ptrToDummy) // looping through every Node
    {
        if (value == position->data) // when we find a data in Node that is the same as value
            temp = position->data; // assign the data into temp
        position = position->next; // if not, move position to the next Node
    }
    if (temp != value) // if temp does not equal value, that means there was no data in Node same as value, cannot erase from Set because value does not exist
        return false;
    
    position = ptrToDummy->next; // reset pointer to point to first relevant Node
    while (position != ptrToDummy) // looping through every Node
    {
        if (value == position->data) // when we find a data in Node that is the same as value
            break; // break out of loop and we have our position
        position = position->next; // if not, move position to the next Node
    }
    
    position->prev->next = position->next; // connect the Nodes before and after position to each other
    position->next->prev = position->prev;
    delete position; // deallocate the Node position points to
    listSize--; // decrement listSize because we just deleted a Node from Set
    return true;
}

// False if Set does not contain value, true if it does
bool Set::contains(const ItemType& value) const
{
    if (listSize == 0) // if list is empty, does not contain anything
        return false;
    Node* position = ptrToDummy->next; // sets position to the first relevant Node
    while (position != ptrToDummy) // looping through every Node
    {
        if (value == position->data) // if we find a data in Node identical to value, true
            return true;
        position = position->next; // if not, move position along to the next pointer
    }
    return false;
}

// Getting the value that is exactly greater than "pos" elements
bool Set::get(int pos, ItemType& value) const
{
    if ((pos < 0) || (pos >= listSize)) // if pos is negative or equal to or greater than listSize, false
    {
        return false;
    }
    Node* position = ptrToDummy->next; // sets position to first relevant Node
    for (int i = 0; i < pos; i++)
    {
        position = position->next; // moves along position to the next pointer as many times as pos
    }
    value = position->data; // assign that Node's data to value
    return true;
}

// Swat this Set with another Set
void Set::swap(Set& other)
{
    int tempSize = listSize; // three-way swap of int listSize
    listSize = other.listSize;
    other.listSize = tempSize;
    
    Node* tempPtr = ptrToDummy; // three-way swap of head pointer to dummy node
    ptrToDummy = other.ptrToDummy;
    other.ptrToDummy = tempPtr;
}

// Print function to debug
void Set::dump() const
{
    Node* position = ptrToDummy->next; // sets position to first relevant Node
    while (position != ptrToDummy) // looping through every element
    {
        cerr << position->data << endl;
        position = position->next; // moves position along to next pointer
    }
}

// Unite function to combine two Sets into result Set
void unite(const Set& s1, const Set& s2, Set& result)
{
    // result = s1 + s2 - duplicates
    // result may not be an empty Set
    Set temp; // create a temporary Set
    for (int i = 0; i < s1.size(); i++) // looping through each element in s1
    {
        ItemType object;
        s1.get(i,object); // get data of Node i
        temp.insert(object); // insert data of Node i into temp Set
        // insert function takes care of duplicate situation, does not insert if it already exists
    }
    for (int i = 0; i < s2.size(); i++) // looping through each element in s2
    {
        ItemType object;
        s2.get(i,object); // get data from Node i
        temp.insert(object); // insert data of Node i into temp Set
        // insert function takes care of duplicate situation, does not insert if it already exists
    }
    result = temp; // uses assignment operator to set result equal to temp, whatever Set result had would be deallocated because assignment operator uses the swap function
}

// Subtract function to subtract Set s2 from s1 and store in result
void subtract(const Set& s1, const Set& s2, Set& result)
{
    // result = s1 - s2
    // result may not be an empty Set
    Set temp; // create a temporary Set
    unite(s1, s2, temp); // uses unite to add s1 and s2
    for(int i = 0; i < s2.size(); i++) // looping through each element in s2
    {
        ItemType object;
        s2.get(i, object); // get data of Node i
        temp.erase(object); // erase data of Node i from temp Set
    }
    result = temp; // set result as temp
    // same as unite function, no memory leak
}
