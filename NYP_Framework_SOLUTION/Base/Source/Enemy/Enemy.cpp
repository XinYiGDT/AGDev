#include "Enemy.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

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
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init(void)
{
	//set the default values
	defaultPosition.Set(0, 0, 10);
	defaultTarget.Set(0, 0, 0);
	defaultUp.Set(0, 1, 0);

	//set the current values
	position.Set(10.0f, 0.0f, 0.0f);
	target.Set(10.0f, 0.0f, 450.0f);
	up.Set(0.0f, 1.0f, 0.0f);

	//set boundary
	maxBoundary.Set(1.0f, 1.0f, 1.0f);
	minBoundary.Set(-1.0f, -1.0f, -1.0f);

	//set speed
	m_dSpeed = 25.0;

	//initialise the LOD meshes
	//InitLOD("cube", "sphere", "cubeSG");

	//initialise the collider
	this->SetCollider(true);
	this->SetAABB(Vector3(1, 1, 1), Vector3(-1, -1, -1));

	//add to entitymanager
	EntityManager::GetInstance()->AddEntity(this, true);
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

void CEnemy::Update(double dt)
{
	Vector3 viewVector = (target - position).Normalized();
	position += viewVector * (float)m_dSpeed * (float)dt;
	//cout << position << "..." << viewVector << endl;

	//contrain the position
	Constrain();

	//update the target
	if (position.z > 400.f)
		target.z = position.z * -1;
	else if (position.z < -400.f)
		target.z = position.z * -1;
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

void CEnemy::enemyModel()
{
	Vector3 enemyPos[] = { Vector3(1,0,0), Vector3(0,0,1), Vector3(-1,0,0), Vector3(0,0,-1),  Vector3(1,0,1),Vector3(-1,0,1),Vector3(1,0,-1),Vector3(-1,0,-1) };

	int random = Math::RandFloatMinMax(0, 7);


	GenericEntity* headCube = Create::Entity("cubeHead", Vector3(-20.0f, 5.0f, -20.0f), Vector3(2.0f, 2.0f, 2.0f));
	headCube->SetCollider(true);
	headCube->SetAABB(Vector3(1.f, 1.f, 1.f), Vector3(-1.f, -1.f, -1.f));
	headCube->InitLOD("cubeHead", "sphere", "cubeSG"); //high, mid, low

									//add the pointer to this new entity to the scene graph
	CSceneNode* theNode = CSceneGraph::GetInstance()->AddNode(headCube);
	if (theNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}


	CUpdateTransformation* movement = new CUpdateTransformation();
	movement->ApplyUpdate(enemyPos[random].x, enemyPos[random].y, enemyPos[random].z);
	movement->SetSteps(-10, 10);
	theNode->SetUpdateToTransformation(movement);


	GenericEntity* bodyCube = Create::Entity("cube", Vector3(-20.0f, 1.1f, -20.0f), Vector3(3.0f, 6.0f, 3.0f));
	bodyCube->SetCollider(true);
	bodyCube->SetAABB(Vector3(1.5f, 3.f, 1.5f), Vector3(-1.5f, -3.f, -1.5f));
	//add the pointer to this new entity to the scene graph
	CSceneNode* anotherNode = theNode->AddChild(bodyCube);
	if (anotherNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}

	GenericEntity* leftArmCube = Create::Entity("cubeSG", Vector3(-22.0f, 1.8f, -20.0f), Vector3(1.0f, 4.0f, 2.0f));
	leftArmCube->SetCollider(true);
	leftArmCube->SetAABB(Vector3(0.5f, 2.f, 1.f), Vector3(-0.5f, -2.f, -1.f));
	//add the pointer to this new entity to the scene graph
	CSceneNode* leftArmNode = anotherNode->AddChild(leftArmCube);
	if (leftArmNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}

	GenericEntity* rightArmCube = Create::Entity("cubeSG", Vector3(-18.0f, 1.8f, -20.0f), Vector3(1.0f, 4.0f, 2.0f));
	rightArmCube->SetCollider(true);
	rightArmCube->SetAABB(Vector3(0.5f, 2.0f, 1.0f), Vector3(-0.5f, -2.0f, -1.0f));
	//add the pointer to this new entity to the scene graph
	CSceneNode* rightArmNode = anotherNode->AddChild(rightArmCube);
	if (rightArmNode == NULL)
	{
		cout << "EntityManager::AddEntity: Unable to add to scene graph!" << endl;
	}
}

void CEnemy::Render(void)
{
	/*MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);*/

	if (GetLODStatus() == true)
	{
			if (theDetailLevel != NO_DETAILS)
			{
				//cout << theDetailLevel << endl;
				if (i < 1)
				{
					enemyModel();
					i++;
				}
				else
				{
					theDetailLevel = NO_DETAILS;
				}

			}
			else
			{
				int a = 0;
			}
		
	}
	//modelStack.PopMatrix();
}
