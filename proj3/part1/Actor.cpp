#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//================================================= Actor =========================================================
Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth)
: GraphObject(imageID, x, y)
{
    m_worldPtr = w;
}

bool Actor::isDead() const
{
    return false;
}

void Actor::setDead()
{
}

StudentWorld* Actor::getWorld() const
{
    return m_worldPtr;
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

bool Actor::triggersOnlyActiveLandmines() const
{
    return false;
}

bool Actor::triggersZombieVomit() const
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
//================================================== Wall =========================================================
Wall::Wall(StudentWorld* w, double x, double y)
: Actor(w, IID_WALL, x, y, right, 0)
{
}

void Wall::doSomething()
{
    return;
}

bool Wall::blocksMovement() const
{
    return true;
}
bool Wall::blocksFlame() const
{
    return true;
}

//============================================ ActivatingObject ===================================================
ActivatingObject::ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir)
: Actor(w, imageID, x, y, dir, depth)
{
}

//================================================== Exit =========================================================
Exit::Exit(StudentWorld* w, double x, double y)
: ActivatingObject(w, IID_EXIT, x, y, 0, right)
{
}

void Exit::doSomething()
{
}

void Exit::activateIfAppropriate(Actor* a)
{
}

bool Exit::blocksFlame() const
{
    return false;
}

//================================================== Pit ==========================================================
Pit::Pit(StudentWorld* w, double x, double y)
: ActivatingObject(w, IID_PIT, x, y, 0, right)
{
}

void Pit::doSomething()
{
    return;
}
void Pit::activateIfAppropriate(Actor* a)
{
    return;
}

//================================================= Flame =========================================================
Flame::Flame(StudentWorld* w, double x, double y, int dir)
: ActivatingObject(w, IID_FLAME, x, y, 0, dir)
{
}

void Flame::doSomething()
{
    return;
}

void Flame::activateIfAppropriate(Actor* a)
{
    return;
}

//================================================= Vomit =========================================================
Vomit::Vomit(StudentWorld* w, double x, double y, int dir)
: ActivatingObject(w, IID_VOMIT, x, y, 0, dir)
{
}

void Vomit::doSomething()
{
    return;
}

void Vomit::activateIfAppropriate(Actor* a)
{
    return;
}

//=============================================== Landmine ========================================================
Landmine::Landmine(StudentWorld* w, double x, double y)
: ActivatingObject(w, IID_LANDMINE, x, y, 1, right)
{
}
void Landmine::doSomething()
{
    return;
}
void Landmine::activateIfAppropriate(Actor* a)
{
    return;
}
void Landmine::dieByFallOrBurnIfAppropriate()
{
    return;
}

//================================================ Goodie =========================================================
Goodie::Goodie(StudentWorld* w, int imageID, double x, double y)
: ActivatingObject(w, imageID, x, y, 1, right)
{
}

void Goodie::activateIfAppropriate(Actor* a)
{
    return;
}
void Goodie::dieByFallOrBurnIfAppropriate()
{
    return;
}

//============================================ VaccineGoodie ======================================================
VaccineGoodie::VaccineGoodie(StudentWorld* w, double x, double y)
: Goodie(w, IID_VACCINE_GOODIE, x, y)
{
}

void VaccineGoodie::doSomething()
{
    return;
}
void VaccineGoodie::pickUp(Penelope* p)
{
    return;
}

//============================================= GasCanGoodie ======================================================
GasCanGoodie::GasCanGoodie(StudentWorld* w, double x, double y)
: Goodie(w, IID_GAS_CAN_GOODIE, x, y)
{
}

void GasCanGoodie::doSomething()
{
    return;
}

void GasCanGoodie::pickUp(Penelope* p)
{
    return;
}

//============================================ LandmineGoodie =====================================================
LandmineGoodie::LandmineGoodie(StudentWorld* w, double x, double y)
: Goodie(w, IID_LANDMINE_GOODIE, x, y)
{
}

