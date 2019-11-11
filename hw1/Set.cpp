//
//  Set.cpp
//  Set
//
//  Created by Haley Kim on 1/22/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "Set.h"
#include <string>

using namespace std;

Set::Set()         // Create an empty set (i.e., one with no items).
{
    m_size = 0;
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
        if (value == m_value[i])
        {
            return false;
        }
        if (value < m_value[i])
        {
            position = i;
            break;
        }
        else if (value > m_value[size()-1])
        {
            position = size();
        }
    }
    if (position >= 0 && position <= size())
    {
        if (m_size < DEFAULT_MAX_ITEMS)
        {
            m_size++;
            for (int i = size()-1; i > position ; i--)
            {
                m_value[i] = m_value[i-1];
            }
            m_value[position] = value;
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
        if (m_value[i] == value)
        {
            int position = i;
            for (int i = position; i < size(); i++)
            {
                m_value[i] = m_value[i+1];
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
        if (m_value[i] == value)
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
        value = m_value[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    ItemType temp_Set[DEFAULT_MAX_ITEMS];
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        temp_Set[i] = m_value[i];
    }
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        m_value[i] = other.m_value[i];
    }
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        other.m_value[i] = temp_Set[i];
    }
}
