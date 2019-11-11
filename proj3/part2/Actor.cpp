#include "Actor.h"
#include "StudentWorld.h"
#include <cstdlib>
#include <math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//=================================================== Actor =======================================================
Actor::Actor(int imageID, double startX, double startY, StudentWorld* world, Direction dir, int depth)
: GraphObject(imageID, startX, startY, dir, depth)
{
    m_isDead = false;
    m_ptrToWorld = world;
}

bool Actor::isDead() const
{
    return m_isDead;
}

StudentWorld* Actor::getWorld() const
{
    return m_ptrToWorld;
}

void Actor::setDead()
{
    m_isDead = true;
}

void Actor::activateIfAppropriate(Actor* a)
{
}

void Actor::useExitIfAppropriate()
{
}

void Actor::dieByFallOrBurnIfAppropriate()
{
}

void Actor::beVomitedOnIfAppropriate()
{
}

void Actor::pickUpGoodieIfAppropriate(Goodie* g)
{
}

bool Actor::blocksMovement() const
{
    return false;
}

bool Actor::blocksFlame() const
{
    return false;
}

bool Actor::blocksVomit() const
{
    return false;
}

bool Actor::triggersZombieVomit() const
{
    return false;
}

bool Actor::triggersOnlyActiveLandmines() const
{
    return false;
}

bool Actor::threatensCitizens() const
{
    return false;
}

bool Actor::triggersCitizens() const
{
    return false;
}

//=================================================== Wall ========================================================
Wall::Wall(double startX, double startY, StudentWorld* world)
: Actor(IID_WALL, startX, startY, world){}

void Wall::doSomething()
{
}

bool Wall::blocksFlame() const
{
    return true;
}

bool Wall::blocksVomit() const
{
    return true;
}

bool Wall::blocksMovement() const
{
    return true;
}

//============================================= ActivatingObject ==================================================
ActivatingObject::ActivatingObject(int imageID, double x, double y, StudentWorld* world, int dir, int depth)
: Actor(imageID, x, y, world, dir, depth)
{
    m_life = 2;
}

void ActivatingObject::doSomething()
{
    m_life--;
    if (m_life == 0)
    {
        setDead();
    }
}

//=================================================== Exit ========================================================
Exit::Exit(double startX, double startY, StudentWorld* world)
: ActivatingObject(IID_EXIT, startX, startY, world, right, 1)
{
}

void Exit::doSomething()
{
}

void Exit::activateIfAppropriate(Actor* a)
{
    a->useExitIfAppropriate();
}

bool Exit::blocksFlame() const
{
    return true;
}

//==================================================== Pit ========================================================
Pit::Pit(double x, double y, StudentWorld* world)
: ActivatingObject(IID_PIT, x, y, world, right, 0)
{
}

void Pit::doSomething()
{
}

void Pit::activateIfAppropriate(Actor* a)
{
    a->dieByFallOrBurnIfAppropriate();
}

//=================================================== Flame =======================================================
Flame::Flame(double x, double y, StudentWorld* world, int dir)
: ActivatingObject(IID_FLAME, x, y, world, dir, 0)
{
}

void Flame::activateIfAppropriate(Actor* a)
{
    a->dieByFallOrBurnIfAppropriate();
}

//=================================================== Vomit =======================================================
Vomit::Vomit(double x, double y, StudentWorld* world, int dir)
: ActivatingObject(IID_VOMIT, x, y, world, dir, 0)
{
}

void Vomit::activateIfAppropriate(Actor* a)
{
    a->beVomitedOnIfAppropriate();
}

//================================================= Landmine ======================================================
Landmine::Landmine(double x, double y, StudentWorld* world)
: ActivatingObject(IID_LANDMINE, x, y, world, right, 1)
{
    m_safetyTicks = 30;
    m_isActive = false;
}

void Landmine::doSomething()
{
    if (m_isActive)
        return;
    
    m_safetyTicks--;
    
    if (m_safetyTicks == 0){
        m_isActive = true;
    }
}

void Landmine::activateIfAppropriate(Actor* a)
{
    if (!m_isActive)
        return;
    
    if (a->triggersOnlyActiveLandmines())
    {
        explode();
    }
}

void Landmine::dieByFallOrBurnIfAppropriate()
{
    explode();
}

