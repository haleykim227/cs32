//
//  History.h
//  zombies
//
//  Created by Haley Kim on 1/14/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_row;
    int m_col;
    char deadZombies[MAXROWS][MAXCOLS];
};

#endif // HISTORY_INCLUDED
