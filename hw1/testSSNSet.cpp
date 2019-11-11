//
//  testSSNSet.cpp
//  Set
//
//  Created by Haley Kim on 1/22/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//


#include "SSNSet.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    SSNSet numbers;
    assert(numbers.size() == 0);
    numbers.add(111);
    assert(numbers.size() == 1);
    numbers.add(222);
    assert(numbers.size() == 2);
    numbers.print();
    cerr << "Passed All Tests" << endl;
}
