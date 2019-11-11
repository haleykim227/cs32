//
//  Game.h
//  Project 1
//
//  Created by Haley Kim on 1/14/19.
//  Copyright © 2019 Haley Kim. All rights reserved.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

int decodeDirection(char dir);

#endif // GAME_INCLUDED
