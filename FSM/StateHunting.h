#pragma once

#include "FSMState.h"
#include "Ship.h"

class StateHunting : public FSMState
{
public:
	StateHunting(Control* parent) : FSMState(FSM_STATE_HUNTING, parent) {};
	~StateHunting();

	void Update(float dt);
	int CheckTransitions();
	void Exit();

private:
	float computeRotateAng(Ship*, GameObj*,float,float &);
};
