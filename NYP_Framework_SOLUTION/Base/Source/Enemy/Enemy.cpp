#include "Enemy.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../Waypoint/WaypointManager.h"

CEnemy::CEnemy()
	: GenericEntity(NULL)
	, defaultPosition(Vector3(0.0f, 0.0f, 0.0f))
	, defaultTarget(Vector3(0.0f, 0.0f, 0.0f))
	, defaultUp(Vector3(0.0f, 0.0f, 0.0f))
	, target(Vector3(0.0f, 0.0f, 0.0f))
	, up(Vector3(0.0f, 0.0f, 0.0f))
	, maxBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, minBoundary(Vector3(0.0f, 0.0f, 0.0f))
	, m_pTerrain(NULL)
	, isMoving(false)
	, m_iWayPointIndex(-1)
{
	listOfWaypoints.clear();
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init(bool _isMoving)
{
	//set the default values
	defaultPosition.Set(0, 0, 10);
	defaultTarget.Set(0, 0, 0);
	defaultUp.Set(0, 1, 0);

	//Set up the waypoints
	listOfWaypoints.push_back(0);
	listOfWaypoints.push_back(1);
	listOfWaypoints.push_back(2);

	m_iWayPointIndex = 0;

	//set the current values
	position.Set(10.0f, 0.0f, 0.0f);
	scale.Set(3.f, 6.f, 3.f);
	//target.Set(10.0f, 0.0f, 450.0f);
	CWaypoint* nextWaypoint = GetNextWaypoint();
	if (nextWaypoint)
		target = nextWaypoint->GetPosition();
	else
		target = Vector3(0, 0, 0);
	cout << "Next target: " << target << endl;
	up.Set(0.0f, 1.0f, 0.0f);

	//set boundary
	maxBoundary.Set(1.0f, 1.0f, 1.0f);
	minBoundary.Set(-1.0f, -1.0f, -1.0f);

	//set speed
	m_dSpeed = 50.0;

	//initialise the LOD meshes
	InitLOD("sphere", "sphere2", "sphere3");

	//initialise the collider
	this->SetCollider(true);
	this->SetAABB(Vector3(1.5, 3, 1.5), Vector3(-1.5, -3, -1.5));

	//add to entitymanager
	EntityManager::GetInstance()->AddEntity(this, true);
	theMainNode = CSceneGraph::GetInstance()->AddNode(this);

	isMoving = _isMoving;
}

void CEnemy::Reset(void)
{
	//set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void CEnemy::SetPos(const Vector3 & _pos)
{
	position = _pos;
}

void CEnemy::SetTarget(const Vector3 & _target)
{
	this->target = _target;
}

void CEnemy::SetUp(const Vector3 & _up)
{
	this->up = _up;
}

void CEnemy::SetBoundary(Vector3 _max, Vector3 _min)
{
	maxBoundary = _max;
	minBoundary = _min;
}

void CEnemy::SetTerrain(GroundEntity * _m_pTerrain)
{
	if (_m_pTerrain != NULL)
	{
		this->m_pTerrain = _m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
	}
}

Vector3 CEnemy::GetPos(void) const
{
	return position;
}

Vector3 CEnemy::GetTarget(void) const
{
	return target;
}

Vector3 CEnemy::GetUP(void) const
{
	return up;
}

GroundEntity * CEnemy::GetTerrain(void) const
{
	return m_pTerrain;
}

CWaypoint * CEnemy::GetNextWaypoint(void)
{
	if ((int)listOfWaypoints.size() > 0)
	{
		m_iWayPointIndex++;
		if (m_iWayPointIndex >= (int)listOfWaypoints.size())
			m_iWayPointIndex = 0;
		return CWaypointManager::GetInstance()->GetWaypoint(listOfWaypoints[m_iWayPointIndex]);
	}
	else
		return NULL;
}

void CEnemy::Update(double dt)
{
	Vector3 viewVector = (target - position).Normalized();
	if (isMoving)
	{
		position += viewVector * (float)m_dSpeed * (float)dt;

	}

	//contrain the position
	Constrain();

	//update the target
	/*if (position.z > 300.f)
		target.z = position.z * -1;
	else if (position.z < -300.f)
		target.z = position.z * -1;*/

	if ((target - position).LengthSquared() < 25.0f)
	{
		CWaypoint* nextWaypoint = GetNextWaypoint();
		if (nextWaypoint)
			target = nextWaypoint->GetPosition();
		else
			target = Vector3(0, 0, 0);
		cout << "Next target: " << target << endl;
	}
}

void CEnemy::Constrain(void)
{
	//contrain the player within the boundary
	if (position.x > maxBoundary.x - 1.0f)
		position.x = maxBoundary.x - 1.0f;
	if (position.z > maxBoundary.z - 1.0f)
		position.z = maxBoundary.z - 1.0f;

	if (position.x < minBoundary.x + 1.0f)
		position.x = minBoundary.x + 1.0f;
	if (position.z < minBoundary.z + 1.0f)
		position.z = minBoundary.z + 1.0f;

	//if the y position is not equal to terrain height at that position
	//then update y position to the terrain height
	if (position.y != m_pTerrain->GetTerrainHeight(position))
		position.y = m_pTerrain->GetTerrainHeight(position);
}

void CEnemy::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);

	if (GetLODStatus() == true)
	{
		if (theDetailLevel != NO_DETAILS)
		{
			//cout << theDetailLevel << endl;
			RenderHelper::RenderMesh(GetLODMesh());
		}
	}
	modelStack.PopMatrix();
}
