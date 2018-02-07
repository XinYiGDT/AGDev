#ifndef STATES_NPC
#define STATES_NPC

#include "State.h"
#include "../Enemy/Enemy.h"
#include <vector>

class StateNpcRoam : public State
{
	CEnemy *m_go;
public:
	StateNpcRoam(const std::string &stateID, CEnemy *go);
	virtual ~StateNpcRoam();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

class StateNpcChase : public State
{
	CEnemy *m_go;
public:
	StateNpcChase(const std::string &stateID, CEnemy *go);
	virtual ~StateNpcChase();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};
#endif