void Landmine::explode()
{
    if (isDead())
        return;
    
    setDead();
    getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
    
    getWorld()->addActor(new Flame(getX(), getY(), getWorld(), up));
    
    // on top
    int newX = getX();
    int newY = getY() + SPRITE_HEIGHT;
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // on top, right
    newX = getX() + SPRITE_WIDTH;
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // on top, left
    newX = getX() - SPRITE_WIDTH;
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // beneath
    newX = getX();
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // beneath, right
    newY = getY() - SPRITE_HEIGHT;
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // beneath, left
    newX = getX() - SPRITE_WIDTH;
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // right
    newX = getX();
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // left
    newY = getY();
    if (!getWorld()->isFlameBlockedAt(newX, newY))
    {
        getWorld()->addActor(new Flame(newX, newY, getWorld(), up));
    }
    
    // pit at center
    getWorld()->addActor(new Pit(getX(), getY(), getWorld()));
}

//================================================== Goodie =======================================================
Goodie::Goodie(int imageID, double x, double y, StudentWorld* world)
: ActivatingObject(imageID, x, y, world, right, 1)
{
}

void Goodie::activateIfAppropriate(Actor* a)
{
    a->pickUpGoodieIfAppropriate(this);
}

void Goodie::dieByFallOrBurnIfAppropriate()
{
    setDead();
}

//============================================== LandmineGoodie ===================================================
LandmineGoodie::LandmineGoodie(double x, double y, StudentWorld* world)
: Goodie(IID_LANDMINE_GOODIE, x, y, world)
{
}

void LandmineGoodie::doSomething()
{
}

void LandmineGoodie::pickUp(Penelope* p)
{
    p->increaseLandmines();
    setDead();
}

//================================================ GasCanGoodie ===================================================
GasCanGoodie::GasCanGoodie(double x, double y, StudentWorld* world)
: Goodie(IID_GAS_CAN_GOODIE, x, y, world)
{
}

void GasCanGoodie::doSomething()
{
}

void GasCanGoodie::pickUp(Penelope* p)
{
    p->increaseFlameCharges();
    setDead();
}

//=============================================== VaccineGoodie ===================================================
VaccineGoodie::VaccineGoodie(double x, double y, StudentWorld* world)
: Goodie(IID_VACCINE_GOODIE, x, y, world)
{
}

void VaccineGoodie::doSomething()
{
}

void VaccineGoodie::pickUp(Penelope* p)
{
    p->increaseVaccines();
    setDead();
}

//=================================================== Agent =======================================================
Agent::Agent(int imageID, double x, double y, StudentWorld* world)
: Actor(imageID, x, y, world)
{
}

bool Agent::blocksMovement() const
{
    return true;
}

bool Agent::triggersOnlyActiveLandmines() const
{
    return true;
}

//=================================================== Human =======================================================
Human::Human(int imageID, double startX, double startY, StudentWorld* world)
: Agent(imageID, startX, startY, world)
{
    m_infectionCount = 0;
    m_isInfected = false;
}

void Human::beVomitedOnIfAppropriate()
{
    m_isInfected = true;
}

bool Human::triggersZombieVomit() const
{
    return true;
}

void Human::clearInfection()
{
    m_infectionCount = 0;
    m_isInfected = false;
}

int Human::getInfectionCount()
{
    return m_infectionCount;
}


void Human::dealWithInfection()
{
    if (m_isInfected)
    {
        m_infectionCount++;
        if (m_infectionCount == 500)
        {
            dieByInfection();
        }
    }
}

void Human::dieByInfection()
{
    setDead();
}

bool Human::isInfected()
{
    return m_isInfected;
}

//================================================= Penelope ======================================================
Penelope::Penelope(double startX, double startY, StudentWorld* world)
: Human(IID_PLAYER, startX, startY, world)
{
    m_numFlameCharges = 0;
    m_numLandmines = 0;
    m_numVaccines = 0;
}

