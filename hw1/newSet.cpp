//
//  newSet.cpp
//  Set
//
//  Created by Haley Kim on 1/22/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "newSet.h"
#include <iostream>
#include <string>

using namespace std;

Set::Set()         // Create an empty set (i.e., one with no items).
{
    set = new ItemType[DEFAULT_MAX_ITEMS];
    m_cap = DEFAULT_MAX_ITEMS;
    m_size = 0;
}

Set::Set(int arraySize)         
{
    set = new ItemType[arraySize];
    m_cap = arraySize;
    m_size = 0;
}

Set::Set(const Set& other) // copy constructor
{
    m_size = other.size();
    m_cap = other.m_cap;
    set = new ItemType[m_cap];
    for(int i = 0; i < m_size; i++){
        set[i] = other.set[i];
    }
}

Set& Set::operator=(const Set& rhs) // assignment operator
{
    if(this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

Set::~Set() // destructor
{
    delete [] set;
}

bool Set::empty() const
{
    if (m_size > 0)
    {
        return false;
    }
    return true;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    int position = 0;
    for (int i = 0; i < size(); i++)
    {
        if (value == set[i])
        {
            return false;
        }
        if (value < set[i])
        {
            position = i;
            break;
        }
        else if (value > set[size()-1])
        {
            position = size();
        }
    }
    if (position >= 0 && position <= size())
    {
        if (m_size < m_cap)
        {
            m_size++;
            for (int i = size()-1; i > position ; i--)
            {
                set[i] = set[i-1];
            }
            set[position] = value;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool Set::erase(const ItemType& value)
{
    for (int i = 0; i < size(); i++)
    {
        if (set[i] == value)
        {
            int position = i;
            for (int i = position; i < size(); i++)
            {
                set[i] = set[i+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < size(); i++)
    {
        if (set[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < size() && i >= 0)
    {
        value = set[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    ItemType* temp_set;
    
    //Declare all the temp variables
    temp_set = set;
    int tempSize = m_size;
    int tempCap = m_cap;
    
    set = other.set;
    other.set = temp_set;
    
    m_cap = other.m_cap;
    other.m_cap = tempCap;
    
    m_size = other.m_size;
    other.m_size = tempSize;
}
