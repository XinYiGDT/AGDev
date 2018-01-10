#pragma once

#include "Vector3.h"
#include <vector>
using namespace std;

class CWaypoint
{
public:
	CWaypoint();
	virtual ~CWaypoint();

	//Set position
	void SetPosition(Vector3 position);
	//Get position
	Vector3 GetPosition(void) const;

	//Set ID
	void SetID(const int m_iID);
	//Get ID
	int GetID(void)const;

	//Add related waypoint
	void AddRelatedWaypoint(CWaypoint* relatedWaypoint);
	//Remove related waypoint
	bool RemoveRelatedWaypoint(const int m_iID);
	//get nearest waypoint amongst related waypoints
	CWaypoint* GetNearestWaypoint(void);
	//Get the number of related waypoints
	int GetNumberOfWaypoints(void)const;

	//Print self
	void PrintSelf(void);

protected:
	Vector3 position;
	int m_iID;

	vector<CWaypoint*> relatedWaypoints;
};
