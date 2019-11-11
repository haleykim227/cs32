//
//  mazestack.cpp
//  mazestack
//
//  Created by Haley Kim on 2/5/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

class Coord
{
    public:
        Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
        int r() const { return m_r; }
        int c() const { return m_c; }
    private:
        int m_r;
        int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord start(sr,sc);
    Coord end(er,ec);
    coordStack.push(start);
    maze[sr][sc] = 'X';
    while (!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();
        if ((current.r() == end.r()) && (current.c() == end.c()))
            return true;
        if (maze[current.r()+1][current.c()] == '.')
        {
            coordStack.push(Coord(current.r()+1, current.c()));
            maze[current.r()+1][current.c()] = 'X';
        }
        if (maze[current.r()][current.c()-1] == '.')
        {
            coordStack.push(Coord(current.r(), current.c()-1));
            maze[current.r()][current.c()-1] = 'X';
        }
        if (maze[current.r()-1][current.c()] == '.')
        {
            coordStack.push(Coord(current.r()-1, current.c()));
            maze[current.r()-1][current.c()] = 'X';
        }
        if (maze[current.r()][current.c()+1] == '.')
        {
            coordStack.push(Coord(current.r(), current.c()+1));
            maze[current.r()][current.c()+1] = 'X';
        }
    }
    return false;
}
