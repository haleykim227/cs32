//
//  main.cpp
//  mazequeue
//
//  Created by Haley Kim on 2/5/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include <iostream>
#include <queue>
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
    queue<Coord> coordQueue;
    Coord start(sr,sc);
    Coord end(er,ec);
    coordQueue.push(start);
    maze[sr][sc] = 'X';
    while (!coordQueue.empty())
    {
        Coord current = coordQueue.front();
        coordQueue.pop();
        if ((current.r() == end.r()) && (current.c() == end.c()))
            return true;
        if (maze[current.r()+1][current.c()] == '.')
        {
            coordQueue.push(Coord(current.r()+1, current.c()));
            maze[current.r()+1][current.c()] = 'X';
        }
        if (maze[current.r()][current.c()-1] == '.')
        {
            coordQueue.push(Coord(current.r(), current.c()-1));
            maze[current.r()][current.c()-1] = 'X';
        }
        if (maze[current.r()-1][current.c()] == '.')
        {
            coordQueue.push(Coord(current.r()-1, current.c()));
            maze[current.r()-1][current.c()] = 'X';
        }
        if (maze[current.r()][current.c()+1] == '.')
        {
            coordQueue.push(Coord(current.r(), current.c()+1));
            maze[current.r()][current.c()+1] = 'X';
        }
    }
    return false;
}