void Penelope::doSomething()
{
    if (isDead())
        return;
    dealWithInfection();
    int ch;
    if (getWorld()->getKey(ch))
    {
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(left);
                move();
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                move();
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                move();
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                move();
                break;
            case KEY_PRESS_SPACE:
                if (m_numFlameCharges >= 1)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    m_numFlameCharges--;
                    int x = 0;
                    int y = 0;
                    Direction dir = getDirection();
                    switch (dir){
                        case up:
                            y += SPRITE_HEIGHT;
                            break;
                        case down:
                            y -= SPRITE_HEIGHT;
                            break;
                        case left:
                            x -= SPRITE_WIDTH;
                            break;
                        case right:
                            x += SPRITE_WIDTH;
                            break;
                    }
                    for (int i = 1; i < 4; i++)
                    {
                        if (getWorld()->isFlameBlockedAt(getX()+ i * x, getY() + i * y))
                        {
                            break;
                        }
                        else
                        {
                            Flame* f = new Flame(getX() + i * x, getY() + i * y, getWorld(), dir);
                            getWorld()->addActor(f);
                        }
                    }
                }
                break;
            case KEY_PRESS_TAB:
                if (m_numLandmines >= 1)
                {
                    getWorld()->addActor(new Landmine(getX(), getY(), getWorld()));
                    m_numLandmines--;
                }
                break;
            case KEY_PRESS_ENTER:
                if (m_numVaccines >= 1)
                {
                    m_numVaccines--;
                    clearInfection();
                }
                break;
        }
    }
}

void Penelope::move()
{
    Direction dir = getDirection();
    double newX = getX();
    double newY = getY();
    switch(dir){
        case up:
            newY += 4;
            break;
        case down:
            newY -= 4;
            break;
        case left:
            newX -= 4;
            break;
        case right:
            newX += 4;
            break;
    }
    if (!(getWorld()->isAgentMovementBlockedAt(newX, newY, this)))
    {
        moveTo(newX, newY);
    }
}

int Penelope::getNumFlameCharges()
{
    return m_numFlameCharges;
}

int Penelope::getNumLandmines()
{
    return m_numLandmines;
}

int Penelope::getNumVaccines()
{
    return m_numVaccines;
}

void Penelope::increaseVaccines()
{
    m_numVaccines++;
}

void Penelope::increaseFlameCharges()
{
    m_numFlameCharges += 5;
}

void Penelope::increaseLandmines()
{
    m_numLandmines++;
}

void Penelope::useExitIfAppropriate()
{
    getWorld()->recordLevelFinishedIfAllCitizensGone();
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    setDead();
}

bool Penelope::triggersCitizens() const
{
    return true;
}

void Penelope::pickUpGoodieIfAppropriate(Goodie* g)
{
    g->pickUp(this);
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(50);
}

//================================================== Citizen ======================================================
Citizen::Citizen(double x, double y, StudentWorld* world)
: Human(IID_CITIZEN, x, y, world)
{
    m_isParalyzed = false;
}

void Citizen::beVomitedOnIfAppropriate()
{
    if (!isInfected())
        getWorld()->playSound(SOUND_CITIZEN_INFECTED);
    Human::beVomitedOnIfAppropriate();
}

void Citizen::doSomething()
{
    if (isDead())
        return;
    dealWithInfection();
    if (!m_isParalyzed)
    {
        move();
    }
    m_isParalyzed = !m_isParalyzed;
}

