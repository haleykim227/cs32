//
//  Set.h
//  Project 2
//
//  Created by Haley Kim on 1/27/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef SET_H
#define SET_H

#include <iostream>

using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const;
private:
    int listSize;
    class Node
    {
    public:
        ItemType  data;
        Node* next;
        Node* prev;
    };
    Node* ptrToDummy;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_H
