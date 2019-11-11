//
//  newSet.hpp
//  Set
//
//  Created by Haley Kim on 1/22/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef NEWSET_INCLUDED
#define NEWSET_INCLUDED

#include <iostream>
#include <string>

using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    Set();         // Create an empty set (i.e., one with no items).
    
    Set(int arraySize);
    
    Set(const Set& other); // copy constructor
    
    Set& operator=(const Set& rhs); // assignment operator
    
    ~Set(); // destructor
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
private:
    int m_size;
    int m_cap;
    ItemType* set;
};

#endif // NEWSET_INCLUDED