void LandmineGoodie::doSomething()
{
    return;
}

void LandmineGoodie::pickUp(Penelope* p)
{
    return;
}

//================================================= Agent =========================================================
Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir)
: Actor(w, imageID, x, y, dir, 0)
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

//================================================= Human =========================================================
Human::Human(StudentWorld* w, int imageID, double x, double y)
: Agent(w, imageID, x, y, right)
{
}

void Human::beVomitedOnIfAppropriate()
{
    return;
}

bool Human::triggersZombieVomit() const
{
    return true;
}

void Human::clearInfection()
{
    return;
}

int Human::getInfectionDuration() const
{
    return 0;
}
//================================================ Penelope =======================================================
Penelope::Penelope(StudentWorld* w, double x, double y)
: Human(w, IID_PLAYER, x, y)
{
}

void Penelope::doSomething()
{
    int ch;
    if (getWorld()->getKey(ch))
    {
        // user hit a key during this tick!
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(left);
                if (getX() <= 0)
                    break;
                if ((getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() - 12)) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() - 8)) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() - 4)) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() )) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() + 4)) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() + 8)) ||
                    (getWorld()->barrierAt(getX() - SPRITE_WIDTH, getY() + 12)))
                    break;
                moveTo(getX() - 4, getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if (getX() >= VIEW_WIDTH - 17)
                    break;
                if ((getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() - 12)) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() - 8)) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() - 4)) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() )) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() + 4)) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() + 8)) ||
                    (getWorld()->barrierAt(getX() + SPRITE_WIDTH, getY() + 12)))
                    break;
                moveTo(getX() + 4, getY());
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                if (getY() >= VIEW_HEIGHT - 17)
                    break;
                if ((getWorld()->barrierAt(getX() - 12, getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() - 8, getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() - 4, getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX(), getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 4, getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 8, getY() + SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 12, getY() + SPRITE_HEIGHT)))
                    break;
                moveTo(getX(), getY() + 4);
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if (getY() <= 0)
                    break;
                if ((getWorld()->barrierAt(getX() - 12, getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() - 8, getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() - 4, getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX(), getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 4, getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 8, getY() - SPRITE_HEIGHT)) ||
                    (getWorld()->barrierAt(getX() + 12, getY() - SPRITE_HEIGHT)))
                    break;
                moveTo(getX(), getY() - 4);
                break;
        }
    }
}

void Penelope::useExitIfAppropriate()
{
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    return;
}

void Penelope::pickUpGoodieIfAppropriate(Goodie* g)
{
    return;
}

void Penelope::increaseVaccines()
{
    return;
}

void Penelope::increaseFlameCharges()
{
    return;
}

void Penelope::increaseLandmines()
{
    return;
}

int Penelope::getNumVaccines() const
{
    return 0;
}

int Penelope::getNumFlameCharges() const
{
    return 0;
}

int Penelope::getNumLandmines() const
{
    return 0;
}

//================================================= Citizen =======================================================
Citizen::Citizen(StudentWorld* w,  double x, double y)
: Human(w, IID_CITIZEN, x, y)
{
}

void Citizen::doSomething()
{
}

void Citizen::useExitIfAppropriate()
{
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
}

//================================================= Zombie ========================================================
Zombie::Zombie(StudentWorld* w,  double x, double y)
: Agent(w, IID_ZOMBIE, x, y, right)
{
}

//=============================================== DumbZombie ======================================================
DumbZombie::DumbZombie(StudentWorld* w,  double x, double y)
: Zombie(w, x, y)
{
}

void DumbZombie::doSomething()
{
}

void DumbZombie::dieByFallOrBurnIfAppropriate()
{
}

//=============================================== SmartZombie =====================================================
SmartZombie::SmartZombie(StudentWorld* w,  double x, double y)
: Zombie(w, x, y)
{
}

void SmartZombie::doSomething()
{
}

void SmartZombie::dieByFallOrBurnIfAppropriate()
{
}
