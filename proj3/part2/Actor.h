#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include "GraphObject.h"
class StudentWorld;

class Goodie;

//=================================================== Actor =======================================================
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, StudentWorld* world, Direction dir = 0, int depth = 0);
    StudentWorld* getWorld() const;
    
    bool isDead() const;
    void setDead();
    virtual void doSomething() = 0;
    virtual void activateIfAppropriate(Actor* a);
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void beVomitedOnIfAppropriate();
    virtual void pickUpGoodieIfAppropriate(Goodie* g);
    virtual bool blocksMovement() const;
    virtual bool blocksFlame() const;
    virtual bool blocksVomit() const;
    virtual bool triggersZombieVomit() const;
    virtual bool triggersOnlyActiveLandmines() const;
    virtual bool threatensCitizens() const;
    virtual bool triggersCitizens() const;
private:
    StudentWorld* m_ptrToWorld;
    bool m_isDead;
};

//=================================================== Agent =======================================================
class Agent : public Actor
{
public:
    Agent(int imageID, double x, double y, StudentWorld* world);
    bool blocksMovement() const;
    bool triggersOnlyActiveLandmines() const;
    virtual void move() = 0;
};

//=================================================== Human =======================================================
class Human: public Agent
{
public:
    Human(int imageID, double startX, double startY, StudentWorld* world);
    bool triggersZombieVomit() const;
    bool isInfected();
    int getInfectionCount();
    void clearInfection();
    void dealWithInfection();
    virtual void dieByInfection();
    virtual void beVomitedOnIfAppropriate();
private:
    int m_infectionCount;
    bool m_isInfected;
};

//================================================= Penelope ======================================================
class Penelope: public Human
{
public:
    Penelope(double startX, double startY, StudentWorld* world);
    bool triggersCitizens() const;
    int getNumFlameCharges();
    int getNumLandmines();
    int getNumVaccines();
    void increaseVaccines();
    void increaseFlameCharges();
    void increaseLandmines();
    virtual void doSomething();
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void pickUpGoodieIfAppropriate(Goodie* g);
protected:
    void move();
private:
    int m_numFlameCharges;
    int m_numLandmines;
    int m_numVaccines;
};

//================================================== Citizen ======================================================
class Citizen : public Human
{
public:
    Citizen(double x, double y, StudentWorld* world);
    void beVomitedOnIfAppropriate();
    void doSomething();
    void move();
    void useExitIfAppropriate();
    void dieByFallOrBurnIfAppropriate();
    void dieByInfection();
private:
    bool m_isParalyzed;
};

//================================================== Zombie =======================================================
class Zombie : public Agent
{
public:
    Zombie(double x, double y, StudentWorld* world);
    bool threatensCitizens() const;
    void doSomething();
    void vomit() const;
private:
    bool m_isParalyzed;
};

//================================================ DumbZombie =====================================================
class DumbZombie : public Zombie
{
public:
    DumbZombie(double x, double y, StudentWorld* world);
    void move();
    void dieByFallOrBurnIfAppropriate();
private:
    int m_distance;
};

//================================================ SmartZombie ====================================================
class SmartZombie : public Zombie
{
public:
    SmartZombie(double x, double y, StudentWorld* world);
    void move();
    void dieByFallOrBurnIfAppropriate();
private:
    int m_distance;
};


//=================================================== Wall ========================================================
class Wall: public Actor
{
public:
    Wall(double startX, double startY, StudentWorld* world);
    void doSomething();
    bool blocksMovement() const;
    bool blocksFlame() const;
    bool blocksVomit() const;
};

//============================================= ActivatingObject ==================================================
class ActivatingObject : public Actor{
public:
    ActivatingObject(int imageID, double x, double y, StudentWorld* world, int dir, int depth);
    void doSomething();
private:
    int m_life;
};

//=================================================== Exit ========================================================
class Exit: public ActivatingObject
{
public:
    Exit(double startX, double startY, StudentWorld* world);
    void doSomething();
    void activateIfAppropriate(Actor* a);
    bool blocksFlame() const;
};

//==================================================== Pit ========================================================
class Pit : public ActivatingObject
{
public:
    Pit(double x, double y, StudentWorld* w);
    void doSomething();
    void activateIfAppropriate(Actor* a);
};

//=================================================== Flame =======================================================
class Flame : public ActivatingObject
{
public:
    Flame(double x, double y, StudentWorld* world, int dir);
    void activateIfAppropriate(Actor* a);
private:
};

//=================================================== Vomit =======================================================
class Vomit : public ActivatingObject
{
public:
    Vomit(double x, double y, StudentWorld* world, int dir);
    void activateIfAppropriate(Actor* a);
private:
};


//================================================= Landmine ======================================================
class Landmine : public ActivatingObject
{
public:
    Landmine(double x, double y, StudentWorld* world);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
private:
    int m_safetyTicks;
    bool m_isActive;
    void explode();
};

//================================================== Goodie =======================================================
class Goodie : public ActivatingObject
{
public:
    Goodie(int imageID, double x, double y, StudentWorld* world);
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void pickUp(Penelope* p) = 0;
};

//============================================== LandmineGoodie ===================================================
class LandmineGoodie : public Goodie
{
public:
    LandmineGoodie(double x, double y, StudentWorld* world);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

//================================================ GasCanGoodie ===================================================
class GasCanGoodie : public Goodie
{
public:
    GasCanGoodie(double x, double y, StudentWorld* world);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

//=============================================== VaccineGoodie ===================================================
class VaccineGoodie : public Goodie
{
public:
    VaccineGoodie(double x, double y, StudentWorld* world);
    virtual void doSomething();
    virtual void pickUp(Penelope* p);
};

#endif // ACTOR_INCLUDED
