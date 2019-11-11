//
//  Player.h
//  Project 1
//
//  Created by Haley Kim on 1/14/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

#endif // PLAYER_INCLUDED
