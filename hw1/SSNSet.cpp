//
//  SSNSet.cpp
//  Set
//
//  Created by Haley Kim on 1/22/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
: m_set()
{
}

bool SSNSet::add(unsigned long ssn)
// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.
{
    return m_set.insert(ssn);
}

int SSNSet::size() const // Return the number of SSNs in the SSNSet.
{
    return m_set.size();
}

void SSNSet::print() const
{
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
    for (int i = 0; i < size(); i++)
         {
             unsigned long temp = 0;
             m_set.get(i,temp);
             cout << temp << endl;
         }
}
