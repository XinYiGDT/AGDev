#pragma once
#include "../GenericEntity.h"
#include "../GroundEntity.h"
#include "../SceneGraph.h"
#include "../Waypoint/Waypoint.h"

#include <vector>
using namespace std;

class Mesh;

class CEnemy : public GenericEntity
{
public:
	CSceneNode* theMainNode;
	CEnemy();
	virtual ~CEnemy();

	void Init(bool _isMoving = false);
	//Reset this player instance to default
	void Reset(void);


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
	//get next waypoint for this CEnemy
	CWaypoint* GetNextWaypoint(void);

	//update
	void Update(double dt = 0.0333f);

	//constrain the position within the borders
	void Constrain(void);
	//render
	void Render(void);

protected:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;

	//Vector containing IDs of waypoints
	vector<int> listOfWaypoints;
	//current ID of waypoints
	int m_iWayPointIndex;

	double m_dSpeed;
	double m_dAcceleration;
	bool isMoving;
};
