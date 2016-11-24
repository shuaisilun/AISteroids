#pragma once
#include "AIControl.h"

class Ship;
class FSMMachine;
class GameObj;

#define POWERUP_SCAN_DIST 180.0f
#define APPROACH_DIST     180.0f
#define HUNTING_DIST	  250.0f
#define MAX_HUNTING_LEVEL	  9

class FSMAIControl: public AIControl
{
public:
    //constructor/functions
    FSMAIControl(Ship* ship = NULL);
    void Update(float dt);
    void UpdatePerceptions(float dt);
    void Init();
    
    //perception data 
    //(public so that states can share it)
    GameObj* m_nearestAsteroid;
    GameObj* m_nearestPowerup;
    short m_asteroidCount;
    float       m_nearestAsteroidDist;
    float       m_nearestPowerupDist;
    bool        m_willCollide;
    bool        m_powerupNear;
    float       m_safetyRadius;
    float       m_maxSpeed;
	int			m_waveNumber;
    
protected:
    //data
    FSMMachine* m_machine;

};
