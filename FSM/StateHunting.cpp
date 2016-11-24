#include "StateHunting.h"
#include "Ship.h"
#include "FSMAIControl.h"
#include "utility.h"
#include "GameSession.h"

using namespace cyclone;

void StateHunting::Update(float dt)
{
	FSMAIControl* parent = (FSMAIControl*)m_parent;
	Ship* ship = parent->m_ship;
	GameObj* asteroid = parent->m_nearestAsteroid;

	float angDelta;
	float rotateAngle = computeRotateAng(ship,asteroid,parent->m_nearestAsteroidDist,angDelta);

	if (rotateAngle != 0)
		ship->rotateShip(rotateAngle);

	float speed = ship->getVelocity().magnitude();

	if (speed > AI_MAX_SPEED_TRY && parent->m_nearestAsteroidDist < AI_APPROACH_DIST)
		ship->ThrustReverse();
	else if (parent->m_nearestAsteroidDist > parent->m_nearestAsteroid->m_size + 20 && speed < AI_DANGEROUS_SPEED)
		fabsf(angDelta) < 3 ? ship->ThrustOn() : ship->ThrustReverse();
	else 
		ship->ThrustOff();
		

	parent->m_target->setPosition(asteroid->getPosition());
	parent->m_debugTxt = "Hunting";
}

float StateHunting::computeRotateAng(Ship* ship, GameObj* asteroid,float nearestDist, float& targetAngle)
{
	Vector3 futureAstPosition = asteroid->getPosition();
	Vector3 deltaFPos = futureAstPosition - ship->getPosition();
	deltaFPos.normalise();

	float newDir = CALCDIR(deltaFPos);
	float angDelta = CLAMPDIR180(ship->GetClosestGunAngle(newDir) - newDir);
	angDelta *= -1;

	angDelta = angDelta * M_PI / 180;

	targetAngle = angDelta;

	if (angDelta < 0)
	{
		return MAX(angDelta, -1*AngularStepAcceleration);
	}
	else {
		return MIN(angDelta, AngularStepAcceleration);
	}
	return 0;
}

int StateHunting::CheckTransitions()
{
	FSMAIControl* parent = (FSMAIControl*)m_parent;

	if (parent->m_willCollide)
		return FSM_STATE_EVADE;

	if (parent->m_nearestAsteroidDist <= APPROACH_DIST)
		return FSM_STATE_ATTACK;

	return FSM_STATE_HUNTING;
}

void StateHunting::Exit()
{
	
}