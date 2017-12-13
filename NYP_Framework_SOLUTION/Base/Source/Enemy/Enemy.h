#pragma once
#include "../GenericEntity.h"
#include "../GroundEntity.h"

#include "../SceneGraph.h"

class Mesh;

class CEnemy : public GenericEntity
{
public:
	CEnemy();
	virtual ~CEnemy();

	void Init(void);
	//Reset this player instance to default
	void Reset(void);


	//Scene graph
	// Add a Node to this Scene Graph
	CSceneNode* AddNode(EntityBase* theEntity = NULL);
	// Delete a Node from this Scene Graph using the pointer to the node
	bool DeleteNode(EntityBase* theEntity);
	// Generate an ID for a Scene Node
	int GenerateID(void);

	CSceneNode* theRoot;


	//set position
	void SetPos(const Vector3& _pos);
	//set target
	void SetTarget(const Vector3& _target);
	//set up
	void SetUp(const Vector3& _up);
	//set the boundary for the player info
	void SetBoundary(Vector3 _max, Vector3 _min);
	//set the terrain for the player info
	void SetTerrain(GroundEntity* m_pTerrain);

	//get position
	Vector3 GetPos(void)const;
	//get target
	Vector3 GetTarget(void)const;
	//get up
	Vector3 GetUP(void)const;
	//get the terrain for the player info
	GroundEntity* GetTerrain(void)const;

	//update
	void Update(double dt = 0.0333f);

	//constrain the position within the borders
	void Constrain(void);
	//render
	void Render(void);

	void enemyModel();

protected:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;
	int i = 0;

	double m_dSpeed;
	double m_dAcceleration;
	int ID;
};
