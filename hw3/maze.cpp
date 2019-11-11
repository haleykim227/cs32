//
//  main.cpp
//  maze
//
//  Created by Haley Kim on 2/11/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include <iostream>
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
    Coord current = Coord(sr, sc);
    Coord destination = Coord(er, ec);
    if ((current.r() == destination.r()) && (current.c() == destination.c()))
        return true;
    else
    {
        if (maze[current.r()+1][current.c()] == '.')
        {
            maze[current.r()+1][current.c()] = 'X';
            if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
                return true;
        }
        if (maze[current.r()][current.c()-1] == '.')
        {
            maze[current.r()][current.c()-1] = 'X';
            if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
                return true;
        }
        if (maze[current.r()-1][current.c()] == '.')
        {
            maze[current.r()-1][current.c()] = 'X';
            if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
                return true;
        }
        if (maze[current.r()][current.c()+1] == '.')
        {
            maze[current.r()][current.c()+1] = 'X';
            if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
                return true;
        }
    }
    return false;
}
