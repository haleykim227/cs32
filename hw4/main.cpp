//
//  main.cpp
//  Set
//
//  Created by Haley Kim on 3/4/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#include "Set.h"  // class template from problem 1
#include <string>
using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    Coord() : m_r(0), m_c(0) {}
    double r() const { return m_r; }
    double c() const { return m_c; }
private:
    double m_r;
    double m_c;
};

int main()
{
    Set<int> si;
    si.insert(7);               // OK
    Set<string> ss;
    ss.insert("7-Up");          // OK
    Set<Coord> sc;
    sc.insert(Coord(7, -7));    // error!
}
