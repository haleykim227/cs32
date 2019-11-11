#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

class Actor;
class Penelope;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    
    void addActor(Actor* a);
    void recordCitizenGone();
    void recordLevelFinishedIfAllCitizensGone();
    void activateOnAppropriateActors(Actor* a);
    bool isAgentMovementBlockedAt(double x, double y) const;
    bool isFlameBlockedAt(double x, double y) const;
    bool isZombieVomitTriggerAt(double x, double y) const;
    bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const;
    bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const;
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool barrierAt(int x, int y);
    
    void newLevel();
private:
    void load();
    Penelope* penelopePtr;
    std::list<Actor*> listOfActors;
};

#endif // STUDENTWORLD_H_