void Citizen::move()
{
    double PennyX;
    double PennyY;
    double PennyDist;
    double zombieX;
    double zombieY;
    double zombieDist;
    
    bool PennyExists = getWorld()->locateNearestCitizenTrigger(getX(), getY(), PennyX, PennyY, PennyDist, false);
    
    bool zombieExists = getWorld()->locateNearestCitizenTrigger(getX(), getY(), zombieX, zombieY, zombieDist, true);
    
    if (PennyExists)
    {
        if ((!zombieExists || (zombieExists && PennyDist < zombieDist)) && PennyDist <= 80){
            if (getX() == PennyX)
            {
                double newY = PennyY > getY() ? getY() + 2 : getY() - 2;
                if (!getWorld()->isAgentMovementBlockedAt(getX(), newY, this))
                {
                    setDirection(PennyY > getY() ? up : down);
                    moveTo(getX(), newY);
                    return;
                }
            }
            else if (getY() == PennyY)
            {
                double newX = PennyX > getX() ? getX() + 2 : getX() - 2;
                if (!getWorld()->isAgentMovementBlockedAt(newX, getY(), this))
                {
                    setDirection(PennyX > getX() ? right : left);
                    moveTo(newX, getY());
                    return;
                }
            }
            else
            {
                Direction lati = PennyX > getX() ? right: left;
                Direction longi = PennyY > getY() ? up: down;
                int r = rand() % 2;
                if (r == 0)
                {
                    double newX = lati == right ? getX() + 2 : getX() - 2;
                    if (!getWorld()->isAgentMovementBlockedAt(newX, getY(), this))
                    {
                        setDirection(lati);
                        moveTo(newX, getY());
                        return;
                    }
                }
                double newY = longi == up ? getY() + 2 : getY() - 2;
                if (!getWorld()->isAgentMovementBlockedAt(getX(), newY, this))
                {
                    setDirection(longi);
                    moveTo(getX(), newY);
                    return;
                }
            }
        }
    }
    if (zombieExists)
    {
        if (zombieDist <= 80)
        {
            Direction bestDir;
            double newDist = -10;
            double currDist;
            double newX;
            double newY;
            
            // right
            if (!getWorld()->isAgentMovementBlockedAt(getX() + 2, getY(), this))
            {
                //calculate new dist
                currDist = sqrt(pow(zombieX - (getX() + 2), 2) + pow(zombieY - getY(), 2));
                //if no good direction yet or new dist is greater than the original dist
                if (newDist == -10 || currDist > newDist)
                {
                    //set the best direction and set the new dist
                    bestDir = right;
                    newDist = currDist;
                    newX = getX() + 2;
                    newY = getY();
                }
            }
            // left
            if (!getWorld()->isAgentMovementBlockedAt(getX() - 2, getY(), this))
            {
                currDist = sqrt(pow(zombieX - (getX() - 2), 2) + pow(zombieY - getY(), 2));
                if (newDist == -10 || currDist > newDist)
                {
                    bestDir = left;
                    newDist = currDist;
                    newX = getX() - 2;
                    newY = getY();
                }
            }
            // up
            if (!getWorld()->isAgentMovementBlockedAt(getX(), getY() + 2, this))
            {
                currDist = sqrt(pow(zombieX - getX(), 2) + pow(zombieY - (getY()+2), 2));
                if (newDist == -10 || currDist > newDist){
                    bestDir = up;
                    newDist = currDist;
                    newX = getX();
                    newY = getY() + 2;
                }
            }
            // down
            if (!getWorld()->isAgentMovementBlockedAt(getX(), getY() - 2, this))
            {
                currDist = sqrt(pow(zombieX - getX(), 2) + pow(zombieY - (getY()-2), 2));
                if (newDist == -10 || currDist > newDist){
                    bestDir = down;
                    newDist = currDist;
                    newX = getX();
                    newY = getY() - 2;
                }
            }
            if (newDist != -10)
            {
                setDirection(bestDir);
                moveTo(newX, newY);
            }
        }
    }
}

void Citizen::useExitIfAppropriate()
{
    if (isDead())
        return;
    setDead();
    getWorld()->increaseScore(500);
    getWorld()->playSound(SOUND_CITIZEN_SAVED);
    getWorld()->recordCitizenGone();
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    if (isDead())
        return;
    setDead();
    getWorld()->increaseScore(-1000);
    getWorld()->playSound(SOUND_CITIZEN_DIE);
    getWorld()->recordCitizenGone();
}

void Citizen::dieByInfection()
{
    setDead();
    getWorld()->increaseScore(-1000);
    getWorld()->playSound(SOUND_ZOMBIE_BORN);
    getWorld()->citizenZombiefied(this);
    int chance = rand() % 10;
    if (chance >= 0 && chance < 7)
    {
        getWorld()->addActor(new DumbZombie(getX(), getY(), getWorld()));
    }
    else
    {
        getWorld()->addActor(new SmartZombie(getX(), getY(), getWorld()));
    }
}

//================================================== Zombie =======================================================
Zombie::Zombie(double x, double y, StudentWorld* world)
: Agent(IID_ZOMBIE, x, y, world)
{
    m_isParalyzed = false;
}

bool Zombie::threatensCitizens() const
{
    return true;
}

