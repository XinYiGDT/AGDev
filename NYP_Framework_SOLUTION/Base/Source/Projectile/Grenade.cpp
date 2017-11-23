#include "Grenade.h"

#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "GL\glew.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "../SceneGraph.h"

#include <iostream>
using namespace std;

CGrenade::CGrenade()
	: CProjectile(NULL)
	, m_fGravity(-10.0f)
	, m_fElapsedTime(0.0f)
	, m_pTerrain(NULL)
{
}

CGrenade::CGrenade(Mesh * _modelMesh)
	: CProjectile(_modelMesh)
	, m_fGravity(-10.0f)
	, m_fElapsedTime(0.0f)
	, m_pTerrain(NULL)
{
}

CGrenade::~CGrenade()
{
	m_pTerrain = NULL; //cant delete this as the terrain is deleted in Cplayerinfo
	modelMesh = NULL;
	theSource = NULL;
}

void CGrenade::Update(double dt)
{
	if (m_bStatus == false)
		return;

	//update the TimeLife of projectile. set to inactive if too long
	m_fLifetime -= (float)dt;
	if (m_fLifetime < 0.0f)
	{
		SetStatus(false);
		SetIsDone(true);

		vector<EntityBase*> ExportList = CSpatialPartition::GetInstance()->GetObjects(position, 1.0f);
		for (int i = 0; i < ExportList.size(); ++i)
		{
			// Remove from Scene Graph
			if (CSceneGraph::GetInstance()->DeleteNode(ExportList[i]) == true)
			{
				cout << "*** This Entity removed ***" << endl;
			}
		}
		
		return;
	}

	//check if the grenade is already on the ground
	if (position.y >= m_pTerrain->GetTerrainHeight(position) - 10.0f + Math::EPSILON)
	{
		//update position
		m_fElapsedTime += dt;

		position.Set(	position.x + (float)(theDirection.x * m_fElapsedTime * m_fSpeed),
						position.y + (float)(theDirection.y * m_fElapsedTime * m_fSpeed) + (0.5 * m_fGravity * m_fElapsedTime * m_fElapsedTime),
						position.z + (float)(theDirection.z * m_fElapsedTime * m_fSpeed));

		if (position.y < m_pTerrain->GetTerrainHeight(position) - 10.0f)
		{
			position.y = m_pTerrain->GetTerrainHeight(position) - 10.0f;
			m_fSpeed = 0.0f;
			return;
		}
	}
}

void CGrenade::SetTerrain(GroundEntity* m_pTerrain)
{
	this->m_pTerrain = m_pTerrain;
}

CGrenade * Create::Grenade(		const std::string & _meshName, 
								const Vector3 & _position, 
								const Vector3 & _direction, 
								const float m_fLifetime, 
								const float m_fSpeed, 
								CPlayerInfo * _source)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CGrenade* result = new CGrenade(modelMesh);
	result->Set(_position, _direction, m_fLifetime, m_fSpeed);
	result->SetStatus(true);
	result->SetCollider(true);
	result->SetSource(_source);
	result->SetTerrain(_source->GetTerrain());
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}
