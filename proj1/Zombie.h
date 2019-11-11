//
//  Zombie.h
//  Project 1
//
//  Created by Haley Kim on 1/11/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef ZOMBIE_INCLUDED
#define ZOMBIE_INCLUDED

class Arena;
class History;

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    History* m_history;
    int    m_row;
    int    m_col;
    int    m_health;
};

#endif // ZOMBIE_INCLUDED
