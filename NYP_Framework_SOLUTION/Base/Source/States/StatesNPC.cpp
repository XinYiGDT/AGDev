#include "StatesNPC.h"
#include "../PlayerInfo/PlayerInfo.h"

StateNpcRoam::StateNpcRoam(const std::string & stateID, CEnemy * go)
	: State(stateID),
	m_go(go)
{
}

StateNpcRoam::~StateNpcRoam()
{
}

void StateNpcRoam::Enter()
{
}

void StateNpcRoam::Update(double dt)
{
	Vector3 viewVector = (m_go->GetTarget() - m_go->GetPos()).Normalized();
	if (m_go->GetIsMoving()) //move
	{
		Vector3 newPos = m_go->GetPos() += viewVector *(float)m_go->GetSpeed() * (float)dt;
		m_go->SetPos(newPos);
	}

	//contrain the position
	m_go->Constrain();

	
	if ((CPlayerInfo::GetInstance()->GetPos() - m_go->GetPos()).LengthSquared() <= 5000.0f) //set target - player
	{
		//set statemachine chase
		m_go->SetTarget(CPlayerInfo::GetInstance()->GetPos());	//set player as target
		m_go->sm->SetNextState("Chase");						//change state to chase
	}
	else if ((m_go->GetTarget() - m_go->GetPos()).LengthSquared() < 25.0f) //set target - waypoint
	{
		CWaypoint* nextWaypoint = m_go->GetNextWaypoint();
		if (nextWaypoint)
			m_go->SetTarget(nextWaypoint->GetPosition());
		else
			m_go->SetTarget(Vector3(0, 0, 0));
		cout << "Next target: " << m_go->GetTarget() << endl;
	}
}

void StateNpcRoam::Exit()
{
}

StateNpcChase::StateNpcChase(const std::string & stateID, CEnemy * go)
	: State(stateID),
	m_go(go)
{
}

StateNpcChase::~StateNpcChase()
{
}

void StateNpcChase::Enter()
{
}

void StateNpcChase::Update(double dt)
{
	Vector3 viewVector = (m_go->GetTarget() - m_go->GetPos()).Normalized();
	if (m_go->GetIsMoving()) //move
	{
		Vector3 newPos = m_go->GetPos() += viewVector *(float)m_go->GetSpeed() * (float)dt;
		m_go->SetPos(newPos);
	}

	//contrain the position
	m_go->Constrain();

	if ((CPlayerInfo::GetInstance()->GetPos() - m_go->GetPos()).LengthSquared() > 5000.0f) //set target - player
	{
		m_go->sm->SetNextState("Roam");
	}
}

void StateNpcChase::Exit()
{
}
