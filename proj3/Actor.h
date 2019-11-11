#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
class Goodie;
class Penelope;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth);
    virtual void doSomething() = 0;
    bool isDead() const;
    void setDead();
    StudentWorld* getWorld() const;
    virtual void activateIfAppropriate(Actor* a);
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void beVomitedOnIfAppropriate();
    virtual void pickUpGoodieIfAppropriate(Goodie* g);
    virtual bool blocksMovement() const;
    virtual bool blocksFlame() const;
    virtual bool triggersOnlyActiveLandmines() const;
    virtual bool triggersZombieVomit() const;
    virtual bool threatensCitizens() const;
    virtual bool triggersCitizens() const;
protected:
    void loadBarriers(int &leftInt, int &rightInt, int &upInt, int &downInt);
private:
    StudentWorld* m_worldPtr;
};

class Wall: public Actor
{
public:
    Wall(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual bool blocksMovement() const;
    virtual bool blocksFlame() const;
private:
};

class ActivatingObject: public Actor
{
public:
    ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir);
private:
};

class Exit: public ActivatingObject
{
public:
    Exit(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
    virtual bool blocksFlame() const;
};

class Pit: public ActivatingObject
{
public:
    Pit(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
private:
};

class Flame: public ActivatingObject
{
public:
    Flame(StudentWorld* w, double x, double y, int dir);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
};

class Vomit: public ActivatingObject
{
public:
    Vomit(StudentWorld* w, double x, double y, int dir);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
};

class Landmine: public ActivatingObject
{
public:
    Landmine(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
};

class Goodie: public ActivatingObject
{
public:
    Goodie(StudentWorld* w, int imageID, double x, double y);
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void pickUp(Penelope* p) = 0;
};

class VaccineGoodie: public Goodie
{
public:
    VaccineGoodie(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

class GasCanGoodie: public Goodie
{
public:
    GasCanGoodie(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

class LandmineGoodie: public Goodie
{
public:
    LandmineGoodie(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

class Agent: public Actor
{
public:
    Agent(StudentWorld* w, int imageID, double x, double y, int dir);
    virtual bool blocksMovement() const;
    virtual bool triggersOnlyActiveLandmines() const;
};

class Human: public Agent
{
public:
    Human(StudentWorld* w, int imageID, double x, double y);
    virtual void beVomitedOnIfAppropriate();
    virtual bool triggersZombieVomit() const;
    void clearInfection();
    int getInfectionDuration() const;
};

class Penelope: public Human
{
public:
    Penelope(StudentWorld* w, double x, double y);
    virtual void doSomething();
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void pickUpGoodieIfAppropriate(Goodie* g);
    void increaseVaccines();
    void increaseFlameCharges();
    void increaseLandmines();
    int getNumVaccines() const;
    int getNumFlameCharges() const;
    int getNumLandmines() const;
private:
};

class Citizen: public Human
{
public:
    Citizen(StudentWorld* w,  double x, double y);
    virtual void doSomething();
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
};

class Zombie: public Agent
{
public:
    Zombie(StudentWorld* w,  double x, double y);
};

class DumbZombie: public Zombie
{
public:
    DumbZombie(StudentWorld* w,  double x, double y);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
};

class SmartZombie: public Zombie
{
public:
    SmartZombie(StudentWorld* w,  double x, double y);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
};

#endif // ACTOR_H_
