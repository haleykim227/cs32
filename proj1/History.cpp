//
//  History.cpp
//  zombies
//
//  Created by Haley Kim on 1/14/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols;
    for (int i = 0; i < nRows; i++) // Creates grid of dots
    {
        for (int j = 0; j < nCols; j++)
        {
            deadZombies[i][j] = '.';
        }
    }
}

bool History::record(int r, int c)
{
     if ((r > 0 && r <= MAXROWS) && (c > 0 && c <= MAXCOLS))
     {
         if (deadZombies[r-1][c-1] >= 'A' && deadZombies[r-1][c-1] < 'Z')
             deadZombies[r-1][c-1] += 1;
         else if (deadZombies[r-1][c-1] == 'Z')
             deadZombies[r-1][c-1] = 'Z';
         else if (deadZombies[r-1][c-1] == '.')
             deadZombies[r-1][c-1] = 'A';
         return true;
     }
    else
        return false;
}

void History::display() const
{
    clearScreen();
    for (int r = 0; r < m_row; r++)
    {
        for (int c = 0; c < m_col; c++)
            cout << deadZombies[r][c];
        cout << endl;
    }
    cout << endl;
}

