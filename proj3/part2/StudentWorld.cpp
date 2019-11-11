#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <sstream>
#include <iomanip>
#include <iostream>
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

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::updateStatus()
{
    ostringstream oss;
    oss << "Score: ";
    if (getScore() < 0)
    {
        oss << "-";
        oss.fill('0');
        oss << setw(5) << (-1*getScore());
    }
    else
    {
        oss.fill('0');
        oss << setw(6) << getScore();
    }
    oss.fill('0');
    oss << "  Level: " << getLevel() << "  Lives: " << getLives() <<
    "  Vaccines: " << m_ptrToPenny->getNumVaccines() << "  Flames: " << m_ptrToPenny->getNumFlameCharges() <<
    "  Mines: " << m_ptrToPenny->getNumLandmines() << "  Infected: " << m_ptrToPenny->getInfectionCount();
    
    setGameStatText(oss.str());
}

int StudentWorld::init()
{
    m_numCitizens = 0;
    m_status = GWSTATUS_CONTINUE_GAME;
    
    Level lev(assetPath());
    ostringstream levelFile;
    levelFile.fill('0');
    levelFile << "level" << setw(2) << getLevel() << ".txt";
    std::string s = levelFile.str();
    Level::LoadResult result = lev.loadLevel(s);
    if (getLevel() == 100 || result == Level::load_fail_file_not_found){
        cerr << "Cannot find " << levelFile.str() << " data file" << endl;
        return GWSTATUS_PLAYER_WON;
    }
    else if (result == Level::load_fail_bad_format){
        cerr << "Your level was improperly formatted" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::MazeEntry ge;
        for (int row = 0; row < LEVEL_WIDTH; row++){
            for (int col = 0; col < LEVEL_HEIGHT; col++){
                ge = lev.getContentsOf(col, row);
                
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::smart_zombie:
                        listOfActors.push_back(new SmartZombie(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::dumb_zombie:
                        listOfActors.push_back(new DumbZombie(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::player:
                        m_ptrToPenny = new Penelope(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this);
                        break;
                    case Level::exit:
                        listOfActors.push_back(new Exit(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::wall:
                        listOfActors.push_back(new Wall(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::pit:
                        listOfActors.push_back(new Pit(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::citizen:
                        m_numCitizens++;
                        listOfActors.push_back(new Citizen(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::vaccine_goodie:
                        listOfActors.push_back(new VaccineGoodie(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::gas_can_goodie:
                        listOfActors.push_back(new GasCanGoodie(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                    case Level::landmine_goodie:
                        listOfActors.push_back(new LandmineGoodie(col*SPRITE_WIDTH, row*SPRITE_HEIGHT, this));
                        break;
                }
            }
        }
    }
    updateStatus();
    return m_status;
}

int StudentWorld::move()
{
    if (m_status != GWSTATUS_CONTINUE_GAME)
        return m_status;
    
    m_ptrToPenny->doSomething();
    activateOnAppropriateActors(m_ptrToPenny);
    
    list<Actor*>::iterator itr;
    for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if ((*itr)->isDead())
        {
            delete *itr;
            itr = listOfActors.erase(itr);
        }
        else
        {
            (*itr)->doSomething();
            activateOnAppropriateActors(*itr);
        }
    }
    
    if (m_status == GWSTATUS_FINISHED_LEVEL)
    {
        return m_status;
    }
    if (m_ptrToPenny->isDead())
    {
        m_status = GWSTATUS_PLAYER_DIED;
        playSound(SOUND_PLAYER_DIE);
        decLives();
    }
    updateStatus();
    return m_status;
}

void StudentWorld::cleanUp()
{
    delete m_ptrToPenny;
    m_ptrToPenny = nullptr;
    list<Actor*>::iterator itr = listOfActors.begin();
    while (itr != listOfActors.end())
    {
        delete *itr;
        itr++;
    }
    listOfActors.clear();
}

void StudentWorld::citizenZombiefied(Citizen*)
{
    m_numCitizens--;
}

void StudentWorld::addActor(Actor* a)
{
    listOfActors.push_back(a);
}

void StudentWorld::activateOnAppropriateActors(Actor* a)
{
    if (a != m_ptrToPenny)
    {
        if (overlaps(a->getX(), a->getY(), m_ptrToPenny->getX(), m_ptrToPenny->getY()))
        {
            a->activateIfAppropriate(m_ptrToPenny);
        }
    }
    for (list<Actor*>::iterator itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if (a != (*itr))
        {
            if (overlaps(a->getX(), a->getY(), (*itr)->getX(), (*itr)->getY())){
                a->activateIfAppropriate(*itr);
            }
        }
    }
}

void StudentWorld::recordCitizenGone()
{
    m_numCitizens--;
}

void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{
    if (m_numCitizens == 0)
    {
        m_status = GWSTATUS_FINISHED_LEVEL;
        playSound(SOUND_LEVEL_FINISHED);
    }
}

bool StudentWorld::isAgentMovementBlockedAt(double x, double y, Agent* agent) const
{
    if (agent != m_ptrToPenny)
    {
        if (intersects(x, y, m_ptrToPenny->getX(), m_ptrToPenny->getY()))
        {
            if (m_ptrToPenny->blocksMovement())
            {
                return true;
            }
        }
    }
    list<Actor*>::const_iterator itr;
    for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if (agent != *itr)
        {
            if (intersects(x, y, (*itr)->getX(), (*itr)->getY()))
            {
                if ((*itr)->blocksMovement())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool StudentWorld::isFlameBlockedAt(double x, double y) const
{
    list<Actor*>::const_iterator itr;
    for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if (overlaps(x, y, (*itr)->getX(), (*itr)->getY()))
        {
            if ((*itr)->blocksFlame())
            {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::isVomitBlockedAt(double x, double y) const
{
    list<Actor*>::const_iterator itr;
    for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if (overlaps(x, y, (*itr)->getX(), (*itr)->getY()))
        {
            if ((*itr)->blocksVomit())
            {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool isThreat) const
{
    double minDist = -10;
    double minX;
    double minY;

    if (!isThreat)
    {
        if (m_ptrToPenny->triggersCitizens())
        {
            double currDist = sqrt(pow(m_ptrToPenny->getX() - x, 2) + pow(m_ptrToPenny->getY() - y, 2));
            if (minDist == -10 || currDist < minDist)
            {
                minDist = currDist;
                minX = m_ptrToPenny->getX();
                minY = m_ptrToPenny->getY();
            }
        }
    }
    else
    {
        list<Actor*>::const_iterator itr;
        for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
        {
            if ((*itr)->threatensCitizens())
            {
                double currDist = sqrt(pow((*itr)->getX() - x, 2) + pow((*itr)->getY() - y, 2));
                if (minDist == -10 || currDist < minDist)
                {
                    minDist = currDist;
                    minX = (*itr)->getX();
                    minY = (*itr)->getY();
                }
            }
        }
    }
    if (minDist == -10)
    {
        return false;
    }
    else
    {
        distance = minDist;
        otherX = minX;
        otherY = minY;
        return true;
    }
}

bool StudentWorld::locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance)
{
    double minDist = -10;
    double minX;
    double minY;
    
    if (m_ptrToPenny->triggersZombieVomit())
    {
        double currDist = sqrt(pow(m_ptrToPenny->getX() - x, 2) + pow(m_ptrToPenny->getY() - y, 2));
        if (minDist == -10 || currDist < minDist)
        {
            minDist = currDist;
            minX = m_ptrToPenny->getX();
            minY = m_ptrToPenny->getY();
        }
    }
    list<Actor*>::const_iterator itr;
    for (itr = listOfActors.begin(); itr != listOfActors.end(); itr++)
    {
        if ((*itr)->triggersZombieVomit())
        {
            double currDist = sqrt(pow((*itr)->getX() - x, 2) + pow((*itr)->getY() - y, 2));
            if (minDist == -10 || currDist < minDist)
            {
                minDist = currDist;
                minX = (*itr)->getX();
                minY = (*itr)->getY();
            }
        }
    }
    if (minDist == -10)
    {
        return false;
    }
    else
    {
        distance = minDist;
        otherX = minX;
        otherY = minY;
        return true;
    }
}

bool StudentWorld::intersects(double x1, double y1, double x2, double y2) const
{
    double deltaX = x2 - x1;
    if (deltaX < 0)
        deltaX = deltaX * (-1);
    double deltaY = y2 - y1;
    if (deltaY < 0)
        deltaY = deltaY * (-1);
    if (deltaX < SPRITE_WIDTH && deltaY < SPRITE_HEIGHT)
        return true;
    return false;
}

bool StudentWorld::overlaps(double x1, double y1, double x2, double y2) const
{
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)) <= 10;
}
