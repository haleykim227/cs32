#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

void StudentWorld::activateOnAppropriateActors(Actor* a)
{
}

int StudentWorld::init()
{
    load();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::load()
{
    Level lev(assetPath());
    string levelFile = "level04.txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for (int y = LEVEL_HEIGHT-1; y >= 0; y--)
        {
            for (int x = 0; x < 16; x++)
            {
                Level::MazeEntry ge = lev.getContentsOf(x,y); // level_x=5, level_y=10 switch (ge) // so x=80 and y=160
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::dumb_zombie:
                    {
                        DumbZombie* dumbZombiePtr = new DumbZombie(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(dumbZombiePtr);
                        break;
                    }
                    case Level::smart_zombie:
                    {
                        SmartZombie* smartZombiePtr = new SmartZombie(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(smartZombiePtr);
                        break;
                    }
                    case Level::citizen:
                    {
                        Citizen* citizenPtr = new Citizen(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(citizenPtr);
                        break;
                    }
                    case Level::pit:
                    {
                        Pit* pitPtr = new Pit(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(pitPtr);
                        break;
                    }
                    case Level::vaccine_goodie:
                    {
                        VaccineGoodie* vaccineGoodiePtr = new VaccineGoodie(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(vaccineGoodiePtr);
                        break;
                    }
                    case Level::gas_can_goodie:
                    {
                        GasCanGoodie* gasCanGoodiePtr = new GasCanGoodie(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(gasCanGoodiePtr);
                        break;
                    }
                    case Level::landmine_goodie:
                    {
                        LandmineGoodie* landmineGoodiePtr = new LandmineGoodie(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(landmineGoodiePtr);
                        break;
                    }
                    case Level::player:
                    {
                        penelopePtr = new Penelope(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        break;
                    }
                    case Level::wall:
                    {
                        Wall* wallPtr = new Wall(this, SPRITE_WIDTH*x,SPRITE_HEIGHT*y);
                        listOfActors.push_back(wallPtr);
                        break;
                    }
                    case Level::exit:
                    {
                        Exit* exitPtr = new Exit(this, SPRITE_WIDTH*x, SPRITE_HEIGHT*y);
                        listOfActors.push_back(exitPtr);
                        break;
                    }
                }
            }
        }
    }
}

bool StudentWorld::barrierAt(int x, int y)
{
    for(std::list<Actor*>::iterator itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if (((*itr)->blocksMovement() == true) && ((*itr)->getX() == x) && ((*itr)->getY() == y))
            return true;
    }
    return false;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    penelopePtr->doSomething();
    for(std::list<Actor*>::iterator itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        (*itr)->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete penelopePtr;
    for(std::list<Actor*>::iterator itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        delete (*itr);
        listOfActors.erase(itr);
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
