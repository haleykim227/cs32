#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>
#include <math.h>
#include "Actor.h"
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void citizenZombiefied(Citizen*);
    void addActor(Actor* a);
    void activateOnAppropriateActors(Actor* a);
    void recordCitizenGone();
    void recordLevelFinishedIfAllCitizensGone();
    bool isAgentMovementBlockedAt(double x, double y, Agent* ac) const;
    bool isFlameBlockedAt(double x, double y) const;
    bool isVomitBlockedAt(double x, double y) const;
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool isThreat) const;
    bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);
private:
    void updateStatus();
    bool intersects(double x1, double y1, double x2, double y2) const;
    bool overlaps(double x1, double y1, double x2, double y2) const;
    
    Penelope* m_ptrToPenny;
    list<Actor*> listOfActors;
    int m_numCitizens;
    int m_status;
};

#endif // STUDENTWORLD_H_