void Zombie::vomit() const
{
    int vomitX = getX();
    int vomitY = getY();
    switch (getDirection()){
        case up:
            vomitY += SPRITE_HEIGHT;
            break;
        case down:
            vomitY -= SPRITE_HEIGHT;
            break;
        case left:
            vomitX -= SPRITE_WIDTH;
            break;
        case right:
            vomitX += SPRITE_WIDTH;
            break;
    }
    
    double personX;
    double personY;
    double minDistance;
    
    getWorld()->locateNearestVomitTrigger(vomitX, vomitY, personX, personY, minDistance);
    if (minDistance <= 10)
    {
        int chance = rand() % 3;
        if (chance == 0)
        {
            getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
            if (!(getWorld()->isVomitBlockedAt(vomitX, vomitY)))
            {
                getWorld()->addActor(new Vomit(vomitX, vomitY, getWorld(), getDirection()));
            }
            return;
        }
    }
}

void Zombie::doSomething()
{
    if (isDead())
        return;
    if (!m_isParalyzed)
    {
        vomit();
        move();
    }
    m_isParalyzed = !m_isParalyzed;
}

//================================================ DumbZombie =====================================================
DumbZombie::DumbZombie(double x, double y, StudentWorld* world)
: Zombie(x, y, world)
{
    m_distance = 0;
}

void DumbZombie::move()
{
    if (m_distance == 0)
    {
        m_distance = rand() % 8 + 3;
        int dir = rand() % 4;
        switch(dir)
        {
            case 0:
                setDirection(up);
                break;
            case 1:
                setDirection(down);
                break;
            case 2:
                setDirection(left);
                break;
            case 3:
                setDirection(right);
                break;
        }
    }
    double newX = getX();
    double newY = getY();
    switch (getDirection())
    {
        case up:
            newY += 1;
            break;
        case down:
            newY -= 1;
            break;
        case left:
            newX -= 1;
            break;
        case right:
            newX += 1;
            break;
    }
    if (!getWorld()->isAgentMovementBlockedAt(newX, newY, this))
    {
        moveTo(newX, newY);
        m_distance--;
    }
    else
    {
        m_distance = 0;
    }
    
}

void DumbZombie::dieByFallOrBurnIfAppropriate()
{
    if (isDead())
        return;
    
    setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(1000);

    int chance = rand() % 10;
    if (chance == 0)
    {
        int dir = rand() % 4;
        double newX = getX();
        double newY = getY();
        switch (dir)
        {
            case 0:
                newY += SPRITE_HEIGHT;
                break;
            case 1:
                newY -= SPRITE_HEIGHT;
                break;
            case 2:
                newX -= SPRITE_WIDTH;
                break;
            case 3:
                newX += SPRITE_WIDTH;
                break;
        }
        VaccineGoodie* vaccine = new VaccineGoodie(newX, newY, getWorld());
    }
}

//================================================ SmartZombie ====================================================
SmartZombie::SmartZombie(double x, double y, StudentWorld* world)
: Zombie(x, y, world)
{
    m_distance = 0;
}

void SmartZombie::move()
{
    if (m_distance == 0)
    {
        m_distance = rand() % 8 + 3;
        double personX;
        double personY;
        double minDistance;
        
        getWorld()->locateNearestVomitTrigger(getX(), getY(), personX, personY, minDistance);
        if (minDistance <= 80)
        {
            if (personX == getX())
            {
                Direction dir = personY > getY() ? up: down;
                setDirection(dir);
            }
            else if (personY == getY())
            {
                Direction dir = personX > getX() ? right: left;
                setDirection(dir);
            }
            else
            {
                Direction lati = personX > getX() ? right : left;
                Direction longi = personY > getY() ? up : down;
                int chance = rand() % 2;
                if (chance == 0)
                {
                    setDirection(lati);
                }
                else
                {
                    setDirection(longi);
                }
            }
        }
        else
        {
            int dir = rand() % 4;
            switch(dir)
            {
                case 0:
                    setDirection(up);
                    break;
                case 1:
                    setDirection(down);
                    break;
                case 2:
                    setDirection(left);
                    break;
                case 3:
                    setDirection(right);
                    break;
            }
        }
    }
    int newX = getX();
    int newY = getY();
    switch (getDirection())
    {
        case up:
            newY += 1;
            break;
        case down:
            newY -= 1;
            break;
        case left:
            newX -= 1;
            break;
        case right:
            newX += 1;
            break;
    }
    
    if (!(getWorld()->isAgentMovementBlockedAt(newX, newY, this)))
    {
        moveTo(newX, newY);
        m_distance--;
    }
    else
    {
        m_distance = 0;
    }
}

void SmartZombie::dieByFallOrBurnIfAppropriate()
{
    if (isDead())
        return;
    setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(2000);
}
